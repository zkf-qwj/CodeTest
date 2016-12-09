#include  "tsidxparse.h"
#include <stdio.h>
#include <stdlib.h>


void print(struct KeyFrameGroup*list)
{
    if(!list || !list->nb_keyframe)
    {
        fprintf(stdout,"keyframe is null");
    }
    
    int i=0;
    for(i=0;i<list->nb_keyframe;i++)
    {
        fprintf(stdout,"pos:%ld,time:%ld\n",list->keyframes[i].pos,list->keyframes[i].timestamp);
    }
}

int main()
{
    char file[1024]="http://192.168.1.211:8080/test.ts";
     struct KeyFrameGroup*list = NULL;
//(struct KeyFrameGroup*)malloc(sizeof(struct KeyFrameGroup));
   //  struct   KeyFrameNode* keyframes =(struct   KeyFrameNode*) malloc(sizeof(struct   KeyFrameNode) *6);
    //        list->keyframes = keyframes;
    tsidxparse::initialize();
    tsidxparse *tsidxparse_ins = new tsidxparse();
    tsidxparse_ins->configure(file,1,0,0,"Range: bytes=32307523-328616836\r\n",1);
    list =tsidxparse_ins->get_keyframe_list();
   // tsidxparse(file,0,0,"","Range: bytes=32307523-328616836\r\n",6,list);
    if(list)
    print(list);
    delete tsidxparse_ins;
    return 0;
}
