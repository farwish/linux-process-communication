#include <stdio.h>
#include <signal.h>

int main(int argc, char *argv[])
{
	int sig;
	int pid;
	int ret;

	if (argc < 2) {
		printf("please input two param\n");
		return -1;
	}

	sig = atoi(argv[1]);
	pid = atoi(argv[2]);
	
	ret = kill(pid, sig);

	if (ret < 0) {
		printf("kill pid=%d error\n", pid);
		return -2;
	}

	return 0;
}
