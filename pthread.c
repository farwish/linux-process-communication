#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int flag = 0;
void *fun(void *p)
{
	int i;
	for (i = 0; i < 5; i++) {
		usleep(100);
		printf("child pthread i is %d\n", i);
	}

	flag = 1;
}

int main()
{
	char str[] = "hello\n";
	pthread_t tid;
	int ret;
	int j;

	ret = pthread_create(&tid, NULL, fun, (void *)str);

	if (ret < 0) {
		printf("create pthread failure\n");
		return -1;
	}

	while(flag == 0);
	for (j = 0; j < 5; j++) {
		printf("man pthread j is %d\n", j);
		usleep(100);
	}

	return 0;
}
