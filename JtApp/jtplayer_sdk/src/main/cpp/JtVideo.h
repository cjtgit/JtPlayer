//
// Created by 13466 on 2020/7/27.
//

#ifndef JTAPP_JTVIDEO_H
#define JTAPP_JTVIDEO_H


#include "JtPlaystatus.h"
#include "JtJniCallbackJava.h"
#include "include/libavutil/frame.h"

class JtVideo {

public:
    JtVideo(JtPlaystatus *playstatus, JtJniCallbackJava *wlCallJava);
    ~JtVideo();

    void play();

    void release();

    double getFrameDiffTime(AVFrame *avFrame);

    double getDelayTime(double diff);
};


#endif //JTAPP_JTVIDEO_H
