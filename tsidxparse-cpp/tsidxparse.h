#ifndef _TSIDXPARSE_H
#define _TSIDXPARSE_H
extern "C"
{
#include <stdint.h>
}

#define MAX_LEN         40960
#define MAX_BUF_LEN     4096
#define COMM_BUF_LEN    1024
#define STOUS 1000000


struct KeyFrameNode
{
    int64_t pos;
    int64_t timestamp;
};
struct KeyFrameGroup{
 struct   KeyFrameNode* keyframes;
 int      nb_keyframe;
};


typedef struct _av_tp {
    int64_t vp;   /*video pos*/
    int64_t vt;   /*video time*/
    int64_t ap;   /*audio pos*/
    int64_t at;   /*audio time*/
} av_tp;


typedef struct video_idx_elem{
    char    *mux;
    char    *location;
    char    *meta_data;    
    char    *stream_info;
    av_tp   *frame_list;
    int     frame_list_n;
    int64_t frame_list_size;
    int64_t data_len;
    int     retry; 
    int     success;  
    int     err;    
}video_idx_elem;


class tsidxparse
{
public:
    tsidxparse();
    ~tsidxparse();
    bool configure(char *filename, int con_limit_time,int retry_con,char* useragent_p,char *otherHeader_p,int nb_segment);
    KeyFrameGroup*get_keyframe_list();
    static void initialize();
    
protected:    
    char *filename;
    int  con_limit_time;
    int  retry_con;
    char useragent[COMM_BUF_LEN];
    char otherHeaders[COMM_BUF_LEN];
    
private:
      
    video_idx_elem   video_idx;   
    int             nb_seg; 
   
    struct KeyFrameGroup*list;
    
    void clear_video_idx_elem();
    void do_exit();
    void clear_KeyFrameGroup();
    
};



#endif

