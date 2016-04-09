#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main()
{
	int fd[2];
	int ret;
	char writebuf[] = "linux";
	char readbuf[128] = {0};

	ret = pipe(fd);
	
	if (ret < 0) {
		printf("create pipe failure\n");
		return -1;
	}

	// fd[0]读, fd[1]写
	printf("create pipe success, fd[0]=%d, fd[1]=%d\n", fd[0], fd[1]);

	// writebuf写入管道
	write(fd[1], writebuf, sizeof(writebuf));

	// read from pipe
	read(fd[0], readbuf, 128);
	printf("readbuf=%s\n", readbuf);

	// 将readbuf前128字节设为0
	memset(readbuf, 0, 128);
	// 由于第一次读完,管道就销毁了, 所以第二次读将阻塞
	read(fd[0], readbuf, 128);
	printf("readbuf is %s\n", readbuf);

	// 读端和写端关闭
	close(fd[0]);
	close(fd[1]);

	return 0;
}
