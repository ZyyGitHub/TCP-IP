#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

//³¬Ê±Á¬½Ó
int timeout_connect(const char* ip, int port, int time)
{
	int ret = 0;
	struct sockaddr_in address;
	
	bzero(&address, sizeof(address));
	address.sin_family = AF_INET;
	address.sin_port = htons(port);
	address.sin_addr.s_addr = inet_addr(ip);
	inet_pton(AF_INET, ip, &address.sin_addr);

	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	assert(sockfd >= 0);
	printf("socket : %d\n", sockfd);
	printf("socket Ok\n");
	struct timeval timeout;
	timeout.tv_sec = time;
	timeout.tv_usec = 0;
	socklen_t len = sizeof(timeout);
	ret = setsockopt(sockfd, SOL_SOCKET, SO_SNDTIMEO, &timeout, len);
	assert(ret != -1);
	printf("ret : %d\n", ret);
	printf("setsockopt OK\n");
	ret = connect(sockfd, (struct sockaddr*)&address, sizeof(address));
	if (ret == -1)
	{
		if (errno == EINPROGRESS)
		{
			printf("connecting timeout ,process timeout logic\n");
			return -1;
		}
		printf("errno occur when connecting to server\n");
		return -1;
	}
	return sockfd;
}
int main(int argc, char *argv[])
{
	if (argc <= 2)
	{
		printf("usage:%s ip_address port_number\n", basename(argv[0]));
		return 1;
	}
	const char* ip = argv[1];
	const int port = atoi(argv[2]);
	int sockfd = timeout_connect(ip, port, 10);
	if (sockfd < 0)
	{
		printf("connect fail\n");
		return 1;
	}
	close(sockfd);
	return 0;
}