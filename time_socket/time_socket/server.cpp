#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>



void error_handing(char *message) {
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}

int main(int argc, char * argv[]) {
	int serv_sock;
	int clnt_sock;
	int ret;
	struct sockaddr_in serv_addr;
	struct sockaddr_in clnt_addr;
	socklen_t clnt_addr_size;
	char message[] = "hello world";
	int fd;
	ret = write(fd, message, sizeof(message));
	if (fd == -1)
	{
		printf("open() error\n");
		return -1;
	}
	if (argc != 2) {
		printf("usage :%s<port>\n", argv[0]);
		return -1;
	}
	serv_sock = socket(AF_INET, SOCK_STREAM, 0);
	if (serv_sock == -1)
	{
		printf("socker error\n");
		return -1;
	}
	printf("socker OK\n");
	printf("socket : %d\n", serv_sock);
	//bzero(&serv_addr, sizeof(serv_addr));
	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_addr.sin_port = htons(atoi(argv[1]));
	printf("start bind\n");
	ret = bind(serv_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
	printf("bind ret: %d\n", ret);
	if (ret == -1)
	{
		printf("bind error\n");
		return -1;
	}
	printf("bind OK");
	ret = listen(serv_sock, 5);
	printf("listen ret: %d\n", ret);
	if (ret == -1)
	{
		printf("listen error");
		return -1;

	}
	printf("listen OK\n");
	clnt_addr_size = sizeof(clnt_addr);
	clnt_sock = accept(serv_sock, (struct sockaddr *)&clnt_addr, &clnt_addr_size);
	printf("accept clnt_sock: %d\n", clnt_sock);
	if (clnt_sock == -1) {
		printf("accept error");
		return -1;
	}
	printf("accept OK");
	write(clnt_sock, message, sizeof(message));
	close(clnt_sock);
	close(serv_sock);
	return 0;
}