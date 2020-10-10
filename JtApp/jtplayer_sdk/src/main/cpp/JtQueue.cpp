//
// Created by 13466 on 2020/10/6.
//

#include "JtQueue.h"


JtQueue::JtQueue(JtPlaystatus *playstatus) {
	this->_pPlayState = playstatus;
	pthread_mutex_init(&_mutex, NULL);
	pthread_cond_init(&_cond, NULL);
}


JtQueue::~JtQueue() {
	clearQueue();
    pthread_mutex_destroy(&_mutex);
    pthread_cond_destroy(&_cond);
};


int JtQueue::pushAvPacket(AVPacket *&avpacket) {
	pthread_mutex_lock(&_mutex);
	if(_queueAvpacket.size() >= 30) {
		pthread_cond_signal(&_cond);
		pthread_mutex_unlock(&_mutex);
		return -1;
	}else {
		_queueAvpacket.push(avpacket);
		pthread_cond_signal(&_cond);
		pthread_mutex_unlock(&_mutex);
		return 0;
	}
}


int JtQueue::popAvPacket(AVPacket** avpacket) {
	pthread_mutex_lock(&_mutex);
	if(_queueAvpacket.empty()) {
		pthread_cond_wait(&_cond, &_mutex);
	}
    AVPacket *tmpPacket =  _queueAvpacket.front();
    if(av_packet_ref(*avpacket, tmpPacket) == 0)
    {
    	_queueAvpacket.pop();
    }
    av_packet_free(&tmpPacket);
    av_free(tmpPacket);
    tmpPacket = NULL;
	pthread_mutex_unlock(&_mutex);
	return 0;
}



int JtQueue::getQueueSize() {
    int queueSize = 0;
    pthread_mutex_lock(&_mutex);
    queueSize = _queueAvpacket.size();
    pthread_mutex_unlock(&_mutex);
    return queueSize;
};



int JtQueue::clearQueue() {
	pthread_mutex_lock(&_mutex);
	if(!_queueAvpacket.empty()) {
        AVPacket *packet = _queueAvpacket.front();
        _queueAvpacket.pop();
        av_packet_free(&packet);
        av_free(packet);
        packet = NULL;
	}
	pthread_mutex_unlock(&_mutex);
	return 0;
}
