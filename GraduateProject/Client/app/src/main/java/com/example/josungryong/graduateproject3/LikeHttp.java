package com.example.josungryong.graduateproject3;

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
 * Created by josungryong on 2017-05-14.
 */

public class LikeHttp extends AsyncTask<String, String, String> {
    protected String doInBackground(String... params) {
        // TODO Auto-generated method stub

        String where = params[0]; // PROJECT , DESIGN 둘 중 하나
        String seq = params[1]; // PROJECT_SEQ 혹은 DESIGN_SEQ
        String like_status = params[2]; // UNCHECKED 혹은 CHECKED; (좋아요를 눌렀는지에 대한 상태)

        Log.i("paramsvalue" , "value : " + where + " " + seq + " " +  like_status);
        if(where.equals("DESIGN")) {
            try {
                String urlPath = "http://58.142.149.131/grad/Grad_work_like.php";

                String data = "DESIGN_WORK_SEQ=" + seq;
                data += "&MEMBER_SEQ=" + preferences.getString("MEMBERSEQ","");
                data += "&LIKE_STATUS=" + like_status;

                URL url = new URL(urlPath);
                URLConnection conn = url.openConnection();
                conn.setDoOutput(true);
                OutputStreamWriter wr = new OutputStreamWriter(conn.getOutputStream());

                //추가 할 내용 - 서버 on/off 검사

                // 문자열 전송
                Log.i("likedata" , "value : " + data);
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
        }
        //오류시 null 반환
        return null;
    }

    //asyonTask 3번째 인자와 일치 매개변수값 -> doInBackground 리턴값이 전달됨
    //AsynoTask 는 preExcute - doInBackground - postExecute 순으로 자동으로 실행됩니다.
    //ui는 여기서 변경
    protected void onPostExecute(String value) { // 스피너 불러오기
        super.onPostExecute(value);
    }
}
