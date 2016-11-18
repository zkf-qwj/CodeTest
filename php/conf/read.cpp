#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE *fp = NULL;

int main()
{
	fp = fopen("test", "r");
	if(NULL == fp){
		printf("open failed\n");
		return 0;
	}

//	char szMsg[14] = {0};

	int iValue = 0;
	char buf[10] = {0};
	fread(buf, 1, 4, fp);
	memcpy((char *)&iValue,buf,4);
	fread(buf, 1, iValue, fp);

	printf("read value from test file : %d,buf:%s\n", iValue,buf);
	fclose(fp);

	return 0;
}
