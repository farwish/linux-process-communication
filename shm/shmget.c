#include <stdio.h>
#include <sys/shm.h>

int main()
{
	int shmid;
	char *str;
	
	// key=IPC_PRIVATE, 创建size=128byte的共享内存,权限shmflg=0755, 返回标示符id
	shmid = shmget(IPC_PRIVATE, 128, 0755);

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
