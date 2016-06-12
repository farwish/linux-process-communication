#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

sem_t sem;
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

	sem_init(&sem, 0, 0);

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
