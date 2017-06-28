package com.example.josungryong.graduateproject3.Design_Fragment;

import android.net.Uri;
import android.os.AsyncTask;
import android.util.Log;

import com.example.josungryong.graduateproject3.ImageUtill;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.UnsupportedEncodingException;
import java.net.URL;
import java.net.URLConnection;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Date;

import static com.example.josungryong.graduateproject3.Design_Fragment.DesignWrite.Time_FileName;
import static com.example.josungryong.graduateproject3.Design_Fragment.DesignWrite.list;
import static com.example.josungryong.graduateproject3.Design_Fragment.DesignWrite2.Write2Context;
import static com.example.josungryong.graduateproject3.Design_Fragment.DesignWrite2.list_Tag;
import static com.example.josungryong.graduateproject3.Login.preferences;

/**
 * Created by josungryong on 2017-05-16.
 */

public class HttpTaskWrite extends AsyncTask<String, Void, String> {

    protected String doInBackground(String... params) {
        String TITLE = params[0];
        String CONTENTS = params[1];
        String IMAGE_LIST = params[2];
        String MEMBER_SEQ = preferences.getString("MEMBERSEQ","");
        ArrayList<ItemDataTag> Tag = list_Tag; // 태그
        ArrayList<ItemDataDesignWrite> UriSet = list; // 이미지 URI들
        String FilePath = null;
        String FileName = null;

        // TODO Auto-generated method stub
        try {
            String urlPath = "http://58.142.149.131/grad/Grad_design_register.php";

            // 내가 보낼 데이터 (쿼리, SUBSEQ 전역변수, switch 에서 정해준다.)
            String data = "TITLE=" + TITLE;
            data += "&CONTENTS=" + CONTENTS;
            data += "&MEMBER_SEQ=" + MEMBER_SEQ;
            data += "&IMAGE_LIST=" + IMAGE_LIST;
            data += "&TAGS=";
            for(int i=0; i<Tag.size(); i++) {
                data += "#"+Tag.get(i).text;
            }

            URL url = new URL(urlPath);
            URLConnection conn = url.openConnection();
            conn.setDoOutput(true);
            OutputStreamWriter wr = new OutputStreamWriter(conn.getOutputStream());

            //추가 할 내용 - 서버 on/off 검사

            // 문자열 전송
            Log.i("write2data" , "value ; " + data);
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

        } catch (UnsupportedEncodingException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }
        return null;
    }
    //asyonTask 3번째 인자와 일치 매개변수값 -> doInBackground 리턴값이 전달됨
    //AsynoTask 는 preExcute - doInBackground - postExecute 순으로 자동으로 실행됩니다.
    //ui는 여기서 변경
    protected void onPostExecute(String value) { // 스피너 불러오기
        super.onPostExecute(value);
    }

    @Override
    protected void onProgressUpdate(Void... values) {
        super.onProgressUpdate(values);
    }
}