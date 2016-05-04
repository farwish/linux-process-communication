#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void func(int signum)
{
	int j = 0;
	while ( j < 5 ) {
		j++;
		printf("func receive signum = %d, j = %d\n", signum, j);
		sleep(1);
	}
	return;
}

void func1(int signum)
{
	printf("func1 receive signum = %d\n", signum);
	wait(NULL);
	return;
}

int main()
{
	pid_t pid;
	int i = 0;

	pid = fork();

	signal(10, func);
	signal(17, func1);

	if (pid > 0) {
		while ( i < 10 ) {
			i++;
			printf("parent process, i = %d\n", i);
			sleep(1);
		}
	}

	if (pid == 0) {
		sleep(1);
		kill(getppid(), 10);
		sleep(10);
		// 10秒后执行17号信号
		exit(0); // kill(getppid(), 17)
	}

	return 0;
}
