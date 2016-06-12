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
	msg_buf sendbuf;
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

	system("ipcs -q");

	printf("server msgid = %d\n", msgid);

	while (1) {
		// 缓存初始化
		memset(sendbuf.text, 0, 124);

		sendbuf.type = 100;

		printf("server start write:\n");

		fgets(sendbuf.text, 124, stdin);

		msgsnd(msgid, (void *)&sendbuf, strlen(sendbuf.text), 0);
	}
	return 0;
}
