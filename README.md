###linux-process-communication
===
* 进程通信: 在用户空间实现进程通信是不可能的, 通过Linux内核通信.  

* 线程间通信: 可以在用户空间就可以实现, 可以通过全局变量通信.  
( gcc -o build pthread.c -pthread )  

* 几种通信方式:  
> 管道通信: 无名管道, 有名管道(文件系统中有名).  
> 信号通信: 包括信号的发送\信号的接收和信号的处理.  
> IPC通信(Inter-Process Communication): 共享内存\消息队列和信号灯.  
>  // 以上是单机模式下的进程通信(只有一个Linux内核)
> Socket通信: 存在于一个网络中两个进程之间的通信(两个Linux内核)

* 进程通信思路: 每一种通信方式都是基于文件IO的思想.


