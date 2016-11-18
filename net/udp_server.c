#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/uio.h>
#include <unistd.h>
#include <netinet/tcp.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#define MAX_MSG_SIZE 1024

int Open(int *fFileDesc,int theType);

int main(int argc,const char *argv[])
{
	int fd_server;
	struct sockaddr_in  server_addr;
	struct sockaddr_in 	client_addr;
	int client_len;
	int ret;
	char buf[MAX_MSG_SIZE] = {0};
	char sendbuf[MAX_MSG_SIZE] = {0};
	memset(&server_addr,0,sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(50000);
	inet_pton(AF_INET, "192.168.3.114", &server_addr.sin_addr);

	if (Open(&fd_server,SOCK_DGRAM) != 0){
		perror("open faild");
		return -1;
	}

	if (bind(fd_server,(struct sockaddr *)&server_addr,sizeof(server_addr)) == -1){
		perror("bind faild");
		return -1;
	}

	while(1){
		ret = recvfrom(fd_server,buf,MAX_MSG_SIZE,0,(struct sockaddr*)&client_addr,&client_len);
		//printf("client addr:port %s:%d\n",inet_ntoa(client_addr.sin_addr),ntohs(client_addr.sin_port));
		if (ret == 0){
			printf("recv data from %s:%d error\n",inet_ntoa(client_addr.sin_addr),ntohs(client_addr.sin_port));
		}else if (ret < 0){
			perror("client has been closing socket!");
		}else
		{
		//	printf("From %s:%d error\n",inet_ntoa(client_addr.sin_addr),ntohs(client_addr.sin_port));
		printf("recv: %s\n",buf);
		memset(sendbuf,0,MAX_MSG_SIZE);
			switch(buf[0]){
				case 'a':
					strcpy(sendbuf,"After u,lady...");
					break;
				case 'b':
					strcpy(sendbuf,"Before u .sir..");
					break;
				case 'c':
					strcpy(sendbuf,"Can u?");
					break;
				default:
					strcpy(sendbuf,"I dont know what u want!");
			}
			sendto(fd_server,sendbuf,strlen(sendbuf),0,(struct sockaddr*)&client_addr,client_len);

		}

		memset(buf,0,MAX_MSG_SIZE);
	}

	return 0;
}
int Open(int *fFileDesc,int theType)
{
	*fFileDesc = socket(PF_INET, theType, 0);
	if (*fFileDesc == -1)
		return (int )errno;
	//	int err = fcntl(*fFileDesc, F_SETFL, O_RDWR | O_NONBLOCK);
	return 0;
}
