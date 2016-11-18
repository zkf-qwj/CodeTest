#include <stdlib.h>
#include <uv.h>
#include <stdio.h>
#include <assert.h>
#include <time.h>

static void timer_cb(uv_timer_t *handle) 
{
	static int count;
	printf("count %d now %d\n", count++, time(NULL));
}

int main(int argc, char *argv[])
{
	int r;
	uv_timer_t timer;
	r = uv_timer_init(uv_default_loop(), &timer);
	if (r != 0){
		return -1;
	}

	if (uv_is_active((uv_handle_t *) &timer)){
		return -1;
	}
	if (uv_is_closing((uv_handle_t *) &timer)){
		return -1;
	}
	r = uv_timer_start(&timer, timer_cb, 1000, 3000);
	r = uv_run(uv_default_loop(), UV_RUN_DEFAULT);
	if (r != 0){
		return -1;
	}
	return 0;
}
