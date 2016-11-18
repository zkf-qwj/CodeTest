#include <stdio.h>
#include <iostream>
class session1
{
public:
	void set_id(int s_id)
	{
		sessid = s_id;
	}
	int get_id()
	{
		return sessid;
	}
	void set_ser(int s_ser)
	{
		server = s_ser;
	}
	int get_ser()
	{
		return server;
	}
private:
	int sessid;
	static int server;
};
int main()
{
	session1 a,b,c;
	a.set_id(1);
	b.set_id(2);
	c.set_id(3);
	a.set_ser(1);
	b.set_ser(2);
	c.set_ser(3);
	printf("a.id:%d,b.id:%d,c.id:%d,a.ser:%d,b.ser:%d,c.ser:%d\n",a.get_id(),b.get_id(),c.get_id(),a.get_ser(),b.get_ser(),c.get_ser());
	return 0;	
}
