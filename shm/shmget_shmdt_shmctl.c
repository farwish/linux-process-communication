#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>

int main()
{
	int shmid;
	char *p;
	
	shmid = shmget(IPC_PRIVATE, 128, 0755);

	if (shmid < 0) {
		printf("create shm failure\n");
		return -1;
	}

	printf("create shm success, shmid = %d\n", shmid);

	// 映射到用户空间, 第二个参数NULL表示随机分配, 
	p = (char *)shmat(shmid, NULL, 0);

	if (p == NULL) {
		printf("shmat failure\n");
		return -2;
	}

	system("ipcs -m");

	fgets(p, 128, stdin);

	printf("p is %s\n", p);
	printf("second p is %s\n", p);

	// 删除共享内存在用户空间地址的映射
	if (shmdt(p) < 0) {
		printf("shmdt p failure\n");
		return -3;
	}

	// printf("third p is %s\n", p); 对不存在的地址操作,段错误

	// 删除共享内存
	shmctl(shmid, IPC_RMID, NULL);
	system("ipcs -m");

	return 0;
}
