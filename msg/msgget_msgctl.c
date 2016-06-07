#include <stdio.h>
#include <sys/msg.h>

int main()
{
	int msgid;

	msgid = msgget(IPC_PRIVATE, 0777);

	if (msgid < 0) {
		printf("create msg queqes failure\n");
		return -1;
	}

	printf("message queues msgid = %d\n", msgid);

	system("ipcs -q");

	msgctl(msgid, IPC_RMID, NULL);

	system("ipcs -q");

	return 0;
}
