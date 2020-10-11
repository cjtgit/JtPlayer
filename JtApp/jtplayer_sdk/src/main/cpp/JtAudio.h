//
// Created by 13466 on 2020/7/27.
//

#ifndef JTAPP_JTAUDIO_H
#define JTAPP_JTAUDIO_H


#include "JtPlaystatus.h"
#include "JtJniCallbackJava.h"
#include "JtQueue.h"

class JtAudio {

public:
    JtAudio(JtPlaystatus *playstatus, int sample_rate, JtJniCallbackJava *callJava);
    ~JtAudio();

    void play();
    int resampleAudio();

    void initOpenSLES();

    int getCurrentSampleRateForOpensles(int sample_rate);

    void pause();

    void resume();

    void stop();

    void release();
    JtQueue *_pJtQueue;
private:
    JtPlaystatus *_pPlayState;
    JtJniCallbackJava *_pCallback;

    int _sampleRate;
    pthread_mutex_t _codecMutex;
    uint8_t _pJtFramBuf;


};


#endif //JTAPP_JTAUDIO_H
