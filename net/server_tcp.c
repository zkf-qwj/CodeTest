#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h> //互联网地址族
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <ctype.h> //toupper （小写转化为大写）
#include <errno.h>
#define TRANS_LEN 1316
int port =50008;

ssize_t  readn(int fd, void *vptr, size_t n); 
/*服务端*/
int main(int argc, char** argv) {

	struct sockaddr_in sin;//struct sockaddr和struct sockaddr_in这两个结构体用来处理网络通信的地址。
	struct sockaddr_in pin;
	int sock_descriptor;//  套接口描述字
	int temp_sock_descriptor;
	int address_size;
	char buf[16384];// 缓冲区大小
	int i,len;
	int file_desc = 0;
	sock_descriptor=socket(AF_INET,SOCK_STREAM,0);//IPV4 TCP协议
	if(sock_descriptor== -1)//申请失败
	{
		perror("call to socket");
		exit(1);
	}

	bzero(&sin,sizeof(sin));// 初始化 然后是设置套接字
	sin.sin_family = AF_INET;//协议族，在socket编程中只能是AF_INET(TCP/IP协议族)
	sin.sin_addr.s_addr=INADDR_ANY;//sin_addr存储IP地址,使用in_addr这个数据结构
	//s_addr按照网络字节顺序存储IP地址
	//                                   //in_addr32位的IPv4地址
	sin.sin_port=htons(port);//存储端口号



	if(bind(sock_descriptor,(struct sockaddr *)&sin,sizeof(sin)) ==-1)
	{
		perror("call to bind");
		exit(1);
	}
	/*int PASCAL FAR listen( SOCKET s, int backlog);
	 * 　　     S：用于标识一个已捆绑未连接套接口的描述字。
	 * 　　     backlog：等待连接队列的最大长度。
	 *      * listen()仅适用于支持连接的套接口，如SOCK_STREAM类型的。
	 *           */
	if(listen(sock_descriptor,20) == -1) //在端口sock_descriptor监听
	{
		perror("call to listen");
		exit(1);
	}

	printf("accepting connections \n");


	temp_sock_descriptor = accept(sock_descriptor,(struct sockaddr *)&pin, &address_size);
	if(temp_sock_descriptor== -1)
	{
		perror("call to accept");
		exit(1);
	}
	recv(temp_sock_descriptor,buf,4,0);
	int a;
	//int *b = &a;
	int *b;
	memcpy(b,buf,4);
	printf("buf:%s,b:%d\n",buf,*b);

	return 0;
	if((file_desc = open("./stream.ts",O_RDWR|O_CREAT|O_APPEND)) < 0){
		perror("open fiald!....");
		exit(1);
	}

	int ret_buf_len = 0;
	int g_div = 0;
	char g_array[3948] = {0};
	int num = 0;
	int n = 0;
	while(1)
	{
#if 1
		ret_buf_len = readn(temp_sock_descriptor,buf,TRANS_LEN);
		printf("---------------------:%d\n",ret_buf_len);
		write(file_desc,buf,TRANS_LEN);
#endif
#if 0
		if (!num){
			n = 0;
			ret_buf_len = recv(temp_sock_descriptor,buf,TRANS_LEN,0);
			if(ret_buf_len == -1)
			{
				perror("call to recv");
				exit(1);
			}
		}
		if(ret_buf_len){
			memcpy(g_array+g_div,buf,ret_buf_len);
			g_div = g_div + ret_buf_len;
		}
		ret_buf_len = 0;
		if (g_div == TRANS_LEN){
			write(file_desc,g_array,TRANS_LEN);
			//printf("--------------------------------:%s\n",g_array);
			g_div = 0;
		}else if (g_div > TRANS_LEN){
			num = g_div / TRANS_LEN;
			g_div = g_div - TRANS_LEN;
			if(n < num){
				//printf("--------------------------------:%s\n",g_array);
				write(file_desc,g_array+TRANS_LEN*n,TRANS_LEN);
				n++;
			}
			num--;
			if(!num){
				memmove(g_array,g_array+n*TRANS_LEN,g_div);
			}
		}
#endif

	}
	close(temp_sock_descriptor);

	return (EXIT_SUCCESS);
}

ssize_t  readn(int fd, void *vptr, size_t n)  
{  
	size_t nleft;  
	ssize_t nread;  
	char *ptr;  

	ptr = vptr;  
	nleft = n;  
	while (nleft > 0) {  
		if ( (nread = read(fd, ptr, nleft)) < 0) {  
			if (errno == EINTR)  
				nread = 0;  /* and call read() again */  
			else  
				return(-1);  
		} else if (nread == 0)  
			break;    /* EOF */  

		nleft -= nread;  
		ptr   += nread;  
	}  
	return(n - nleft);  /* return >= 0 */  
} 





/*
   len =strlen(buf);
   for(i=0;i<len;i++)
   {
   buf[i]= toupper(buf[i]);//将小写字母转化为大写字母
   }
   */
/*int PASCAL FAR send( SOCKET s, const char FAR* buf, int len, int flags);
 * 　　        s：一个用于标识已连接套接口的描述字。
 * 　　        buf：包含待发送数据的缓冲区。
 * 　　        len：缓冲区中数据的长度。
 * 　　        flags：调用执行方式。*/

/*send()   基于链接的发送 TCP
 *          *sendto() 基于无链接到   UDP
 *                   */

/*		if(send(temp_sock_descriptor,buf,len,0) == -1)
		{
		perror("call to send");
		exit(1);
		}
		*/
//		close(temp_sock_descriptor);
