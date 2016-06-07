#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <signal.h>

struct buf {
	int pid;
	char bufs[124];
};

void func(int signum)
{
	return;
}

// server

int main()
{
	int shmid;
	int key;
	int pid;
	struct buf *p;

	// 非父子进程间通信必须使用key
	key = ftok("a.c", 1);

	if (key < 0) {
		printf("create key failure\n");
		return -1;
	}

	// 共享内存
	shmid = shmget(key, 128, IPC_CREAT | 0777);

	if (shmid < 0) {
		printf("create share memory failure\n");	
		return -2;
	}

	printf("share memory shmid = %d\n", shmid);

	// 设置信号
	signal(SIGUSR1, func);

	p = (struct buf *)shmat(shmid, NULL, 0);
	if (p == NULL) {
		printf("server shmat failure\n");
		return -3;
	}

	p->pid = getpid(); // server process id 写入共享内存

	pause(); // 等 client 读取

	pid = p->pid; // 获取 client process id

	printf("server could start to write:\n");

	while (1) {
		// 写
		fgets(p->bufs, 124, stdin);

		// 发送信号
		kill(pid, SIGUSR2);

		// 暂停, 等待client读
		pause();
	}
}
