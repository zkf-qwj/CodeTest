#include <stdio.h>
#include <string.h>
int StrExplode(char inStr[],char *delim,char *outStr[],char *outLen);
int main()
{
	char str[] = "abcdef:add:ee:yt";
	char str2[128] = {'\0'};
	char *a[128] = {'\0'};
	strncpy(str2,str,strlen(str));
	printf("---%s\n",str2);

	return 0;


/*
	char len = 0;
	if (-1 == StrExplode(str,":",a,&len)){
		printf("StrExplode err \n");
		return -1;
	}
	char i = 0;
	for (i = 0; i < len; i++){
		if(NULL != strstr(a[i],"yt"))
			break;
		printf("%s\n",a[i]);
	}
	printf("----%d\n",i);

	return 0;
	*/
}

int StrExplode(char inStr[],char *delim,char *outStr[],char *outLen)
{
	char *p = NULL;
	outStr[0] = strtok(inStr,delim);
	if (NULL == outStr[0]){
		return -1;
	}
	char i = 1;
	while((p = strtok(NULL,delim))){
		outStr[i] = p;
		i++;
	}
	*outLen = i;
	return 0;
}
