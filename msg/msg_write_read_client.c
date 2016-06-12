#include <stdio.h>
#include <stdlib.h>
#include <sys/msg.h>
#include <string.h>

typedef struct {
	long type;
	char text[124];
} msg_buf;

int main()
{	
	int msgid;
	msg_buf sendbuf, recvbuf;
	int key;
	int pid;

	key = ftok("b.c", 1);

	if (key < 0) {
		printf("create key failure\n");
		return -1;
	}

	msgid = msgget(key, IPC_CREAT | 0777);

	if (msgid < 0) {
		printf("create message quequ failure\n");
		return -2;
	}

	system("ipcs -q");

	printf("server msgid = %d\n", msgid);

	pid = fork();

	recvbuf.type = 100;

	if (pid > 0) {
		while (1) {
			memset(recvbuf.text, 0, 124);

			msgrcv(msgid, (void *)&recvbuf, 124, recvbuf.type, 0);

			printf("client message queue receive data: %s", recvbuf.text);
		}
	}

	// child process write
	if (pid == 0) {
		sendbuf.type = 200;

		while (1) {
			memset(sendbuf.text, 0, 124);
			printf("client start write:\n");
			fgets(sendbuf.text, 124, stdin);
			msgsnd(msgid, (void *)&sendbuf, strlen(sendbuf.text), 0);
		}
	}

	msgctl(msgid, IPC_RMID, NULL);

	return 0;
}
