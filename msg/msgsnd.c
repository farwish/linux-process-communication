#include <stdio.h>
#include <sys/msg.h>
#include <string.h>

struct msgbuf {
	long type;
	char text[124];
	char id[4];
};

int main()
{
	int msgid;
	struct msgbuf sendbuf,rcvbuf;

	msgid = msgget(IPC_PRIVATE, 0777);

	if (msgid < 0) {
		printf("create msg queqes failure\n");
		return -1;
	}

	printf("message queues msgid = %d\n", msgid);

	system("ipcs -q");

	// 初始化
	sendbuf.type = 100;
	printf("please input message: \n");
	fgets(sendbuf.text, 124, stdin);
	// 向消息队列写消息
	msgsnd(msgid, (void *)&sendbuf, strlen(sendbuf.text), 0);	

	memset(rcvbuf.text, 0, 124);
	msgrcv(msgid, (void *)&rcvbuf, 124, 100, 0);
	printf("receive message queu data: %s\n", rcvbuf.text);

	msgctl(msgid, IPC_RMID, NULL);

	system("ipcs -q");

	return 0;
}
