// src/com/kdab/training/MyActivity.java
package com.mbruel.test;

import org.qtproject.qt5.android.bindings.QtActivity;
import android.content.Intent;
import java.util.ArrayList;
import android.widget.Toast;
import android.speech.RecognizerIntent;
import android.os.Bundle;
import android.content.ActivityNotFoundException;

public class MyActivity extends QtActivity
{
    private static final int REQ_CODE_SPEECH_INPUT = 1;

    public void popup(String msg)
    {
        try
        {
            Toast.makeText(getBaseContext(), msg, Toast.LENGTH_SHORT).show();
        }
        catch(Exception e)
        {
            String str = "Error:" + e.getMessage();
            NativeFunctions.onError(str);
        }
    }

    public void startSpeechRecogniztion(String language)
    {
        //see laguage codes on link
        //https://github.com/libyal/libfwnt/wiki/Language-Code-identifiers

        //String language =  language;
        Intent speechIntent = new Intent(RecognizerIntent.ACTION_RECOGNIZE_SPEECH);
        speechIntent.putExtra(RecognizerIntent.EXTRA_LANGUAGE_MODEL, RecognizerIntent.LANGUAGE_MODEL_FREE_FORM);
        speechIntent.putExtra(RecognizerIntent.EXTRA_PROMPT, "Speak please");

        speechIntent.putExtra(RecognizerIntent.EXTRA_LANGUAGE_MODEL,language);
        speechIntent.putExtra(RecognizerIntent.EXTRA_LANGUAGE, language);
        speechIntent.putExtra(RecognizerIntent.EXTRA_LANGUAGE_PREFERENCE, language);
        speechIntent.putExtra(RecognizerIntent.EXTRA_ONLY_RETURN_LANGUAGE_PREFERENCE, language);


        startActivityForResult(speechIntent, REQ_CODE_SPEECH_INPUT);
    }

    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data)
    {
        super.onActivityResult(requestCode, resultCode, data);
        switch (requestCode)
        {
            case REQ_CODE_SPEECH_INPUT:
            {
                if (null != data)
                {
                    String strResult = "";
                    ArrayList<String> result = data.getStringArrayListExtra(RecognizerIntent.EXTRA_RESULTS);

                    for (int i=0; i<result.size(); i++)
                    {
                        strResult += result.get(i);
                        strResult += "\n";
                    }
                    NativeFunctions.onResult(strResult);
                }
                break;
            }
        }
    }
}
