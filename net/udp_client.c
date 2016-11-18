#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <arpa/inet.h>
#define MAX_MSG_SIZE 1024

int main(int argc,char** argv){
    int skfd,ret,len;
    struct sockaddr_in srvaddr;
    char buf[MAX_MSG_SIZE]={0};
    char sndbuf[MAX_MSG_SIZE]={0};
    struct in_addr addr;

    //创建数据报式套接字skfd
    if(0>(skfd=socket(AF_INET,SOCK_DGRAM,0))){
         perror("Create Error");
         exit(1);
    }

    if(0 == inet_aton(argv[1],&addr)){
         perror("server addr invalid!");
         exit(1);
    }

    bzero(&srvaddr,sizeof(struct sockaddr_in));
    srvaddr.sin_family = AF_INET;
    srvaddr.sin_addr=addr;
    srvaddr.sin_port=htons(atoi(argv[2]));

    //我们的客户端只接收从服务器地址是srvaddr的主机发来的数据
    if(0>(connect(skfd,(struct sockaddr*)&srvaddr,sizeof(struct sockaddr_in)))){
          perror("Connect Error");
          exit(1);
    }
    
    //开始收发数据
    while(1){
        memset(sndbuf,0,MAX_MSG_SIZE);
        len=read(0,sndbuf,MAX_MSG_SIZE);
        ret=sendto(skfd,sndbuf,strlen(sndbuf),0,(struct sockaddr*)&srvaddr,sizeof(struct sockaddr));
        if(ret == len){
              memset(buf,0,MAX_MSG_SIZE);
              //我们已经知道服务器地址信息了，所以最后两个参数为NULL
              ret=recvfrom(skfd,buf,MAX_MSG_SIZE,0,NULL,NULL);
       
              if(ret < 0){
                     perror("read error from server!");
              }else if(ret == 0){
                     perror("server has been closing socket!");
              }else{
                     buf[ret]='\0';
                     printf("From Server:%s\n",buf);
              }
        }
    }
    return 0;
}