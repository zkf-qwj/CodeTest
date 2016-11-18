#include <stdio.h>
#include <stdlib.h>
#include <string.h>
unsigned char        sCaseInsensitiveMask[] =
{
	0, 1, 2, 3, 4, 5, 6, 7, 8, 9, //0-9 
	10, 11, 12, 13, 14, 15, 16, 17, 18, 19, //10-19 
	20, 21, 22, 23, 24, 25, 26, 27, 28, 29, //20-29
	30, 31, 32, 33, 34, 35, 36, 37, 38, 39, //30-39 
	40, 41, 42, 43, 44, 45, 46, 47, 48, 49, //40-49
	50, 51, 52, 53, 54, 55, 56, 57, 58, 59, //50-59
	60, 61, 62, 63, 64, 97, 98, 99, 100, 101, //60-69 //stop on every character except a letter
	102, 103, 104, 105, 106, 107, 108, 109, 110, 111, //70-79
	112, 113, 114, 115, 116, 117, 118, 119, 120, 121, //80-89
	122, 91, 92, 93, 94, 95, 96, 97, 98, 99, //90-99
	100, 101, 102, 103, 104, 105, 106, 107, 108, 109, //100-109
	110, 111, 112, 113, 114, 115, 116, 117, 118, 119, //110-119
	120, 121, 122, 123, 124, 125, 126, 127, 128, 129 //120-129
};
int EqualIgnoreCase(const char* compare, const unsigned int len)
{
	unsigned int Len = 8;
	unsigned int x = 0;
	char *Ptr = "abcdefgh";
	if (len == Len)
	{
		for ( x = 0; x < len; x++){
			printf("--1:%c,--2:%c\n",sCaseInsensitiveMask[(unsigned char ) Ptr[x]],sCaseInsensitiveMask[(unsigned char ) compare[x]]);
			if (sCaseInsensitiveMask[(unsigned char ) Ptr[x]] != sCaseInsensitiveMask[(unsigned char ) compare[x]])
				return 0;
		}
		return 1;
	}
	return 0;
}
int main()
{
	printf("---:%d\n",EqualIgnoreCase("ABCDEFGH",8));
	return 0;
}
