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

int main(int argc, char *argv[])
{
struct sockaddr_in addr1,addr2;
ulong l1,l2;
l1 = inet_pton(AF_INET, "192.168.3.114", &addr1.sin_addr);
l2 = inet_pton(AF_INET, "192.168.3.114", &addr2.sin_addr);
memcpy(&addr1, &l1, 4);
memcpy(&addr2, &l2, 4);
printf("%s : %s\n", inet_ntoa(addr1), inet_ntoa(addr2)); //注意这一句的运行结果
printf("%s\n", inet_ntoa(addr1));
printf("%s\n", inet_ntoa(addr2));
return 0;
}
