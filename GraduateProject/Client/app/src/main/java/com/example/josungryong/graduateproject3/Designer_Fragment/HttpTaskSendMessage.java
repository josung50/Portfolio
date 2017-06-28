package com.example.josungryong.graduateproject3.Designer_Fragment;

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
 * Created by josungryong on 2017-05-25.
 */

public class HttpTaskSendMessage extends AsyncTask<String, String, String> {
    protected String doInBackground(String... params) {
        // TODO Auto-generated method stub

        String RECEIVER = params[0]; // designer seq
        String MESSAGE = params[1]; // 메시지
            try {
                String urlPath = "http://58.142.149.131/grad/Grad_message.php";

                String data = "RECEIVER=" + RECEIVER;
                data += "&MEMBER_SEQ=" + preferences.getString("MEMBERSEQ","");
                data += "&MESSAGE=" + MESSAGE;
                data += "&COMMAND=SEND_MESSAGE";

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

