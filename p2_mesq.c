#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
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


    for (int i=0;i<10;i++){
        
        if (msgrcv(qid, &message, MSG_SIZE, 12345, 0)==-1){
            printf("Error receiving message\n");
            return -1;
        }
        printf("Reading....\n");
        sleep(1);
        printf("Index: %d String: %s\nIndex: %d String: %s\nIndex: %d String: %s\nIndex: %d String: %s\nIndex: %d String: %s\n", message.id1, message.value1, message.id2, message.value2, message.id3, message.value3, message.id4, message.value4, message.id5, message.value5 );

        feedback.id = message.id5;
        feedback.type = 54321;
        if(msgsnd(qid, &feedback, MSG_SIZE, 0)==-1){
			printf("Error sending message\n");
			return -1;
		}
        
    }
    printf("\n");

    msgctl(qid, IPC_RMID, NULL);	


}

