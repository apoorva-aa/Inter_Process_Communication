#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <errno.h>

#define PROJECT_PATHNAME "p1_mesq.c"
#define PROJECT_ID 57
#define MSG_SIZE 512

struct msg_struct{
	long type;
	int id1;
	int id2;
	int id3;
	int id4;
	int id5;
	char value1[50];
	char value2[50];
	char value3[50];
	char value4[50];
	char value5[50];
}message;

struct msg_struct_1{
	long type;
	int id;
}feedback;

int main(){

	char arr[50][6];

	char str[100] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";

	for (int i=0;i<50;i++){
		for (int j=0;j<5;j++){
			int x = (rand())%62;
			arr[i][j] = str[x];
			arr[i][j+1] = '\0';
		}
	}

	key_t key = ftok(PROJECT_PATHNAME, PROJECT_ID);
	if (key==-1){
		printf("Error generating message key\n");
		return -1;
	}

	int qid = msgget(key, 0666|IPC_CREAT);
	if (qid==-1){
		printf("Error retrieving queue id\n");
		return -1;
	}

	int idx = 0;
	for (int i=0;i<10;i++){
		message.id1 = idx;
		strcpy(message.value1, arr[idx]);
		
		message.id2 = idx+1;
		strcpy(message.value2, arr[idx+1]);
		
		message.id3 = idx+2;
		strcpy(message.value3, arr[idx+2]);
		
		message.id4 = idx+3;
		strcpy(message.value4, arr[idx+3]);
		
		message.id5 = idx+4;
		strcpy(message.value5, arr[idx+4]);

		message.type = 12345;
		
		if(msgsnd(qid, &message, MSG_SIZE, 0)==-1){
			printf("Error sending message\n");
			return -1;
		}
		idx += 5;

		printf("Recieving....\n");
		sleep(1);
		if (msgrcv(qid, &feedback, MSG_SIZE, 54321, 0)==-1){
			printf("Error receiving message\n");
			return -1;
		}
		printf("ID: %d\n", feedback.id);

	}


}