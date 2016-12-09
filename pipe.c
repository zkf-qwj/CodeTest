#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
int main(int argc, char **argv)
{
	char buf[1024] = {'\0'};
	int fd = 0;
	char *FIFO = "pipe";
	mkfifo(FIFO,0666);
	if (fork() > 0) {
		char s[] = "hello!";
		fd  = open(FIFO,O_WRONLY);
		write(fd,s,sizeof(s));
		close(fd);
	}else {
		fd = open(FIFO, O_RDONLY);
		read(fd,buf,1024);
		printf("%s",buf);
		close(fd);
	}
	return 0;
}
