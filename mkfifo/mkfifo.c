#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>

int main()
{
	int ret;
	const char *pathname = "mkfifo";
	mode_t mode = 0777;
	
	ret = mkfifo(pathname, mode);

	if (ret < 0) {
		printf("create mkfifo file failure\n");
		return -1;
	}

	return 0;
}
