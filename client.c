#include <stdio.h> 
#include <stdlib.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#define MAXLINE 80
#define SERV_PORT 50000

int main(int argc, char *argv[])
{
	struct sockaddr_in servaddr;
	char buf[MAXLINE];
	int sockfd, n;
	char *str;

	if (argc != 2) {
		fputs("usage: ./client message\n", stderr);
		exit(1);
	}
	str = argv[1];

	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	inet_pton(AF_INET, "192.168.3.114", &servaddr.sin_addr);
	servaddr.sin_port = htons(SERV_PORT);

	connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
	printf("client:%d\n",sockfd);
	perror("connect");
	printf("errno:%d\n",errno);
	printf("str:%s\n",str);
	while(1){
	write(sockfd, "12345", strlen("12345"));
	n = read(sockfd, buf, MAXLINE);
	printf("Response from server buf:%s\n",buf);
}
/*
	write(STDOUT_FILENO, buf, n);
	write(STDOUT_FILENO, "\n", 1);
*/
	//close(sockfd);
	return 0;
}
