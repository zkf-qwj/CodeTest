extern "C"
{
#include "libavformat/avformat.h"
#include "libavformat/avio.h"
#include "libavcodec/avcodec.h"
#include "libavutil/base64.h"
#include "libavutil/opt.h"
#include <string.h>
#include <pthread.h>
}
#include  "tsidxparse.h"

pthread_mutex_t avcodec_mut;
static  int parse_avlist(AVStream *vstream, AVStream *astream, av_tp **pp_av_tp_list,int need_a_list);
static void parse_range( const char *buf,int64_t *start_off);
 
//Note user-agent should not be contained in @a otherHeaders,
//otherwise User-Agent will be "default_user-agent""user-agent"


int generateidxfile( char* videofile,
                     //const char* idxfile,
                     char* userAgent,
                     char* otherHeaders,                  
                     video_idx_elem * video_list_elem,
                     int nb_seg,                    
                     int timeout                                            
                   )
{
    int video_index;
    int audio_index;
    int i,j;
   
    int ret =0;
    AVFormatContext *c = NULL;
    int need_a_list =1 ;
    int64_t start_off =0;
retry:
    c = avformat_alloc_context();
    
    
    //set http headers.
    AVDictionary* options = NULL;
    //we add an option save_box in mov_cns demuxer,only when this option
    //set we will save box.
    av_dict_set(&options, "save_box", "1", 0);
    if(userAgent && userAgent[0])
        av_dict_set(&options, "user-agent",userAgent, 0);      // add an entry
    if(otherHeaders && otherHeaders[0])
    {
        av_dict_set(&options, "headers",otherHeaders,0);
        if(strstr(otherHeaders,"Range"))
        {
            parse_range(otherHeaders,&start_off);
        }
     }
    if(start_off >0)
    {
        char start_off_str[128];
        sprintf(start_off_str,"%ld",start_off);
        av_dict_set(&options,"range_start",start_off_str,0);
    }
    if(nb_seg >0)
    {   
        char nb_seg_str[128]={'\0'};
        sprintf(nb_seg_str,"%d",nb_seg); 
        av_dict_set(&options,"nb_segment",nb_seg_str,0);
    }
    if(timeout >0)
    {
        char timeoutstr[256]={'\0'};
        sprintf(timeoutstr,"%d",timeout*STOUS);
        av_dict_set(&options,"con_timeout",timeoutstr,0);
    }
  
    
    if( (ret=avformat_open_input( &c, videofile, NULL, &options) )<0 )
    {                     
       
        goto finish;
    }
    fprintf(stdout,"defore duration:%lld\n",c->duration);

    if ( (ret=avformat_find_stream_info(c,NULL)) < 0) {
        
      
        goto finish;
    }
    
    fprintf(stdout,"after duration:%lld\n",c->duration);
    
  
    if( !c->pb->seekable && strstr(c->iformat->name,"ts") == NULL && 
        strstr(c->iformat->name,"hls") == NULL && strstr(c->iformat->name,"applehttp") == NULL )    
    {
       
        ret =-4;
        goto finish;      
    }
    
    video_index = -1;
    audio_index = -1;
    for (i = 0; i < c->nb_streams && (video_index < 0 || audio_index < 0); i++) {
        //fprintf(stdout, "the codec type is %d\n", (int)c->streams[i]->codec->codec_type);
        switch (c->streams[i]->codec->codec_type) {
        case AVMEDIA_TYPE_VIDEO:
            video_index = i;
            c->streams[i]->discard = AVDISCARD_NONE;
            break;
        case AVMEDIA_TYPE_AUDIO:
            audio_index = i;
            break;
        default:
            c->streams[i]->discard = AVDISCARD_ALL;
            break;
        }
    }
    
     if(video_index >= 0 )
    {
       // fprintf(stdout, "video index is %d\n", video_index);
       // fprintf(stdout, "video entrys number %d\n", c->streams[video_index]->nb_index_entries);
        av_tp *p_list = NULL;
        int size = parse_avlist(video_index >= 0 ? c->streams[video_index] : NULL,
                                audio_index >= 0 ? c->streams[audio_index] : NULL,
                                &p_list ,need_a_list);
        if(size <= 0)
        {
            goto finish;           
            
        }
              
        video_list_elem->frame_list = p_list;
        video_list_elem->frame_list_n = size;    
              
    }
    
    video_list_elem->success =1;    
    
finish:
    av_dict_free(&options);
    if(c != NULL )
    {
        avformat_close_input(&c);         
    }

    return ret;
}


