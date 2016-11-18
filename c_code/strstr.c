#include <stdio.h>
#include <string.h>
int main()
{
	char a[10] = "abcdef-g";
	char *b = NULL;
	b = a;
	memset(strstr(b,"-"),0,1);
	printf("---:%s,len:%d\n",b,strlen(b));
	return 0;
}
