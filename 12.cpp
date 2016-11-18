#include <stdio.h>
#include <iostream>
class A
{
	public:
		A(){
			delete [] buf;
		}
	char *buf;
};
int main()
{
	A a;
}

