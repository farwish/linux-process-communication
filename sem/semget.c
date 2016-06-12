#include <stdio.h>
#include <semaphore.h>
#include <sys/sem.h>

int main()
{
	int semid;
	
	semid = semget(IPC_PRIVATE, 3, IPC_CREAT | 0777);

	if (semid < 0) {
		printf("create semaphore failure\n");	
		return -1;
	}

	printf("semaphore id is %d\n", semid);

	system("ipcs -s");

	semctl(semid, 3, IPC_RMID);

	system("ipcs -s");

	return 0;
}
