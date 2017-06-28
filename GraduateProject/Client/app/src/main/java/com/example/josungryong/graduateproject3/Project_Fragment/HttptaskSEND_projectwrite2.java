package com.example.josungryong.graduateproject3.Project_Fragment;

import android.os.AsyncTask;
import android.util.Log;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.UnsupportedEncodingException;
import java.net.URL;
import java.net.URLConnection;

import static com.example.josungryong.graduateproject3.Login.preferences;

/**
 * Created by josungryong on 2017-05-22.
 */

public class HttptaskSEND_projectwrite2 extends AsyncTask<String, Void, String> {
    protected String doInBackground(String... params) {
        String title = params[0];
        String thumbnail = params[1]; // 썸네일 파일 이름
        String subj_seq = params[2]; // 주제 seq;
        String contents = params[3]; // 상세내용
        contents = contents.replace("\n","ReAdLiNe"); // readline에서 개행을 기준으로 받기 때문에 새로운 문자로 바꿔준다.
        // TODO Auto-generated method stub
        String NewMemeberID = params[0]; // 추가하고자 하는 멤버의 e mail

        try {
            String urlPath = "http://58.142.149.131/grad/Grad_project_work_register.php";
            Log.i("urlPat", "value:" + urlPath);

            // 내가 보낼 데이터 (쿼리, CODE는 전역변수, switch 에서 정해준다.)
            //String data = "&MEMBER_SEQ=" + preferences.getString("MEMBERSEQ","");
            String data = "TITLE=" + title;
            data += "&MEMBER_SEQ=" + preferences.getString("MEMBERSEQ","");
            data += "&THUMB_URI=" + thumbnail;
            data += "&SUBJ_SEQ=" + subj_seq;
            data += "&CONTENTS=" + contents;

            URL url = new URL(urlPath);
            URLConnection conn = url.openConnection();
            conn.setDoOutput(true);
            OutputStreamWriter wr = new OutputStreamWriter(conn.getOutputStream());

            //추가 할 내용 - 서버 on/off 검사

            // 문자열 전송
            Log.i("datavalueSEND" , "value : " + data);
            wr.write(data);
            wr.flush();

            BufferedReader reader = new BufferedReader(new InputStreamReader(conn.getInputStream()));

            StringBuilder sb = new StringBuilder();
            String CheckNull = "0";
            String line = null;

            while ((line = reader.readLine()) != null) {
                sb.append(line);
            }

            CheckNull = sb.toString();

            if (sb.toString() != "") {
            }
            else{
                return null;
            }
        }

        catch(UnsupportedEncodingException e){
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

    @Override
    protected void onProgressUpdate(Void... values) {
        super.onProgressUpdate(values);
    }
}