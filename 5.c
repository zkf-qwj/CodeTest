#include <stdio.h>
#include "6.h"
extern int array[MAX];
g_Increment= 5;
int main()
{
	int i;
	int s_pid = 3;
	for (i = 0; i < MAX; i++)
		array[i] = i;
	for (i = 0; i < g_Increment; i++){
		if ( s_pid == array[i] ){
			s_pid += 1;
			i = 0;
		}
	}
	array[g_Increment] = s_pid;
	for(i = 0 ; i < MAX; i++)
		printf("array[%d]:%d\n",i,array[i]);
		printf("s_pid:%d\n",s_pid);
	return 0;
}
