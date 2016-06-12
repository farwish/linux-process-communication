#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/ipc.h>
#include <sys/sem.h>

int semid;
union semun {
	int val;
	struct semid_ds *buf;
	unsigned short *array;
} arg;

void *fun(void *p)
{
	int i;
	sem_wait(&sem);
	for (i = 0; i < 5; i++) {
		usleep(100);
		printf("child pthread i is %d\n", i);
	}

}

int main()
{
	char str[] = "hello\n";
	pthread_t tid;
	int ret;
	int j;

	// 创建信号灯标示符
	semget(IPC_PRIVATE, 3, 0777);
	if (semid < 0) {
		printf("create semaphore failure\n");
		return -1;
	}
	printf("semaphore semid = %d\n", semid);

	system("ipcs -s");

	// 初始化
	semctl();

	ret = pthread_create(&tid, NULL, fun, (void *)str);

	if (ret < 0) {
		printf("create pthread failure\n");
		return -1;
	}

	for (j = 0; j < 5; j++) {
		printf("man pthread j is %d\n", j);
		usleep(100);
	}

	sem_post(&sem);

	sleep(2);

	return 0;
}
