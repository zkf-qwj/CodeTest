#include <stdio.h>
#include <string.h>
#define kPathDelimiterString "/"
#define kPathDelimiterChar '/'
int main()
{
	char *a = "1234567";
	char b[20] = {0};
	strcpy(b,a);
	printf("----:%s\n",b);
	printf("%s,%c",kPathDelimiterString,kPathDelimiterChar);
	return 0;
}
