#ifndef IPC_H
#define IPC_H

#define CLIENT_SOCK_FILE "client.sock"
#define SERVER_SOCK_FILE "server.sock"

#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

int main() {

	char arr[50][6];

	char str[100] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";

	for (int i=0;i<50;i++){
		for (int j=0;j<5;j++){
			int x = (rand())%62;
			arr[i][j] = str[x];
			arr[i][j+1] = '\0';
		}
	}

	int sock_fd, sending, receiving;
	struct sockaddr_un dest;
	struct sockaddr_un src;
	char buff[100];
	int flag = 1;
	socklen_t addr = sizeof(src); //size of address

	if ((sock_fd = socket(AF_UNIX, SOCK_DGRAM, 0)) < 0) { //datagrams
		perror("socket");
		flag = 0;
	}

	if (flag!=0) {
		memset(&dest, 0, sizeof(dest));
		dest.sun_family = AF_UNIX;
		strcpy(dest.sun_path, SERVER_SOCK_FILE);
		unlink(SERVER_SOCK_FILE);
		if (bind(sock_fd, (struct sockaddr *)&dest, sizeof(dest)) < 0) {
			perror("bind");
			flag = 0;
		}
	}
	

	while ((receiving = recvfrom(sock_fd, buff, 100, 0, (struct sockaddr *)&src, &addr)) > 0) {
		
		char buffer[50];
        strncpy(buffer, buff, 2);
        int id = atoi(buffer);
        int pointer;
        if (id>=10){
            pointer = 3;
        }
        else if (0<=id<10){
            pointer = 2;
        }

        char st1[7];
        for (int j=0;j<5;j++){
            st1[j] = buff[pointer+j];
        }

        char st2[7];
        for (int j=0;j<5;j++){
            st2[j] = buff[pointer+j+6];
        }

        char st3[7];
        for (int j=0;j<5;j++){
            st3[j] = buff[pointer+j+12];
        }

        char st4[7];
        for (int j=0;j<5;j++){
            st4[j] = buff[pointer+j+18];
        }

        char st5[7];
        for (int j=0;j<5;j++){
            st5[j] = buff[pointer+j+24];
        }

		printf("Reading....\n");
		sleep(1);

        printf("Index: %d String: %s\n", id, st1);
        printf("Index: %d String: %s\n", id+1, st2);
        printf("Index: %d String: %s\n", id+2, st3);
        printf("Index: %d String: %s\n", id+3, st4);
        printf("Index: %d String: %s\n", id+4, st5);
		int feedback = id+4;
        char temp[5];
        sprintf(temp, "%d", feedback);
		sending = sendto(sock_fd, temp, strlen(temp), 0, (struct sockaddr *)&src, addr);
		if (sending < 0) {
			perror("sendto");
			break;
		}
	}
	

	if (sock_fd >= 0) {
		close(sock_fd);
	}

	return 0;
}