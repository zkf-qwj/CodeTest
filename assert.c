#include <stdio.h>
#define NDEBUG 
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
int main(int argc, const char *argv[])
{
	FILE *fp;
	fp = fopen("test.txt","r");
	assert(fp);
	printf("asdfg\n");
	return 0;
}
