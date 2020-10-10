//
// Created by 13466 on 2020/7/27.
//

#ifndef JTAPP_JTVIDEO_H
#define JTAPP_JTVIDEO_H


#include "JtPlaystatus.h"
#include "JtJniCallbackJava.h"
#include "JtQueue.h"
#include "include/libavutil/frame.h"

class JtVideo {

 public:
    JtVideo(JtPlaystatus *playstatus, JtJniCallbackJava *jtCallJava, JtAudio* jtAudio);
    ~JtVideo();

    void play();

    void release();

    double getFrameDiffTime(AVFrame *avFrame);

    double getDelayTime(double diff);

    int initFfmpegParams(int index, AVCodecParameters *codecParam, AVRational *timebase);
 private:
    JtPlaystatus *_pPlaystatus;
    JtJniCallbackJava *_pCallback;
    JtAudio *_pAudioObj;
    JtQueue *_pVideoQueue;

    //ffmpeg
    AVCodecContext *_pCodecContext;
    AVCodecParameters *_pCodecParam;

    int _FfmpegStreamIndex;
    AVCodecParameters *_FfmpegCodecParam;
    AVRational _FfmpegTimebase;



};


#endif //JTAPP_JTVIDEO_H
