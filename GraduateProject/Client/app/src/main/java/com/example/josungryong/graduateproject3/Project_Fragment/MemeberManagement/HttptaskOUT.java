package com.example.josungryong.graduateproject3.Project_Fragment.MemeberManagement;

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

import static com.example.josungryong.graduateproject3.Login.preferences;
import static com.example.josungryong.graduateproject3.Project_Fragment.MemeberManagement.Management.ManagementContext;

/**
 * Created by josungryong on 2017-05-15.
 */

// 멤버 탈퇴 통신 //
public class HttptaskOUT extends AsyncTask<String, Void, String> {
    String result = "";
    protected String doInBackground(String... params) {
        // TODO Auto-generated method stub
        String PROJ_SEQ = params[0];
        try {
            String urlPath = "http://58.142.149.131/grad/Grad_project_member_management.php";
            Log.i("urlPat", "value:" + urlPath);

            // 내가 보낼 데이터 (쿼리, CODE는 전역변수, switch 에서 정해준다.)
            String data = "MENU=RETIRE";
            data += "&PROJECT_SEQ=" + PROJ_SEQ;
            data += "&MEMBER_SEQ=" + preferences.getString("MEMBERSEQ", "");

            URL url = new URL(urlPath);
            URLConnection conn = url.openConnection();
            conn.setDoOutput(true);
            OutputStreamWriter wr = new OutputStreamWriter(conn.getOutputStream());

            //추가 할 내용 - 서버 on/off 검사

            // 문자열 전송
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
                result = sb.toString();
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
        if(result.equals("SUCCESS")) {
            Toast.makeText(ManagementContext, "탈퇴 성공", Toast.LENGTH_SHORT).show();
        }
        else {
            Toast.makeText(ManagementContext, "탈퇴 실패", Toast.LENGTH_SHORT).show();
        }
    }

    @Override
    protected void onProgressUpdate(Void... values) {
        super.onProgressUpdate(values);
    }
}

