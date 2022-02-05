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

	char arr[50][5];
	char file[MAX_FILENAME_SIZE];
	strcpy(file, "fifo");
	char str[100] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";

	for (int i=0;i<50;i++){
		for (int j=0;j<5;j++){
			int x = (rand())%62;
			arr[i][j] = str[x];
			arr[i][j+1] = '\0';
		}
	}

	int idx = 0;
	int r = 0;
	int fifo_fd;
	char buffer[BUFFLEN];

	checkerr(mkfifo(file, 0777), "Error creating FIFO\n");

	while (idx<50){

		if (r!=0){
			fifo_fd = checkerr(open(file, O_RDONLY), "Error opening FIFO");
			printf("Receiving...\n");
			sleep(1);
			checkerr(read(fifo_fd, buffer, sizeof(buffer)), "Error reading from FIFO");
			buffer[BUFFLEN - 1] = 0;
			idx = atoi(buffer);
			printf("ID = %d\n", idx);
			idx++;
			checkerr(close(fifo_fd), "Error closing FIFO\n");
		}

		if (idx<50){
			r = 1;

			char buff[50] = "";

			sprintf(buff, "%d", idx);
			strncat(buff, " ", 2);
			for (int i=0;i<5;i++){
				strncat(buff, arr[idx+i], 5);
				strncat(buff, " ", 2);
			}

			fifo_fd = checkerr(open(file, O_WRONLY), "Error opening FIFO\n");
			checkerr(write(fifo_fd, buff, sizeof(buff)), "Error writing to FIFO\n");

			checkerr(close(fifo_fd), "Error closing FIFO\n");
		}
		

	}

	checkerr(remove(file), "Error removing FIFO\n");

	exit(EXIT_SUCCESS);
}