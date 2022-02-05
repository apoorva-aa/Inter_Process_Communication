Answer 2

This question focuses on three types of IPCs : named piped or FIFOs, message queues, unix domain sockets. In this question, in the process P1 first we have generated a an array of 50 strings, each composed of 5 characters (eg: ygdj6). 

FIFO : p1_fifo.c 	p2_fifo.c

Named pipes or FIFOs (First In First Out) help in inter-process communication by creating a file which can be read or written in. FIFOs are by default blocking processes and therefore, when one process is writing into the file, the other process is blocked from interacting with it. Similarly, when the other process is reading the file, the first process cannot write into it simultaneously.

Here, first we have made a new fifo file (named "fifo") using the command "mkfifo(const char *pathname, mode_t mode);" which takes in the file path and the mode (the permissions of the created file) as parameters. Then, we need to send in 5 elements of the array at once, so to send 50 elements in such a manner, we execute a for loop ten times. In eahc for loop, we concatenate all the strings values and ids, separated by ids and send them  to process P2 (basically write them into the created file "fifo"). First, we open the file we created. Then, we write those strings into the file through the command  "write(fifo_fd, buff, sizeof(buff);" Here, fifo_fs is the file descriptor of the file, buff is a buffer which holds the data (strings, ids) to be sent. After writing this, the control moves to process P2 which reads these strings using the command: "read(fifo_fd, buffer, sizeof(buffer))". After reading these, we print them out onto the console and identify the highest ID sent to P2, which then P2 sends back to process P1. When process P1 reads the file now, it finds the highest ID sent by P2 which confirms that P2 has successfully received the strings and P1 prints out the ids onto the screen.

TO RUN THIS PROGRAM - split the terminal into two and enter the following commands (mentioned in the makefile):
	1. make fifo (any terminal works) - generates executable files
	2. make run_f1 (Terminal 1)  (these steps must be followed in this order only)
	3. make run_f2 (Terminal 2)

Message Queues : p1_mesq.c 		p2_mesq.c

Message queues are maintained by the kernel wherein one process (sender) van pass messages and another process (receiver) can read those messages. Here also the reading/retrieval of messages happens in a first in first out order (FIFO). 

For process P1 first we generate a new queue using the msgget() call. This requires a key, which can be generated as follows: 
	ftok(PROJECT_PATHNAME, PROJECT_ID); - Here, first argument is path of the process, the second being the ID associated with the project.
When we call msgget(), an id is generated which is associated with the message queue. For the purpose of this question we have customized the struct of the message queue, giving it the standard long type (important), and additionally giving it 5 integer type fields to store IDs and 5 String (char arrays) type fields to store 5 strings which need to be sent at once. We send the message to the queue using the command : msgsnd(qid, &message, MSG_SIZE, 0); Here, first parameter is the message queue id, seconnd is the pomiter to the message, third is the size of the message and last one is for flags. When we have passed the message, P2 now retrieves the message through the command (msgrcv(qid, &message, MSG_SIZE, 12345, 0); Here, first parameter is again the queue id, them the pointer ot the message, then the size, then the type of the message (message.type) which was set in the process P1. It reads the message and prints it out, sending back the highest ID received to process P2, telling it that the messages have been delivered. P1 in turn retrieves that ID from the queue and prints it out.

TO RUN THIS PROGRAM - split the terminal into two and enter the following commands (mentioned in the makefile):
	1. make queue (any terminal works) - generates executable files
	2. make run_q1 (Terminal 1)  (these steps must be followed in this order only)
	3. make run_q2 (Terminal 2)


Unix Domain Sockets : p1_socket.c 	p2_socket.c

Sockets retrieve the information on one port/destination while the other socket (or node) reaches out and connects with it for communication. Server forms the listener socket, while the client reaches out to server. In this case, P1 is the client and P2 is the server.

Here, first in P1 (server), we have made a socket and  which is a unix domain socket datagram since we want to send the data as "packets" rather than in a continuous stream. This socket belongs to AF_UNIX family of sockets which help in efficient communication between process on the same machine. SOCK_DGRAM socket helps in keeping our data separate and ordered.  The familt of sockets here, sun_family always contains AF_UNIX sockets. Then we connect and bind the sockets using the following commands: 
	int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
	int connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen);

Here, sockfd is the file descriptor, and the second argument is the address. The bind() call assigns the address specified by address (second parameter) to the socket with file descriptor as metioned in the first argument. The connect syscall connects the socket with the particular file descriptor to the address mentioned after it. The third argument is the address space. After this is done, we go to P1 (client) which sends out the strings as we sent them in FIFOs, to the P2 (server). Socket is a 2 way connectiona nd thus when P2 receives the strings is acknowledged it by sending back the highest ID it received from P1, back to P1. The process P1 prints out the IDs, while P2 prints out the Strings and their indices.

TO RUN THIS PROGRAM - split the terminal into two and enter the following commands (mentioned in the makefile):
	1. make socket (any terminal works) - generates executable files
	2. make run_s2 (Terminal 1)  (these steps must be followed in this order only)
	3. make run_s1 (Terminal 2)  (*The order is dfferent here since P2 (server) needs to be made first so that P1 (client) can connect with it)
