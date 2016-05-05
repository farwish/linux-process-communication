#include <stdio.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>

int main()
{
	int shmid;
	char *str;
	int key;

	key = ftok("./shmget_ftok.c", 1);

	if (key < 0) {
		printf("create ftok failure\n");
		return -2;
	}

	printf("create ftok success, key = %d\n", key);
	
	// 第三个参数必须使用IPC_CREAT, 否则创建失败
	shmid = shmget(key, 128, IPC_CREAT | 0755);

	if (shmid < 0) {
		printf("create shm failure\n");
		return -1;
	}

	printf("create shm success, shmid = %d\n", shmid);

	// 查看消息队列
	//system("ipcs -q");

	// 查看共享内存段
	//system("ipcs -m");

	// 查看信号量数组
	//system("ipcs -s");
	
	//sprintf(str, "ipcrm -m %d", shmid);
	// 按ID号移除共享内存段
	//system(str);

	// 通过IPC_PRIVATE宏 创建的共享内存, key始终为0x00000000
	system("ipcs");

	return 0;
}
