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
	int ret;

	if (argc != 3)
	{
		printf("usage :%s<IP><port>\n", argv[0]);
		return -1;
	}
	sock = socket(AF_INET, SOCK_STREAM, 0);
	//bzero(&server_addr, sizeof(server_addr));
	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = inet_addr(argv[1]);
	server_addr.sin_port = htons(atoi(argv[2]));

	ret = connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr));
	printf("connect ret: %d\n", ret);
	printf(" sock: %d\n", sock);
	if (ret == -1)
	{
		printf("connect error\n");
		return -1;
	}
	str_len = read(sock, message, sizeof(message));
	printf("read str_len: %d\n", str_len);
	if (str_len == -1)
	{
		printf("read error\n");
		return -1;
	}
	printf("Message from server :%s \n", message);
	close(sock);
	return 0;
}