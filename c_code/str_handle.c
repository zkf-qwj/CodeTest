#include <stdio.h>
#include <string.h>
#include <stdlib.h>
char *str_replace(char *dest,char *src);
int main()
{
	char *fullstr = "trackID=1 \0";                                                                                                  
	char *requeststr = "SETUP rtsp://10.255.43.3:803/camera/91ed64ff77c32bae794e966d5548dad6.ts/* RTSP/1.0\r\nCSeq: 2\r\nUser-Agent: EVM RTSP Client v1.0\r\nTransport: MP2T\0";
#if 1
	char newstr[2048] = {0};
	char *start = NULL,*end = NULL;
	start = strstr(requeststr,"*");
	end = strstr(requeststr,"RTSP");
	int len = 0;
	len = start - requeststr;
	strncpy(newstr,requeststr,len);
	strncpy(newstr+len,fullstr,strlen(fullstr));
	strncpy(newstr+len+strlen(fullstr),end,strlen(end));
	requeststr = newstr;
	printf("newstr:%s\n",requeststr);
#endif
	return 0;
}
