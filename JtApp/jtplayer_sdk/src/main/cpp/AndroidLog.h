//
// Created by 13466 on 2020/7/26.
//

#ifndef JTAPP_ANDROIDLOG_H
#define JTAPP_ANDROIDLOG_H

#include "android/log.h"

#define LOG_DEBUG true

#define LOGD(FORMAT,...) __android_log_print(ANDROID_LOG_DEBUG,"jt",FORMAT,##__VA_ARGS__);
#define LOGE(FORMAT,...) __android_log_print(ANDROID_LOG_ERROR,"jt",FORMAT,##__VA_ARGS__);


#endif //JTAPP_ANDROIDLOG_H


