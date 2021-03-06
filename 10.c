#include <stdio.h>
#include <string.h>
unsigned char sNonPrintChars[] =
{
	0, 1, 1, 1, 1, 1, 1, 1, 1, 1, //0-9     // stop
	0, 1, 1, 0, 1, 1, 1, 1, 1, 1, //10-19    //'\r' & '\n' are not stop conditions
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, //20-29
	1, 1, 0, 0, 0, 0, 0, 0, 0, 0, //30-39   
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //40-49
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //50-59
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //60-69  
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //70-79
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //80-89
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //90-99
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //100-109
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //110-119
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //120-129
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //130-139
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //140-149
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //150-159
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //160-169
	0, 0, 0, 0, 0, 0, 0, 0, 1, 1, //170-179
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, //180-189
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, //190-199
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, //200-209
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, //210-219
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, //220-229
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, //230-239
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, //240-249
	1, 1, 1, 1, 1, 1             //250-255
};
void PrintStr(FILE *file);
int main()
{
	FILE *fp = fopen("b","a");
	PrintStr(fp);
	return 0;
}
void PrintStr(FILE *file)
{
	char *thestr = "abcdEfgh";

	unsigned int i = 0;
	for (; i < strlen(thestr); i ++) 
	{ 
		if (sNonPrintChars[(unsigned char) thestr[i]]) 
		{   thestr[i] = 0;
			break;
		}

	} 

	if (thestr != NULL)
	{   
		if(file)
			fprintf(file,thestr);
		else
		{
			printf(thestr);
		}   
	}
}
