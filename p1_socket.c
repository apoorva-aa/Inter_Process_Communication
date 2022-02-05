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

	int sock_fd, receiving;
	struct sockaddr_un dest;
	char buff[100];
	int flag = 1;

	if ((sock_fd = socket(AF_UNIX, SOCK_DGRAM, 0)) < 0) {
		perror("socket");
		flag = 0;
	}

	if (flag) {
		memset(&dest, 0, sizeof(dest));
		dest.sun_family = AF_UNIX;
		strcpy(dest.sun_path, SERVER_SOCK_FILE);
		if (connect(sock_fd, (struct sockaddr *)&dest, sizeof(dest)) == -1) {
			perror("connect");
			flag = 0;
		}
	}

	if (flag) {
		memset(&dest, 0, sizeof(dest));
		dest.sun_family = AF_UNIX;
		strcpy(dest.sun_path, CLIENT_SOCK_FILE);
		unlink(CLIENT_SOCK_FILE);
		if (bind(sock_fd, (struct sockaddr *)&dest, sizeof(dest)) < 0) {
			perror("bind");
			flag = 0;
		}
	}


	int idx = 0;

	for (int i=0;i<10;i++){

		char temp[50];

		sprintf(temp, "%d", idx);
		strncat(temp, " ", 2);
		for (int j=0;j<5;j++){
			strncat(temp, arr[idx+j], 5);
			strncat(temp, " ", 2);
		}

		if (flag) {
			strcpy (buff, temp);
			if (send(sock_fd, buff, strlen(buff), 0) == -1) {
				perror("send");
				flag = 0;
			}
		}

		if (flag) {
			if ((receiving = recv(sock_fd, buff, 100, 0)) < 0) {
				perror("recv");
				flag = 0;
			}
			printf("Receiving....\n");
			sleep(1);
			int id = atoi(buff);
			printf ("ID: %d\n", id);
		}

		idx+=5;
	}

	if (sock_fd >= 0) {
		close(sock_fd);
	}

	unlink (CLIENT_SOCK_FILE);
	return 0;


}