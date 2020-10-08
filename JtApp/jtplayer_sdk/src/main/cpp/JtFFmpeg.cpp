//
// Created by 13466 on 2020/7/26.
//

#include "JtFFmpeg.h"
#include "include/libavutil/time.h"

JtFFmpeg::JtFFmpeg(JtPlaystatus *playstatus, JtJniCallbackJava *callJava, const char *url) {
    this->pPlayStatus = playstatus;
    this->pJniCallbackJava = callJava;
    this->url = url;
    exit = false;
    pthread_mutex_init(&init_mutex, NULL);
    pthread_mutex_init(&seek_mutex, NULL);
}



void JtFFmpeg::parpared() {

    pthread_create(&decodeThread, NULL, decodeFFmpeg, this);

}




void JtFFmpeg::start() {

    if(NULL == stFFmpegStatus.audio || NULL == stFFmpegStatus.video)
    {
        return;
    }

    //stFFmpegStatus.video->audio = stFFmpegStatus.audio;

    stFFmpegStatus.audio->play();
    stFFmpegStatus.video->play();
    while(pPlayStatus != NULL && !pPlayStatus->exit)
    {
        if(pPlayStatus->seek)
        {
            av_usleep(1000 * 100);
            continue;
        }

        if(stFFmpegStatus.audio->queue->getQueueSize() > 40)
        {
            av_usleep(1000 * 100);
            continue;
        }
        AVPacket *avPacket = av_packet_alloc();
        if(av_read_frame(pFormatCtx, avPacket) == 0)
        {
            if(avPacket->stream_index == audio->streamIndex)
            {
                audio->queue->putAvpacket(avPacket);
            }
            else if(avPacket->stream_index == video->streamIndex)
            {
                video->queue->putAvpacket(avPacket);
            }
            else{
                av_packet_free(&avPacket);
                av_free(avPacket);
            }
        } else{
            av_packet_free(&avPacket);
            av_free(avPacket);
            while(playstatus != NULL && !playstatus->exit)
            {
                if(audio->queue->getQueueSize() > 0)
                {
                    av_usleep(1000 * 100);
                    continue;
                } else{
                    if(!playstatus->seek)
                    {
                        av_usleep(1000 * 100);
                        playstatus->exit = true;
                    }
                    break;
                }
            }
            break;
        }
    }
    if(pCallJava != NULL)
    {
        callJava->onCallComplete(CHILD_THREAD);
    }
    exit = true;

}

void JtFFmpeg::pause() {

}

void JtFFmpeg::resume() {

}

void JtFFmpeg::release() {

}

void JtFFmpeg::seek(int64_t secds){

}


void* JtFFmpeg::decodeFFmpeg(void *data)
{
    JtFFmpeg *pThis = (JtFFmpeg *) data;
    pThis->decodeFFmpegThread();
    pthread_exit(&pThis->decodeThread);
}

void JtFFmpeg::decodeFFmpegThread() {

    pthread_mutex_lock(&init_mutex);
    av_register_all();
    avformat_network_init();
    stFFmpegStatus.pFormatCtx = avformat_alloc_context();

    stFFmpegStatus.pFormatCtx->interrupt_callback.callback = avformat_callback;
    stFFmpegStatus.pFormatCtx->interrupt_callback.opaque = this;

    if(avformat_open_input(&stFFmpegStatus.pFormatCtx, url, NULL, NULL) != 0)
    {
        if(LOG_DEBUG)
        {
            LOGE("can not open url :%s", url);
        }
        pJniCallbackJava->CallbackError(CHILD_THREAD, 1001, "can not open url");
        exit = true;
        pthread_mutex_unlock(&init_mutex);
        return;
    }
    if(avformat_find_stream_info(stFFmpegStatus.pFormatCtx, NULL) < 0)
    {
        if(LOG_DEBUG)
        {
            LOGE("can not find streams from %s", url);
        }
        pJniCallbackJava->CallbackError(CHILD_THREAD, 1002, "can not find streams from url");
        exit = true;
        pthread_mutex_unlock(&init_mutex);
        return;
    }
    for(int i = 0; i < stFFmpegStatus.pFormatCtx->nb_streams; i++)
    {
        if(stFFmpegStatus.pFormatCtx->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_AUDIO)//得到音频流
        {
            if(stFFmpegStatus.audio == NULL)
            {
                stFFmpegStatus.audio = new JtAudio(pPlayStatus, stFFmpegStatus.pFormatCtx->streams[i]->codecpar->sample_rate, callJava);
                stFFmpegStatus.audio->streamIndex = i;
                stFFmpegStatus.audio->codecpar = stFFmpegStatus.pFormatCtx->streams[i]->codecpar;
                stFFmpegStatus.audio->duration = stFFmpegStatus.pFormatCtx->duration / AV_TIME_BASE;
                stFFmpegStatus.audio->time_base = stFFmpegStatus.pFormatCtx->streams[i]->time_base;
                stFFmpegStatus.duration = stFFmpegStatus.audio->duration;
            }
        }
        else if(stFFmpegStatus.pFormatCtx->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_VIDEO)
        {
            if(stFFmpegStatus.video == NULL)
            {
                stFFmpegStatus.video = new JtVideo(pPlayStatus, pJniCallbackJava);
                stFFmpegStatus.video->streamIndex = i;
                stFFmpegStatus.video->codecpar = stFFmpegStatus.pFormatCtx->streams[i]->codecpar;
                stFFmpegStatus.video->time_base = stFFmpegStatus.pFormatCtx->streams[i]->time_base;

                int num = stFFmpegStatus.pFormatCtx->streams[i]->avg_frame_rate.num;
                int den = stFFmpegStatus.pFormatCtx->streams[i]->avg_frame_rate.den;
                if(num != 0 && den != 0)
                {
                    int fps = num / den;//[25 / 1]
                    stFFmpegStatus.video->defaultDelayTime = 1.0 / fps;
                }
            }
        }

    }
    if(stFFmpegStatus.audio != NULL)
    {
        getCodecContext(stFFmpegStatus.audio->codecpar, &stFFmpegStatus.audio->avCodecContext);
    }
    if(stFFmpegStatus.video != NULL)
    {
        getCodecContext(stFFmpegStatus.video->codecpar, &stFFmpegStatus.video->avCodecContext);
    }

    if(pJniCallbackJava != NULL)
    {
        if(pPlayStatus != NULL && !pPlayStatus->exit)
        {
            pJniCallbackJava->CallbackParpared(CHILD_THREAD);
        } else{
            exit = true;
        }
    }
    pthread_mutex_unlock(&init_mutex);
}

int JtFFmpeg::avformat_callback(void *ctx)
{
    JtFFmpeg *fFmpeg = (JtFFmpeg *) ctx;
    if(fFmpeg->pPlayStatus->exit)
    {
        return AVERROR_EOF;
    }
    return 0;
}