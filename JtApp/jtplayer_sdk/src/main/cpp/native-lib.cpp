#include <jni.h>
#include <string>
#include "JtJniCallbackJava.h"
#include "JtFFmpeg.h"
#include "JtPlaystatus.h"

_JavaVM *javaVM = NULL;

static JtPlaystatus *pStatus = NULL;
static JtFFmpeg *pFFmpegObj = NULL;
static JtJniCallbackJava *pCallbackJavaObj = NULL; //回调Java层的处理函数

//JNI_OnLoad获取虚拟机vm，虚拟机获取环境线程env，返回JNI版本JNI_VERSION_1_4
extern "C"
JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM *vm, void *reserved)
{
    jint result = -1;
    javaVM = vm;
    JNIEnv *env;
    if(vm->GetEnv((void **) &env, JNI_VERSION_1_4) != JNI_OK)
    {
        return result;
    }
    return JNI_VERSION_1_4;
}


extern "C" JNIEXPORT jstring JNICALL
Java_com_cjt_jtplayer_1sdk_JtPlayer_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}

extern "C"
JNIEXPORT void JNICALL
Java_com_cjt_jtplayer_1sdk_JtPlayer_n_1parpared(JNIEnv *env, jobject instance, jstring source_) {
    const char *source = env->GetStringUTFChars(source_, 0);

    // TODO
    if(pFFmpegObj == NULL)
    {
        pStatus = new JtPlaystatus();
        if(pCallbackJavaObj == NULL)
        {
            pCallbackJavaObj = new JtJniCallbackJava(javaVM, env, &instance);
        }
        pCallbackJavaObj->CallbackLoad(MAIN_THREAD, true);
        pFFmpegObj = new JtFFmpeg(pStatus, pCallbackJavaObj, source);
        pFFmpegObj->parpared();
    }
    env->ReleaseStringUTFChars(source_, source);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_cjt_jtplayer_1sdk_JtPlayer_n_1start(JNIEnv *env, jobject instance) {

    // TODO
    if(NULL != pFFmpegObj) {
        pFFmpegObj->start();
    }

}

extern "C"
JNIEXPORT void JNICALL
Java_com_cjt_jtplayer_1sdk_JtPlayer_n_1pause(JNIEnv *env, jobject instance) {

    // TODO
    if(NULL != pFFmpegObj) {
        pFFmpegObj->pause();
    }
}

extern "C"
JNIEXPORT void JNICALL
Java_com_cjt_jtplayer_1sdk_JtPlayer_n_1resume(JNIEnv *env, jobject instance) {

    // TODO
    if(NULL != pFFmpegObj) {
        pFFmpegObj->resume();
    }
}

extern "C"
JNIEXPORT void JNICALL
Java_com_cjt_jtplayer_1sdk_JtPlayer_n_1stop(JNIEnv *env, jobject instance) {

    // TODO
    if(NULL != pFFmpegObj) {
//        pFFmpegObj->
    }
}

extern "C"
JNIEXPORT void JNICALL
Java_com_cjt_jtplayer_1sdk_JtPlayer_n_1seek(JNIEnv *env, jobject instance, jint secds) {

    // TODO
    if(NULL != pFFmpegObj) {
        pFFmpegObj->start();
    }
}