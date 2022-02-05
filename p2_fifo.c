#ifndef UTIL
#define UTIL
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>

#define BUFFLEN 100
#define MAX_FILENAME_SIZE 100

int checkerr(int ret, const char* msg){

	if (ret<0){
		perror(msg);
		exit(EXIT_FAILURE);
	}

	else{
		return ret;
	}
}

int main(){

    int fifo_fd;
    char buffer[BUFFLEN];
    char file[MAX_FILENAME_SIZE];
	strcpy(file, "fifo");
    
    for (int i=0;i<10;i++){

        fifo_fd = checkerr(open(file, O_RDONLY), "Error opening FIFO\n");
        printf("Reading....\n");
        sleep(1);
        checkerr(read(fifo_fd, buffer, sizeof(buffer)), "Error reading from FIFO\n");
        checkerr(close(fifo_fd), "Error closing FIFO\n");

        char buff[BUFFLEN];
        strncpy(buff, buffer, 2);
        int id = atoi(buff);
        int pointer;
        if (id>=10){
            pointer = 3;
        }
        else if (0<=id<10){
            pointer = 2;
        }

        char st1[7];
        for (int j=0;j<5;j++){
            st1[j] = buffer[pointer+j];
        }

        char st2[7];
        for (int j=0;j<5;j++){
            st2[j] = buffer[pointer+j+6];
        }

        char st3[7];
        for (int j=0;j<5;j++){
            st3[j] = buffer[pointer+j+12];
        }

        char st4[7];
        for (int j=0;j<5;j++){
            st4[j] = buffer[pointer+j+18];
        }

        char st5[7];
        for (int j=0;j<5;j++){
            st5[j] = buffer[pointer+j+24];
        }

        printf("Index: %d String: %s\n", id, st1);
        printf("Index: %d String: %s\n", id+1, st2);
        printf("Index: %d String: %s\n", id+2, st3);
        printf("Index: %d String: %s\n", id+3, st4);
        printf("Index: %d String: %s\n", id+4, st5);

        int feedback = id+4;
        char temp[5];
        sprintf(temp, "%d", feedback);
        fifo_fd = checkerr(open(file, O_WRONLY), "Error opening FIFO\n");
        checkerr(write(fifo_fd, temp, sizeof(temp)), "Error writing to FIFO\n");
        checkerr(close(fifo_fd), "Error closing FIFO\n");

    }

    exit(EXIT_SUCCESS);

}