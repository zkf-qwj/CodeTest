#!/bin/bash
#gcc -g -o video_test_2 video_test-2.c  -I /home/extend-disk/build/ffmpeg-2.5.2/shared-debug/include -L/home/extend-disk/build/ffmpeg-2.5.2/shared-debug/lib -lavformat -lavcodec -lswresample  -lavutil  -lz -lbz2 -lpthread

#gcc -g  tsidxparse.c -fPIC -shared -o tsidxparse.so   -I /home/extend-disk/build/ffmpeg-2.5.2/shared-debug/include -L/home/extend-disk/build/ffmpeg-2.5.2/shared-debug/lib -lavformat -lavcodec -lswresample  -lavutil  -lz -lbz2 -lpthread

#ggcc -g -o tsidxparse tsidxparse.c -DDEBUG   -I /home/extend-disk/build/ffmpeg-2.5.2/shared-tsidx/include -L/home/extend-disk/build/ffmpeg-2.5.2/shared-tsidx/lib -lavformat -lavcodec -lswresample  -lavutil  -lz -lbz2 -lpthread

#gcc -g -o tsidxparse tsidxparse.c -DDEBUG   -I /home/extend-disk/build/ffmpeg-2.5.2/shared-tsidx/include -L/home/extend-disk/build/ffmpeg-2.5.2/shared-tsidx/lib -lavformat -lavcodec -lswresample  -lavutil  -lz -lbz2 -lpthread

#gcc -g  tsidxparse.c -fPIC -shared -o tsidxparse.so   -I /home/extend-disk/build/ffmpeg-2.5.2/shared-tsidx/include -L/home/extend-disk/build/ffmpeg-2.5.2/shared-tsidx/lib -lavformat -lavcodec -lswresample  -lavutil  -lz -lbz2 -lpthread
#export LD_LIBRARY_PATH=/home/extend-disk/build/ffmpeg-2.5.2/shared-tsidx/lib:/home/extend-disk/build/ffmpeg-1.2.1/shared-debug/lib:$LD_LIBRARY_PATH
#low_version=/home/extend-disk/build/ffmpeg-1.2.1/shared-debug
#high_version=/home/extend-disk/build/ffmpeg-2.5.2/shared-tsidx
#high_version=/home/ll/svn/centos-64/build/ffmpeg/ffmpeg-2.5.2/shared/
high_version=/home/extend-disk/build/libav-1.3.2
g++  -g -o test test.cpp  -L.   tsidxparse.so  -L  $high_version/lib  -lavformat -lavcodec -lswresample  -lavutil  -lz -lbz2 -lpthread 
#-I /home/extend-disk/build/ffmpeg-2.5.2/shared-tsidx/include -L/home/extend-disk/build/ffmpeg-2.5.2/shared-tsidx/lib -lavformat -lavcodec -lswresample  -lavutil  -lz -lbz2 -lpthread  -L.  -ltsidxparse 
export LD_LIBRARY_PATH=/home/extend-disk/build/libav-1.3.2/lib:/home/extend-disk/code/tsidxparse/tsidxparse-cpp:$LD_LBRARY_PATH;

