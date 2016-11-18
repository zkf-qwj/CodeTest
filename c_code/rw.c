#include <stdio.h>
#include <unistd.h>
#define BUFFSIZE 1024
int main()
{
	int n;
	char buf[BUFFSIZE];
	while ((n = read(STDIN_FILENO,buf,BUFFSIZE)) > 0)
		if (write(STDOUT_FILENO,buf,n) != n)
			printf("err write\n");
	if (n < 0){
		printf("read err\n");
	}
	return 0;
}
