package com.example.josungryong.graduateproject3;

import android.os.AsyncTask;
import android.util.Log;
import android.widget.Toast;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.UnsupportedEncodingException;
import java.net.URL;
import java.net.URLConnection;

import static com.example.josungryong.graduateproject3.Comment.Comment;
import static com.example.josungryong.graduateproject3.Comment.DESIGN_WORK_SEQ;
import static com.example.josungryong.graduateproject3.Comment.PROJECT_WORK_SEQ;
import static com.example.josungryong.graduateproject3.Comment.WHERE;
import static com.example.josungryong.graduateproject3.Login.preferences;

/**
 * Created by josungryong on 2017-05-25.
 */

public class HttpTaskCommentDelete extends AsyncTask<String, String, String> {
    protected String doInBackground(String... params) {
        // TODO Auto-generated method stub

        String WHERE_SEQ = params[0];
        String COMMENT_SEQ = params[1]; // PROJECT_SEQ=14 OR DESIGN_SEQ=15 등

            try {
                String urlPath = "http://58.142.149.131/grad/Grad_delete_comment.php";

                String data = "COMMENT_SEQ=" + COMMENT_SEQ;
                data += "&" + WHERE_SEQ;

                URL url = new URL(urlPath);
                URLConnection conn = url.openConnection();
                conn.setDoOutput(true);
                OutputStreamWriter wr = new OutputStreamWriter(conn.getOutputStream());

                //추가 할 내용 - 서버 on/off 검사

                // 문자열 전송
                Log.i("commentdelete" , "value : " + data);
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
    protected void onPostExecute(String value) {
        super.onPostExecute(value);
        Toast.makeText(Comment, "삭제 되었습니다.", Toast.LENGTH_SHORT).show();
        if(WHERE.equals("PROJECTINFO2")) {
            new HttpTaskCommentShow().execute(WHERE , PROJECT_WORK_SEQ);
        }
        else if(WHERE.equals("DESIGNINFO")) {
            new HttpTaskCommentShow().execute(WHERE , DESIGN_WORK_SEQ);
        }
    }
}