#include <stdio.h>
struct Teacer
{
	int &a;
	int &b;
};
int main()
{
	printf("===>%d\n",sizeof(Teacer));
	return 0;
}
