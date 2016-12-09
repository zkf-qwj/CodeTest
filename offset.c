#include <stdio.h>
typedef struct
{
	void *x;
	void *y;
	void *z;
} Point;
#define offsetof(TYPE,MEMBER) ((size_t) &(((TYPE*)0)->MEMBER))
#define list_entry(ptr, type, member)  ((type *)((char *)(ptr)-(unsigned long)(&((type *)0)->member)))
void test1()
{
	int x = (size_t) &((Point*)0)->x;
	int y = (size_t) &((Point*)0)->y;
	int z = (size_t) &((Point*)0)->z;
	printf("offset: x = %d,y = %d,z = %d\n",x,y,z);
}
void test2()
{
	printf("Point.x offset = %d\n",offsetof(Point,x));
	printf("Point.y offset = %d\n",offsetof(Point,y));
	printf("Point.z offset = %d\n",offsetof(Point,z));
}
int main()
{
	Point p1;
	int a = 10,b = 5;
	char aa[200];
	p1.z = (void *)aa;
	p1.x = (void *)&b;
	printf("p1 add:%p\n",&p1);
	
	//test1();
	printf("\n");
	//test2();
	printf("aa:%p\n",&aa);
	printf("p1.z addr:%p\n",&(p1.z));
	void *pos = NULL;
	pos = (p1.z);
	Point *p2 = list_entry(&pos,Point,z);
	int *c = (int *)(p2->x);
	printf("Point.z offset = %d\n",*c);
	return 0;
}

