#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>

#include <sys/stat.h>
#include <fcntl.h>
#include <sys/socket.h>
#define TRANS_LEN 188
#define portnumber 50008

int main(int argc, char *argv[])

{
	int sockfd;
	char buffer[1024];
	struct sockaddr_in server_addr;
	struct hostent *host;
	int fd_out = 0;
	strcpy( buffer,"aaaaaaaaaabbbbbbbbbbcccccccccc----------");
	if(argc<2)

	{
		fprintf(stderr,"Usage:%s hostname \a\n",argv[0]);
		exit(1);

	}

	if((host=gethostbyname(argv[1]))==NULL)

	{
		fprintf(stderr,"Gethostname error\n");

		exit(1);
	}



	if((sockfd=socket(AF_INET,SOCK_STREAM,0))==-1) // AF_INET:Internet;SOCK_STREAM:TCP
	{

		fprintf(stderr,"Socket Error:%s\a\n",strerror(errno));
		exit(1);

	}


	bzero(&server_addr,sizeof(server_addr));
	server_addr.sin_family=AF_INET;          // IPV4

	server_addr.sin_port=htons(portnumber);  // (将本机器上的short数据转化为网络上的short数据)端口号

	server_addr.sin_addr=*((struct in_addr *)host->h_addr); // IP地址

	int sent = 0;

	char temp[1024] = {0};                                                                                                                                                                                       
	int iStrLen = 2016;
	if(connect(sockfd,(struct sockaddr *)(&server_addr),sizeof(struct sockaddr))==-1)
	{

		fprintf(stderr,"Connect Error:%s\a\n",strerror(errno));

		exit(1);
	}
	memcpy(temp,&iStrLen,4);
	send(sockfd,temp,4, 0);
	printf("temp:%s\n",temp);
return 0;


	if ((fd_out = open(argv[2],O_RDONLY)) < 0){
		perror("open file filad!...");
		exit(1);
	}


	printf("Please input char:\n");
	int read_len = 0;
	while(1){
		read_len = read(fd_out,buffer,TRANS_LEN);
		if(read_len <= 0){
			perror("recv end!..");
			exit(1);
		}
		sent = send(sockfd, buffer, read_len, 0);
		if (sent < 0){
			perror("send faild !");
			exit(1);
		}
	}

	close(sockfd);

	exit(0);

}
