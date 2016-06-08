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
		memset(recvbuf.text, 0, strlen(recvbuf.text));
		recvbuf.type = 100;

		msgrcv(msgid, (void *)&recvbuf, strlen(recvbuf.text), recvbuf.type, 0);

		printf("client message queue receive data: %s\n", recvbuf.text);
	}
	return 0;
}
