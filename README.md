##linux-process-communication
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

	*缺点：不能实现非父子进程的通信, 因为父子进程共享内核空间的管道.*

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
	```
	有名就是文件系统中存在这个文件节点, 有inode号, 文件类型为p管道类型.

	mkfifo用来创建管道文件节点, 没有在内核中创建管道, 只有通过open函数打开这个文件时才会在内核空间创建管道.  
	```

	```
	open函数只能创建普通文件  
	( 管道：mkfifo, 套接字：socket, 字符设备文件：mknod, 链接文件：ln -s, 目录文件：mkdir )
	
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

* 信号通信: mykill.c , `kill -l` 查看系统中的信号  
	```
	gcc -o build while.c

	./build

	gcc -o mykill mykill.c

	./mykill 9 pid  
	```
* 信号通信框架  

	信号的发送(发送信号进程): `kill()` , `raise()` , `alarm()`  
	```
	`int kill(pid_t pid, int sig)`  // send a signal to a process or a group of processes, 可以向任意进程发送不同信号

	`int raise(int sig)`  // send a signal to the caller, 只能向当前进程发送不同信号

	`unsigned alarm(unsigned seconds)`  // schedule an alarm signal, 发送闹钟信号  
	```

	信号的接收(接收信号进程): `pause()` , `sleep()` , `while(1)`  

	信号的处理(接收信号进程): `signal()`  
	```
	第一个参数: 处理哪个信号;

	第二个参数: 采用什么方式处理(忽略:SIG_IGN, 默认的:SIG_DFL, 自定义的)  
	```

* IPC通信 (文件IO的思想)  

	|文件I/O		| IPC
	|---			|---
	|open			| msgget<br/> shmget<br/> semget
	|read<br/> write	| msgsnd msgrecv<br/> shmat shmdt<br/> semop
	|close			| msgctrl<br/> shmctrl<br/> semctrl

	共享内存 shared memory （sys/shm.h）  
	
	`shmget`: 创建一个共享内存, 通过 IPC_PRIVATE宏 创建的共享内存, key始终为0x00000000. (shmget.c)

	```
	`ipcs -q`	查看消息队列

	`ipcs -m`	查看共享内存段

	`ipcs -s`	查看信号量数组

	`ipcrm -m ID`	按ID号移除共享内存段  
	```

	`ftok`: 创建key值, 作为 shmget 的第一个参数使用, 此时 shmget 第三个参数必须是IPC_CREAT, 此时创建的共享内存是非亲缘关系的; ftok 的参数不变时, 不会创建多个key. (shmget_ftok.c)

	`shmat`: 将共享内存映射到用户空间的地址上, 便于高效读写, 第二个参数NULL表示由系统随机分配, 第三个参数0允许读写. (shmget_shmat.c)  
	```
	共享内存创建之后, 一直存在于内核中, 直到被删除或系统关系.

	共享内存和管道不一样, 读取后, 内容仍在其共享内存中.  
	```
	
	`shmdt`: 删除共享内存在用户空间地址的映射.  
	
	`shmctl`: 删除共享内存对象. (shmget_shmat_shmctl.c)  
	( `int shmctl(int shmid, int cmd, struct shmid_ds *buf)` )
	```
	cmd:  

	IPC_STAT(获取对象属性,实现了ipcs -m)

	IPC_SET(设置对象属性)

	IPC_RMID(删除对象,实现了ipcrm -m)

	buf:  
	
	指定IPC_STAT, IPC_SET 时用以保存/设置属性  
	```
