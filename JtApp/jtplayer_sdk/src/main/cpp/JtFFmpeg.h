//
// Created by 13466 on 2020/7/26.
//

#ifndef JTAPP_JTFFMPEG_H
#define JTAPP_JTFFMPEG_H

#include "pthread.h"

#include "JtPlaystatus.h"
#include "JtJniCallbackJava.h"
#include "include/libavcodec/avcodec.h"
#include "JtAudio.h"
#include "JtVideo.h"


extern "C"
{
#include "include/libavformat/avformat.h"
#include <include/libavutil/time.h>
};


typedef struct {
    AVFormatContext *pFormatCtx = NULL;
    JtAudio *audio = NULL;
    JtVideo *video = NULL;
    int duration = 0;
}FFmpegStatus;


class JtFFmpeg {

public:
    JtFFmpeg(JtPlaystatus *playstatus, JtJniCallbackJava *callJava, const char *url);
    ~WlFFmpeg();

    void parpared();

    void start();

    void pause();

    void resume();

    void release();

    void seek(int64_t secds);

    int getCodecContext(AVCodecParameters *codecpar, AVCodecContext **avCodecContext);

    void decodeFFmpegThread();


private:
    JtPlaystatus* pPlayStatus;
    JtJniCallbackJava* pJniCallbackJava;
    const char* url = NULL;
    bool exit = false;
    pthread_mutex_t init_mutex;
    pthread_mutex_t seek_mutex;

    pthread_t decodeThread;

    FFmpegStatus stFFmpegStatus;

    static void* decodeFFmpeg(void *);
    static int avformat_callback(void *ctx);
};


#endif //JTAPP_JTFFMPEG_H