int parse_avlist(AVStream *vstream, AVStream *astream, av_tp **pp_av_tp_list,int need_alist)
{
    int i=0;
    if(!pp_av_tp_list)
        return 0;
    if( (!vstream || vstream->nb_index_entries <= 0) && (!astream || astream->nb_index_entries <= 0))
        return 0;

    if(!vstream || vstream->nb_index_entries <= 0)
    {
        av_tp *p_list;
        *pp_av_tp_list = p_list =(av_tp*) malloc(sizeof(av_tp) *astream->nb_index_entries);
        double unit =  (1000.0 * (double)astream->time_base.num/(double)astream->time_base.den);
        for(i = 0; i < astream->nb_index_entries; ++i)
        {
            p_list[i].vp = 0;
            p_list[i].vt = 0;
            p_list[i].ap = astream->index_entries[i].pos;
            p_list[i].at = (int64_t)((double)astream->index_entries[i].timestamp * unit);
        }
        return astream->nb_index_entries;
    }

    if(!astream || astream->nb_index_entries <= 0 || !need_alist)
    {
        int nkeyframes = 0;
        
        for(i = 0; i < vstream->nb_index_entries; ++i)
            if(vstream->index_entries[i].flags & AVINDEX_KEYFRAME)
                ++nkeyframes;
        av_tp *p_list = NULL;
        *pp_av_tp_list = p_list =(av_tp*) malloc(sizeof(av_tp) *nkeyframes);
        double unit =  (1000.0 * (double)vstream->time_base.num/(double)vstream->time_base.den);
        int index = 0;
        for(i = 0; i < vstream->nb_index_entries; ++i)
        {
            if(vstream->index_entries[i].flags & AVINDEX_KEYFRAME)
            {
                p_list[index].vp = vstream->index_entries[i].pos;
                p_list[index].vt = (int64_t)((double)vstream->index_entries[i].timestamp * unit);
                p_list[index].ap = 0;
                p_list[index].at = 0;
                ++index;
            }
        }
        return nkeyframes;
    }

    int nkeyframes = 0;
    for(i = 0; i < vstream->nb_index_entries; ++i)
        if(vstream->index_entries[i].flags & AVINDEX_KEYFRAME)
            ++nkeyframes;
    av_tp *p_list;
    *pp_av_tp_list = p_list = (av_tp*)malloc(sizeof(av_tp) * nkeyframes);
    double vunit =  (1000.0 * (double)vstream->time_base.num/(double)vstream->time_base.den);
    double aunit =  (1000.0 * (double)astream->time_base.num/(double)astream->time_base.den);
    int index = 0;
    int index_match = 0;
    for(i = 0; i < vstream->nb_index_entries; ++i)
        if(vstream->index_entries[i].flags & AVINDEX_KEYFRAME)
        {
            int64_t vt = (int64_t)((double)vstream->index_entries[i].timestamp * vunit);
            int j;
            for(j = index_match; j < astream->nb_index_entries; ++j)
            {
                int64_t at = (int64_t)((double)astream->index_entries[j].timestamp * aunit);
                if(at >= vt)
                    break;
            }
            if(j < 1)
                index_match = j;
            else if(j >= astream->nb_index_entries)
                index_match = j - 1;
            else
            {
                index_match = j;
            }

            p_list[index].vp = vstream->index_entries[i].pos;
            p_list[index].vt = (int64_t)((double)(vstream->index_entries[i].timestamp ) * vunit);
            p_list[index].ap = astream->index_entries[index_match].pos;
            p_list[index].at = (int64_t)((double)(astream->index_entries[index_match].timestamp ) * aunit);
            ++index;
        }

    return nkeyframes;
}


void tsidxparse::do_exit()
{
    av_lockmgr_register(NULL);
    avformat_network_deinit();
}



static int lockmgr(void **mtx, enum AVLockOp op)
{
	int ret;
	switch(op) {
		case AV_LOCK_CREATE:
		ret = pthread_mutex_init(&avcodec_mut,NULL);
		if(!ret)
			return 0;
		return 1;
		
	case AV_LOCK_OBTAIN:
		return pthread_mutex_lock(&avcodec_mut);
	case AV_LOCK_RELEASE:
		return pthread_mutex_unlock(&avcodec_mut);
	case AV_LOCK_DESTROY:
		pthread_mutex_destroy(&avcodec_mut);
		return 0;
	}
	
	return 1;
}

void tsidxparse::clear_video_idx_elem()
{
    int i=0;
    //for(i=0;i<video_list_n;i++)
    {
        av_freep(&( (this->video_idx).mux));
        av_freep(&((this->video_idx).location));
        av_freep(&((this->video_idx).frame_list));
        av_freep(&((this->video_idx).stream_info));
        av_freep(&((this->video_idx).meta_data));
    }
    
}


/*
* @return -1 param err, 
*
*/


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

static void parse_range( const char *buf,int64_t *start_off)
{
   
    
    const char *slash;
    const char *p = strstr(buf,"bytes");
   
    if (p && !strncmp(p, "bytes=", 6)) {
        p     += 6;
        (*start_off) = strtoll(p, NULL, 10);       
    }
    return ;
}

