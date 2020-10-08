//
// Created by 13466 on 2020/7/27.
//

#include "JtAudio.h"
#include "include/libavutil/mem.h"


JtAudio::JtAudio(JtPlaystatus *playstatus, int sample_rate, JtJniCallbackJava *callJava) {
    _pPlayState = playstatus;
    _sampleRate = sample_rate;
    _pCallback = callJava;
    _pJtQueue = new JtQueue(_pPlayState);
    _pJtFramBuf = (uint8_t *)av_malloc(sample_rate * 2 * 2);
    pthread_mutex_init(&_codecMutex, NULL);
}
