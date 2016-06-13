#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/ipc.h>
#include <sys/sem.h>

union semun {
	int val; // 设置信号灯的值
	struct semid_ds *buf;
	unsigned short *array;
};

struct sembuf {
	short sem_num;  // 信号量标号
	short sem_op;   // 信号量操作
	short sem_flag; // 阻塞或非阻塞
}

int semid;
union semun mysemun;
struct sembuf mysembuf;

void *fun(void *p)
{
	int i;

	semop();
	// sem_wait(&sem);
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
	semid = semget(IPC_PRIVATE, 3, 0777);
	if (semid < 0) {
		printf("create semaphore failure\n");
		exit(1);
	}
	printf("semaphore semid = %d\n", semid);

	system("ipcs -s");

	// 初始化信号灯
	mysemun.val = 0;
	ret = semctl(semid, 0, SETVAL, mysemun);
	if (ret < 0) {
		printf("semctl setval failure\n");	
		exit(1);
	}

	mysembuf.sem_num = 0;
	mysembuf.sem_op = 0;
	mysembuf.sem_flag = 0;
	ret = semop(semid, &mysembuf, 3);
	if (ret < 0) {
		printf("IPC error: semop\n");
		exit(1);
	}

	ret = pthread_create(&tid, NULL, fun, (void *)str);

	if (ret < 0) {
		printf("create pthread failure\n");
		exit(1);
	}

	for (j = 0; j < 5; j++) {
		printf("man pthread j is %d\n", j);
		usleep(100);
	}

	//sem_post(&sem);

	sleep(2);

	return 0;
}
