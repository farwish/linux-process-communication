#include <stdio.h>
#include <unistd.h>

int main()
{
	pid_t pid;					// fork返回值
	int file_descriptors[2];	// pipe参数
	int fd_ret;					// pipe返回值
	int process_signal = 0;
	ssize_t ret; 				// read返回值

	// 1. 先创建无名管道, 使父子进程继承
	fd_ret = pipe(file_descriptors);
	if (fd_ret < 0) {
		printf("create pipe failure\n");
		return -1;
	}

	// 2. 创建一个子进程
	pid = fork();
	
	// 子进程
	if (pid == 0) {
		int i;

		// 从管道中读到process_signal中, 如果空, 则睡眠
		ret = read(file_descriptors[0], &process_signal, 1);

		while(ret == 0);

		for (i = 0; i < 5; i++) {
			printf("child pid=%d i is %d\n", pid, i);
			usleep(100);
		}
	}

	// 父进程
	if (pid > 0) {
		int j;
		for (j = 0; j < 5; j++) {
			printf("parent pid=%d j is %d\n", pid, j);
			usleep(100);
		}

		usleep(1000000);

		// process_sianal写入管道
		write(file_descriptors[1], &process_signal, 1);
	}

	return 0;
}
