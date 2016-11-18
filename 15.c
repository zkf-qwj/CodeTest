#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <sys/types.h>
int main()
{
	pid_t fpid; //fpid表示fork函数返回的值  
	int count=0;  
	int i = 0;                                                                                                                                                                                                   
	fpid=fork();   
	if (fpid < 0)   
		printf("error in fork!");   
	else if (fpid == 0) {  
		printf("i am the child process, my process id is %d\n",getpid());   
		while(i < 10) 
		{   
			sleep(1);
			i++;
		}   
		kill(getppid(),SIGUSR2);
		kill(getpid(),SIGUSR2);
		while(1)
		{   
			printf("-\n");
		} 
	}  
	else {
		while(1){
			sleep(1);
			printf("i am the parent process, my process id is %d\n",getpid());   
		}
	}  
	printf("统计结果是: %d\n",count);  
	return 0;
}
