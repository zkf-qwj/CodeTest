#include <stdio.h>
#include "OSQueue.h"
int main()
{
	OSQueue *line = new OSQueue();
	OSQueueElem *a = new OSQueueElem();
	OSQueueElem *b = new OSQueueElem();
	OSQueueElem *c = new OSQueueElem();
	OSQueueElem d;
	a->SetEnclosingObject((void *)"a");
	b->SetEnclosingObject((void *)"b");
	c->SetEnclosingObject((void *)"c");
	d.SetEnclosingObject((void *)"d");
	line->EnQueue(a);
	line->EnQueue(b);
	line->EnQueue(c);
	line->EnQueue(&d);
	printf("%s,%s,%s,%s\n",(char *)a->GetEnclosingObject(),(char *)b->GetEnclosingObject(),(char *)c->GetEnclosingObject(),(char *)d.GetEnclosingObject());
	printf("a:%d,length:%d\n",a->IsMember(*line),line->GetLength());
	return 0;
}
