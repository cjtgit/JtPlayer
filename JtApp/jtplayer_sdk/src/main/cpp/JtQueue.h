//
// Created by 13466 on 2020/10/6.
//

#ifndef JTAPP_JTQUEUE_H
#define JTAPP_JTQUEUE_H

extern "C"{
#include <include/libavutil/imgutils.h>
#include <include/libavutil/samplefmt.h>
#include <include/libavutil/timestamp.h>
#include <include/libavformat/avformat.h>
}
#include "pthread.h"
#include "JtPlaystatus.h"
#include <vector>
#include <queue>


class JtQueue {

public:
    JtQueue(JtPlaystatus* playstatus);
    ~JtQueue();
	int pushAvPacket(AVPacket *&avpacket);
	int popAvPacket(AVPacket** avpacket);
	int getQueueSize();
	int clearQueue();
private:
    JtPlaystatus *_pPlayState = NULL;
	pthread_mutex_t _mutex;
	pthread_cond_t _cond;
	std::queue<AVPacket *> _queueAvpacket;
	
};


#endif //JTAPP_JTQUEUE_H
