#include <stdio.h>
#include <unistd.h>

int main()
{
	pid_t pid;
	int flag = 0;
	pid = fork();

	if (pid == 0) {
		while (flag == 0);

		int i = 0;
		for (i; i < 5; i++) {
			printf("child pid=%d i is %d\n", pid, i);
			usleep(100);
		}
	}

	if (pid > 0) {
		int j = 0;

		for (j; j < 5; j++) {
			printf("parent pid=%d j is %d\n", pid, j);
			usleep(100);
		}

		flag = 1;
	}

	return 0;
}
