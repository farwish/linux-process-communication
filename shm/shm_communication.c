#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <signal.h>

void func(int signum)
{
	return;
}

int main()
{
	int shmid;
	int pid;
	char *str;

	// 共享内存
	shmid = shmget(IPC_PRIVATE, 128, IPC_CREAT | 0777);

	if (shmid < 0) {
		printf("create share memory failure\n");
		return -1;
	}

	// fork 子进程
	pid = fork();

	if (pid > 0) {
		// parent process
		// signal 与 kill 配对使用
		signal(SIGUSR2, func);

		// 共享内存 映射\附着 操作
		str = (char *)shmat(shmid, NULL, 0);
		if (str == NULL) {
			printf("parent process shmat failure\n");
			return -2;
		}

		while(1) {
			printf("parent process write share memory:\n");

			// 写
			fgets(str, 128, stdin);
			
			// 发送信号到SIGUSR1
			kill(pid, SIGUSR1);

			// 暂停线程, 直到接收到一个信号
			pause();
		}
	}

	if (pid == 0) {
		signal(SIGUSR1, func);

		str = (char *)shmat(shmid, NULL, 0);

		if (str == NULL) {
			printf("child process shmat failure\n");
			return -4;
		}

		while(1) {
			pause();

			printf("child process read: %s", str);

			kill(getppid(), SIGUSR2);
		}
	}

	shmdt(str);

	shmctl(shmid, IPC_RMID, NULL);

	system("ipcs -m");

	return 0;
}
