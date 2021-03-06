package com.example.josungryong.graduateproject3;

import android.content.Intent;
import android.os.AsyncTask;
import android.util.Log;
import android.widget.Toast;

import com.example.josungryong.graduateproject3.Project_Fragment.ProjectWrite;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.UnsupportedEncodingException;
import java.net.URL;
import java.net.URLConnection;

import static com.example.josungryong.graduateproject3.Login.preferences;
import static com.example.josungryong.graduateproject3.MainActivity.CHECK;
import static com.example.josungryong.graduateproject3.MainActivity.MainActivity;

/**
 * Created by josungryong on 2017-05-25.
 */

public class HttpTaskCheckProjectWrite extends AsyncTask<String, String, String> {
    protected String doInBackground(String... params) {
        // TODO Auto-generated method stub

            try {
                String urlPath = "http://58.142.149.131/grad/Grad_project_register_check.php";
                String data = "MEMBER_SEQ=" + preferences.getString("MEMBERSEQ","");
                URL url = new URL(urlPath);
                URLConnection conn = url.openConnection();
                conn.setDoOutput(true);
                OutputStreamWriter wr = new OutputStreamWriter(conn.getOutputStream());

                //추가 할 내용 - 서버 on/off 검사

                // 문자열 전송
                Log.i("checkvalue" , "value :" + data);
                wr.write(data);
                wr.flush();


                BufferedReader reader = new BufferedReader(new InputStreamReader(conn.getInputStream()));

                StringBuilder sb = new StringBuilder();
                String CheckNull = "0";
                String line = null;

                while ((line = reader.readLine()) != null) {
                    sb.append(line);
                }
                Log.i("testvaluelike", "value : " + sb.toString());
                CheckNull = sb.toString();

                if (sb.toString() != "") {
                    return sb.toString();
                } else {
                    return null;
                }

            } catch (UnsupportedEncodingException e) {
                e.printStackTrace();
            } catch (IOException e) {
                e.printStackTrace();
            }
        //오류시 null 반환
        return null;
    }

    //asyonTask 3번째 인자와 일치 매개변수값 -> doInBackground 리턴값이 전달됨
    //AsynoTask 는 preExcute - doInBackground - postExecute 순으로 자동으로 실행됩니다.
    //ui는 여기서 변경
    protected void onPostExecute(String value) { // 스피너 불러오기
        super.onPostExecute(value);
        if(value.equals("CAN")) {
            CHECK = 1;
            Intent intent = new Intent(MainActivity , ProjectWrite.class);
            MainActivity.startActivity(intent);
        }
        else {
            Toast.makeText(MainActivity, "디자인을 먼저 등록해주세요.", Toast.LENGTH_SHORT).show();
            CHECK = 0;
        }
    }
}
