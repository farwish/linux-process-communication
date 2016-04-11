###linux-process-communication
===
* 进程通信: 在用户空间实现进程通信是不可能的, 通过Linux内核通信.  
* 线程间通信: 可以在用户空间就可以实现, 可以通过全局变量通信.  
	( `gcc -o build pthread.c -pthread` )  
* 几种通信方式: 
	```
	管道通信: 无名管道, 有名管道(文件系统中有名).  
	
	信号通信: 包括信号的发送\信号的接收和信号的处理.  
	
	IPC通信(Inter-Process Communication): 共享内存\消息队列和信号灯.  
	( 以上是单机模式下的进程通信, 只有一个Linux内核 )
	
	Socket通信: 存在于一个网络中两个进程之间的通信, 两个Linux内核.  
  
	进程通信思路, 每一种通信方式都是基于文件IO的思想.  
	```

* 无名管道: pipe函数 (pipe.c , fork_2.c 含注释) 
	```
	创建父进程与子进程, 并在内核空间创建一个管道, 子进程先读管道内容, 没有内容有读阻塞;  
	当父进程在管道内写完内容后, 子进程从睡眠转而运行;  
	缺点：不能实现非父子进程的通信, 因为父子进程共享内核空间的管道.  
	
	fd[1] 入队 write -> fd[0] 出队 read , 对应到用户空间就是文件描述符.  
	
	管道中的东西, 读完就删除了, 如果管道中没有东西可读, 则会读阻塞; 管道写满后, 写阻塞.  
	```
	```
	1. 先创建无名管道 (为了使父子进程继承)  
	2. 创建一个子进程  
	3. 子进程读取管道内容 (读阻塞)
	4. 父进程写入管道
	```

* 有名管道: mkfifo函数 (mkfifo.c) , First Input First Output  
	> 有名就是文件系统中存在这个文件节点, 有inode号, 文件类型为p管道类型.  
	> mkfifo用来创建管道文件节点, 没有在内核中创建管道, 只有通过open函数打开这个文件时才会在内核空间创建管道.  

	```
	open函数只能创建普通文件  
	( 管道 - mkfifo, 套接字 - socket, 字符设备文件 - mknod, 链接文件 ln -s, 目录文件 - mkdir )  
	
	管道文件只有inode号, 不占磁盘块空间, 和套结字\字符设备文件一样;  
	普通文件和符号链接文件及目录文件, 不仅有inode号, 还占磁盘空间.  
	```
	```
	# 非亲缘关系文件间进程通信
	gcc -o build mkfifo.c  
	./build  
	gcc -o first first_mkfifo.c  
	gcc -o second second_mkfifi.c  
	./first     # 第一个终端  
	./second    # 第二个终端  
	```

* 信号通信(mykill.c) 
	`kill -l` 查看系统中的信号

	```
	gcc -o build while.c
	./build
	gcc -o mykill mykill.c
	./mykill 9 pid
	```
