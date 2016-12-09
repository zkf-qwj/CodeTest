#!/bin/bash
#g++ -g  tsidxparse.cpp -fPIC -shared -o tsidxparse.so   -I $CNSROOT/build/ffmpeg/ffmpeg-2.5.2/shared/include -L$CNSROOT/build/ffmpeg/ffmpeg-2.5.2/shared/lib -lavformat -lavcodec -lswresample  -lavutil  -lz -lbz2 -lpthread

LIB_PATH=/home/extend-disk/build/libav-1.3.2/
g++ -g  tsidxparse.cpp -fPIC -shared -o tsidxparse.so   -I $LIB_PATH/include -L $LIB_PATH/lib -lavformat -lavcodec -lswresample  -lavutil  -lz -lbz2 -lpthread
