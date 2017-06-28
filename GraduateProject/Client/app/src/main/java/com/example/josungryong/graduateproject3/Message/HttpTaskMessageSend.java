package com.example.josungryong.graduateproject3.Message;

import android.os.AsyncTask;
import android.support.v7.widget.StaggeredGridLayoutManager;
import android.util.Log;
import android.widget.Toast;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.UnsupportedEncodingException;
import java.net.URL;
import java.net.URLConnection;
import java.util.ArrayList;

import static com.example.josungryong.graduateproject3.Login.preferences;
import static com.example.josungryong.graduateproject3.Message.MessageIn.MessageIn;
/**
 * Created by josungryong on 2017-05-24.
 */

public class HttpTaskMessageSend extends AsyncTask<String, Void, String> {

    String result;

    protected String doInBackground(String... params) {
        String RECEIVER = params[0];
        String MESSAGE = params[1];
        // TODO Auto-generated method stub
        try {
            String urlPath = "http://58.142.149.131/grad/Grad_message.php";

            // 내가 보낼 데이터 (쿼리, SUBSEQ 전역변수, switch 에서 정해준다.)
            String data = "MEMBER_SEQ=" +preferences.getString("MEMBERSEQ","");
            data +="&RECEIVER=" + RECEIVER ;
            data +="&MESSAGE=" + MESSAGE;
            data +="&COMMAND=SEND_MESSAGE";

            URL url = new URL(urlPath);
            URLConnection conn = url.openConnection();
            conn.setDoOutput(true);
            OutputStreamWriter wr = new OutputStreamWriter(conn.getOutputStream());

            //추가 할 내용 - 서버 on/off 검사

            // 문자열 전송
            Log.i("MESSAGEINSENDDATA" , "value ; " + data);
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
            Log.i("MESSAGEINSENDDATA2" , "value ; " + sb.toString());
            // <BR> 메세지 내용 / 받거나 보낸 시간 / 보낸 메시지인지 받은 메세지 인지 (R || S)

            if (sb.toString() != "") {
                result = sb.toString();
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
    protected void onPostExecute(String value) {
        super.onPostExecute(value);
        if (result.equals("Y")) {

        }
        else if (result.equals("N")) {
            Toast.makeText(MessageIn, "메시지 전송에 실패했습니다.", Toast.LENGTH_SHORT).show();
        }
    }

    @Override
    protected void onProgressUpdate(Void... values) {
        super.onProgressUpdate(values);
    }
}
