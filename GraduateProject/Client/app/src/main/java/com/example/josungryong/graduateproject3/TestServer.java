package com.example.josungryong.graduateproject3;

import android.os.AsyncTask;
import android.os.Bundle;
import android.support.annotation.Nullable;
import android.support.v7.app.AppCompatActivity;
import android.util.Log;
import android.view.View;

import com.example.josungryong.graduateproject3.Main_Fragment.WordItemData;
import com.ramotion.foldingcell.FoldingCell;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.UnsupportedEncodingException;
import java.net.URL;
import java.net.URLConnection;
import java.util.ArrayList;
import java.util.logging.FileHandler;

/**
 * Created by josungryong on 2017-03-15.
 */

public class TestServer extends AppCompatActivity {

    public static String[] listDB; // DB의 결과를 받아오는 변수

    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.test_layout);

        final FoldingCell fc = (FoldingCell) findViewById(R.id.folding_cell);

        fc.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                fc.toggle(false);
            }
        });
        //new HttpTask().execute();
    }

    // PHP 검색 쿼리 보내는 class
    class HttpTask extends AsyncTask<String,Void,String> {
        /* Bitmap bitmap , String image는 전역변수 */
        protected String doInBackground(String... params) {
            // TODO Auto-generated method stub
            try{
                String urlPath = "http://58.142.149.131/grad/transfer_test.php";

                String data = null;
                //String data = "lat=" + latitude;
                //data += "&lng=" + longitude;

                URL url = new URL(urlPath);
                URLConnection conn = url.openConnection();

                conn.setDoOutput(true);
                OutputStreamWriter wr = new OutputStreamWriter(conn.getOutputStream());
                Log.i("connectionTest" , "dd"+conn.getURL());
                // 문자열 전송

                wr.write("jjj");
                wr.flush();

                BufferedReader reader = new BufferedReader(new InputStreamReader(conn.getInputStream()));

                StringBuilder sb = new StringBuilder();
                String CheckNull = "0";
                String line = null;

                while((line = reader.readLine()) != null) {
                    sb.append(line);
                    Log.i("testreader" , "Test:"+line);
                    break;
                }
                Log.i("testtesttest" , "Test:" + sb.toString());
                CheckNull = sb.toString();
                Log.d("deburgquery", "testConnection:" + sb.toString()); // 1/1360872253931928/37.5619148/126.8570243/368000/computer/good job/1482 Gayang-dong/Japanese/Rice/1360872253931928_2016_12_05_02_14_2////

                /*
                if(sb.toString() != "") {
                    Log.d("디버깅123", "sb.toString:"+sb.toString());
                    listDB = sb.toString().split("////");
                    Log.d("listDB??" , "listDB:"+listDB);
                    return sb.toString();
                }
                else {
                    Log.d("지나감","ㅇㅇ");
                    return null;
                }*/

            }catch(UnsupportedEncodingException e){
                e.printStackTrace();
            }catch(IOException e){
                e.printStackTrace();
            }
            //오류시 null 반환
            return null;
        }

        //asyonTask 3번째 인자와 일치 매개변수값 -> doInBackground 리턴값이 전달됨
        //AsynoTask 는 preExcute - doInBackground - postExecute 순으로 자동으로 실행됩니다.
        //ui는 여기서 변경
        protected void onPostExecute(String value){
            super.onPostExecute(value);
        }
    }

    // listDB를 /단위로 끊어서 반환
    public String[] split(String temp123) {
        String[] temp2 = temp123.split("/");
        return temp2;
    }
}
