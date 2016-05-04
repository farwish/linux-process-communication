#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void func(int sign)
{
	int i = 0;
	while(1) {
		i++;
		printf("func i = %d\n", i);
		sleep(1);
		if (i > 9) {
			break;
		}
	}
	return;
}

int main()
{
	// void (*signal(int sig, void (*func)(int)))(int)
	// 信号处理
	signal(14, func);

	// printf("start pause\n");
	// 暂停线程直到收到一个信号
	// pause();

	// 预定一个闹铃信号,时间5秒钟
	alarm(5);

	// 如果设为忽略, 则不会处理开始时设置的signal任务
	// signal(14, SIG_IGN);

	// 如果设为默认, 则会终止进程, 默认信号处理方式是终止
	// signal(14, SIG_DFL);
	
	int i = 0;
	while(1) {
		i++;
		printf("main i = %d\n", i);
		sleep(1);
		if (i > 9) {
			break;
		}
	}
	return 0;
}