void tsidxparse::clear_KeyFrameGroup()
{
    if(list && list->nb_keyframe)
    {
        int i=0;
        av_freep(&(list->keyframes));
        av_freep(&list);
    }
    
}

KeyFrameGroup* tsidxparse::get_keyframe_list()
{
    int ret =0,j=0;
   
    do {
        if( ( ret= generateidxfile(this->filename,this->useragent,this->otherHeaders,&(this->video_idx),this->nb_seg,this->con_limit_time)) <0 ) 
        {  
            this->video_idx.err =ret;
            this->video_idx.retry --; 
        }
        
       
   }while (ret && (video_idx.retry>=0) );
   
   
   if(this->video_idx.success)
   {
        this->list = (struct KeyFrameGroup*)av_mallocz(sizeof(struct KeyFrameGroup));
       
        if( this->video_idx.frame_list_n >0 )
        {              
            av_tp *p_list = this->video_idx.frame_list;
            this->list->nb_keyframe = this->video_idx.frame_list_n;

            struct   KeyFrameNode* keyframes =(struct   KeyFrameNode*) av_mallocz(sizeof(struct   KeyFrameNode) *list-> nb_keyframe);
            list->keyframes = keyframes;

            for(j=0;j<video_idx.frame_list_n;j++)
            {            
                   
                list->keyframes[j].pos = p_list[j].vp ;
                if(j== 0)
                {
                    list->keyframes[j].pos =list->keyframes[j].pos;
                }
                list->keyframes[j].timestamp = p_list[j].vt;               
            }             
         
          return this->list;        
        }
   }
   
   return NULL;
}



tsidxparse::~tsidxparse()
{
    void clear_video_idx_elem(); 
    do_exit();
    clear_KeyFrameGroup();
}


tsidxparse::tsidxparse()
{
    filename = NULL;    
    memset(&video_idx,0,sizeof(video_idx_elem));
    list = NULL;    
    memset(useragent,0,sizeof(useragent));
    memset(otherHeaders,0,sizeof(otherHeaders));   
    nb_seg =0;
   
    con_limit_time =5;    
}


void tsidxparse::initialize()
{
    av_register_all();  
}

bool tsidxparse::configure(char *filename, int con_limit_time,int retry_con,char* useragent_p,char *otherHeader_p,int nb_segment)
{
    if(!filename || !strlen(filename))
    {
        return false;
    }else
        this->filename = filename;
    
    
    if(useragent_p && strlen(useragent_p))
    {
         strcpy(this->useragent,useragent_p);
    }
    
    
    if(otherHeader_p != NULL && strlen(otherHeader_p))
    {
       strcpy(this->otherHeaders,otherHeader_p);
    }
    
    if(nb_segment >0)
    {
        this->nb_seg = nb_segment;
    }
  
    if(retry_con >=0)
        this->retry_con = retry_con;
        
    if(con_limit_time >0)
    {
        this->con_limit_time = con_limit_time;
    }
         
  
   this->video_idx.retry = this->retry_con;
    
   
   avformat_network_init();
    
    if (av_lockmgr_register(lockmgr)) {			
		return false;
	}  
   
}




#ifdef DEBUG

int main()
{
    
   // char file[1024]="http://220.181.61.212/ipad?file=/197/129/86XGBVuMovhFO9cwYvNLqJ.mp4&start=0&end=10.479&sig=4AzUZJBGEW9H9kUy41S-89xFNkkgF8mx&ch=my&cateCode=192100&vid=80248025&uid=b2ea14b37a35203564aa602c436418ba&plat=6&pt=5&prod=app&pg=1&eye=0&ugcode2=&cv=4.7.1";
    //Range: bytes=564-31722368\r\n
   // int tsidxparse(char *filename, int con_limit_time,int retry_con,char* useragent_p,char *otherHeader_p,int nb_segment,struct KeyFrameGroup*list)
    //char file[1024]="http://192.168.1.211:8080/yulong-cbr.ts";
    //char file[1024]="http://192.168.1.15:8200/sfetch/test1/0";
    char file[1024]="http://192.168.100.71:8080/test.ts";
    //videoidxparse(file,1,2,"","Range: bytes=752-31722368\r\n",0);
    struct KeyFrameGroup*list = (struct KeyFrameGroup*)av_malloc(sizeof(struct KeyFrameGroup));
    tsidxparse(file,0,0,"","Range: bytes=42525611-328616836\r\n",4,list);
    //tsidxparse(file,0,0,"","Range: bytes=31722368-63465792\r\n",4,list);
    //tsidxparse(file,0,0,"","Range: bytes=63465792-95209592\r\n",4,list);
    //tsidxparse(file,0,0,"","",4,list);
    print(list);
    clear_list(list);
    list = NULL;
    return 0;
}
#endif
