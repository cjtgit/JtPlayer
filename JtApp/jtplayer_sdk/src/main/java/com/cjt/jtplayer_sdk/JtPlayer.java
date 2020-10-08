package com.cjt.jtplayer_sdk;

public class JtPlayer {
    static {
        System.loadLibrary("native-lib");
        System.loadLibrary("avcodec-57");
        System.loadLibrary("avdevice-57");
        System.loadLibrary("avfilter-6");
        System.loadLibrary("avformat-57");
        System.loadLibrary("avutil-55");
        System.loadLibrary("postproc-54");
        System.loadLibrary("swresample-2");
        System.loadLibrary("swscale-4");

    }



    public native String stringFromJNI();
    private native void n_parpared(String source);
    private native void n_start();
    private native void n_pause();
    private native void n_resume();
    private native void n_stop();
    private native void n_seek(int secds);


    public JtPlayer()
    {}


}
