#include <stdio.h>
#include <stdio.h>
#include "ev.h"
	ev_timer timer_w;
	struct ev_loop *main_loop;
void handleTimeout(struct ev_loop *main_loop,ev_timer *timer_w,int e)
{
	printf("-----------------\n");
}
void start(){
	printf("run_lev: Start libev \n");
	main_loop = ev_default_loop(0);                                                                                                                                                                              
	ev_init(&timer_w,handleTimeout);
	ev_timer_set(&timer_w,0,3);
	ev_timer_start(main_loop,&timer_w);
	ev_run(main_loop,0);

}
int main()
{
	start();
	return 0;
}
