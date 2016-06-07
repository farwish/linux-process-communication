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

// client 

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
	signal(SIGUSR2, func);

	p = (struct buf *)shmat(shmid, NULL, 0);
	if (p == NULL) {
		printf("client shmat failure\n");
		return -3;
	}

	// 读取 server process id
	pid = p->pid;

	// 设置 client process id
	p->pid = getpid();

	// 向 server process id 发信号
	kill(pid, SIGUSR1);

	while(1) {
		pause();

		printf("client receive data: %s", p->bufs);

		kill(pid, SIGUSR1);
	}
}
