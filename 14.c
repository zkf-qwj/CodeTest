#include <stdio.h>
#include <sys/types.h>
#include <pthread.h> 
#include <signal.h>
void *thrd_func(void *arg);
pthread_t tid;
int main()
{
	int i = 0;
	    if (pthread_create(&tid,NULL,thrd_func,NULL)!=0) {
			        printf("Create thread error!\n");
					        exit(1);
							    }
		    printf("TID in pthread_create function: %u.\n",tid);
			    printf("Main process: PID: %d,TID: %u.\n",getpid(),pthread_self()); 
	while(1){ 
	sleep(1); //race
		printf("this is main process\n");
	}
	return 0;
}
void *thrd_func(void *arg)
{
	int i = 0;
	while(i < 10)
	{
		sleep(1);
		i++;
	}
	kill(getpid(),SIGUSR2);
	while(1)
	{
		printf("-\n");
	}
}
