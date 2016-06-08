#include <stdio.h>
#include <stdlib.h>
#include <sys/msg.h>
#include <string.h>

int main()
{	
	int msgid;
	typedef struct {
		long type;
		char text[124];
	} msg_buf;
	msg_buf sendbuf, recvbuf;
	int key;

	key = ftok("a.c", 1);

	if (key < 0) {
		printf("create key failure\n");
		return -1;
	}

	msgid = msgget(key, IPC_CREAT | 0777);

	if (msgid < 0) {
		printf("create message quequ failure\n");
		return -2;
	}

	printf("server msgid = %d\n", msgid);

	while (1) {
		memset(sendbuf.text, 0, strlen(sendbuf.text));
		sendbuf.type = 100;

		printf("server start write:\n");

		fgets(sendbuf.text, 0, stdin);

		msgsnd(msgid, (void *)&sendbuf, strlen(sendbuf.text), 0);
	}
	return 0;
}