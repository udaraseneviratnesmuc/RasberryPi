package com.hms.beyondm.rpiinteractiveclient;

import android.os.Environment;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.TextView;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;

public class FileReading extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_file_reader);
    }

    public void readFileEvent(View view){
        TextView availableText = (TextView) findViewById(R.id.textView);
        availableText.setText(readFromFile());
    }

    public String readFromFile(){
        // Get the directory for the user's public pictures directory.
        final File path =
                Environment.getExternalStoragePublicDirectory
                        (
                                //Environment.DIRECTORY_PICTURES
                                Environment.DIRECTORY_DCIM
                        );

        try
        {
            final File file = new File(path, "test");
            StringBuilder text = new StringBuilder();

            BufferedReader br = new BufferedReader(new FileReader(file));
            String line;

            while ((line = br.readLine()) != null) {
                text.append(line);
                text.append('\n');
            }
            br.close();

            return text+"";

        }
        catch (IOException e)
        {
            Log.e("Exception", "File write failed: " + e.toString());

            return null;
        }
    }
}
