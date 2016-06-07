#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main()
{
	const char *pathname = "mkfifo";
	int fd;
	int i;
	char buf = 1;

	// 1. 打开mkfifo文件才会在内核空间创建管道
	fd = open(pathname, O_WRONLY);

	if (fd < 0) {
		printf("open %s failure\n", pathname);
	}

	for (i=0; i < 5; i++) {
		printf("first process i=%d\n", i);
	}

	usleep(1000000);

	// 2. 写到管道
	write(fd, &buf, 1);

	return 0;
}
