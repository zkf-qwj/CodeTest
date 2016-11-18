#include <stdio.h> 
#include <stdlib.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

#define MAXLINE 80
#define SERV_PORT 3000

int main(void)
{
	struct sockaddr_in servaddr, cliaddr;
	socklen_t cliaddr_len;
	int listenfd, connfd;
	char buf[MAXLINE];
	char str[INET_ADDRSTRLEN];
	int i, n;

	listenfd = socket(AF_INET, SOCK_STREAM, 0);




	int opt = 1;

	setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(SERV_PORT);

	bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr));

	listen(listenfd, 20);

	printf("Accepting connections ...INET_ADDRSTRLEN: %d\n",INET_ADDRSTRLEN);
	while (1) 
	{
		cliaddr_len = sizeof(cliaddr);
		printf("zlj --- server fd: %d,client fd:%d\n",listenfd,connfd);	
		connfd = accept(listenfd,(struct sockaddr *)&cliaddr, &cliaddr_len);

		while(1){
			n = read(connfd, buf, MAXLINE);
			printf("buf:%s,n:%d\n",buf,n);
			write(connfd,buf,strlen(buf));
		}

		while (1) 
		{
			n = read(connfd, buf, MAXLINE);
			//if (n == 0) {
			//	printf("the other side has been closed.\n");
			//	break;
			//}
			//printf("received from %s at PORT %d\n",inet_ntop(AF_INET, &cliaddr.sin_addr, str, sizeof(str)),ntohs(cliaddr.sin_port));
			for (i = 0; i < n; i++)
				buf[i] = toupper(buf[i]);
			write(connfd, buf, n);
			/*
			*/
		}
		//这里故意不关闭socket,或者是在close之前加上一个sleep都可以
		//sleep(5);
		//close(connfd);
	}
}
