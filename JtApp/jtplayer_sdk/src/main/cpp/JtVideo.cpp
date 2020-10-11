//
// Created by 13466 on 2020/7/27.
//

#include "JtVideo.h"

JtVideo::JtVideo(JtPlaystatus *playstatus, JtJniCallbackJava *jtCallJava, JtAudio* jtAudio) {
    _pPlaystatus = playstatus;
    _pCallback = jtCallJava;
    _pAudioObj = jtAudio;
    if(NULL == _pVideoQueue) {
        _pVideoQueue = new JtQueue(_pPlaystatus);
    }

}


JtVideo::~JtVideo() {
	if(_pVideoQueue) {
		delete _pVideoQueue;
	}
}


int JtVideo::initFfmpegParams(int index, AVCodecParameters *codecParam, AVRational *timebase) {
    _FfmpegStreamIndex = index;
    _FfmpegCodecParam = codecParam;
    _FfmpegTimebase = timebase;
}

int JtVideo::pushVideoAvPacket(AVPacket *&avpacket) {
    if(NULL != _pVideoQueue && NULL != avpacket) {
        return _pVideoQueue->pushAvPacket(avpacket);
    }
    return -1;
}

void JtVideo::play() {


}


void JtVideo::release() {

}


double JtVideo::getFrameDiffTime(AVFrame *avFrame) {

}


double JtVideo::getDelayTime(double diff) {

}
