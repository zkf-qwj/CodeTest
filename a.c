#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define BUF_SIZE 4096

int main(int argc,char *argv[])
{
    struct sockaddr_in servAddr;
    struct hostent * host;
    int sockfd;
    char sendBuf[BUF_SIZE],recvBuf[BUF_SIZE];
    int sendSize,recvSize;

    host=gethostbyname(argv[1]);
    if(host==NULL)
    {
        perror("dns 解析失败");
    }
    servAddr.sin_family=AF_INET;
    servAddr.sin_addr=*((struct in_addr *)host->h_addr);
    servAddr.sin_port=htons(atoi(argv[2]));
    bzero(&(servAddr.sin_zero),8);

    sockfd=socket(AF_INET,SOCK_STREAM,0);
    if(sockfd==-1)
    {
        perror("socket 创建失败");
    }

    if(connect(sockfd,(struct sockaddr *)&servAddr,sizeof(struct sockaddr_in))==-1)
    {
        perror("connect 失败");
    }

    //构建一个http请求
    sprintf(sendBuf,"GET / HTTP/1.1 \r\nHost: %s \r\nConnection: keep-alive \r\n\r\n",argv[1]);
    if((sendSize=send(sockfd,sendBuf,BUF_SIZE,0))==-1)
    {
        perror("send 失败");
    }
    //获取http应答信息
    memset(recvBuf,0,sizeof(recvBuf));
    while(recvSize=recv(sockfd,recvBuf,BUF_SIZE,0))
    {
        printf("%s",recvBuf);
        memset(recvBuf,0,sizeof(recvBuf));
    }

    return 0;
}
