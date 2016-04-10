#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main()
{
	const char *pathname = "mkfifo";
	int fd;
	int i;
	char buf = 0;

	// 1. 打开mkfifo管道
	fd = open(pathname, O_RDONLY);

	if (fd < 0) {
		printf("open %s failure\n", pathname);
	}

	// 读取管道内容到buf中
	read(fd, &buf, 1);

	while (buf == 0);

	for (i=0; i < 5; i++) {
		printf("second process i=%d\n", i);
	}

	return 0;
}
