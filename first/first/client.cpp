#include <stdio.h>
#include <sys/socket.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdlib.h>

void error_handing(char *message) {
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}

int main(int argc,char *argv[]) {
	int sock;
	struct sockaddr_in server_addr;
	char message[30];
	int str_len;

	bzero(&server_addr, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = inet_addr(argv[1]);
	server_addr.sin_port = htons(atoi(argv[2]));

	if (connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr))) {
		error_handing("connect() error");
	}
	str_len = read(sock, message, sizeof(message));
	if (str_len == -1)
	{
		error_handing("read() error");
	}
	printf("Message from server :%s \n",message);
	close(sock);
	return 0;
}