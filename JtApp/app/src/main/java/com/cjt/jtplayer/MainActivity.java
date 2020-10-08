package com.cjt.jtplayer;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.widget.TextView;

import com.cjt.jtplayer_sdk.JtPlayer;

public class MainActivity extends AppCompatActivity {

    // Used to load the 'native-lib' library on application startup.

    private JtPlayer demo;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        demo = new JtPlayer();
        // Example of a call to a native method
        TextView tv = findViewById(R.id.sample_text);
        tv.setText(demo.stringFromJNI());
    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */

}
