#include <stdio.h>
#include <stdlib.h>
enum {  
	kVPos = 0,
	kSPos,
	kTPos,
	kOPos
};

enum {
	kV = 1 << kVPos, 
	kS = 1 << kSPos,
	kT = 1 << kTPos,
	kO = 1 << kOPos,
	kAllReq = kV | kS | kT | kO
};
int main()
{
	printf("--:%d,%d,%d,%d\n",kVPos,kSPos,kTPos,kOPos);
	printf("--:%d,%d,%d,%d,all:%d\n",kV,kS,kT,kO,kAllReq);
while(1);
	return 0;
}
