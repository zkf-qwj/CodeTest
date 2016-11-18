#include <stdio.h>
int main()
{
	const	int a = 10;
	int *p = (int *)&a;
	printf("a===>%d,%x\n",a,&a);
	int b = 11;
	p = &b;
	printf("a===>%d,%x\n",a,&a);
	printf("Hello.....\n");

	return 0;
}

