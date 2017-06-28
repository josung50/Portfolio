package com.example.josungryong.graduateproject3.Project_Fragment.MemeberManagement;

import android.content.Context;
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
 * Created by josungryong on 2017-05-16.
 */

public class HttptaskADD extends AsyncTask<String, Void, String> {
    String result;
    protected String doInBackground(String... params) {
        // TODO Auto-generated method stub
        String PROJ_SEQ = params[0];
        String NewMemeberID = params[1]; // 추가하고자 하는 멤버의 e mail

        try {
            String urlPath = "http://58.142.149.131/grad/Grad_project_member_management.php";
            Log.i("urlPat", "value:" + urlPath);

            // 내가 보낼 데이터 (쿼리, CODE는 전역변수, switch 에서 정해준다.)
            String data = "MENU=JOIN_US";
            data += "&PROJECT_SEQ=" + PROJ_SEQ;
            data += "&MEMBER_SEQ=" + preferences.getString("MEMBERSEQ","");
            data += "&ID=" + NewMemeberID;

            URL url = new URL(urlPath);
            URLConnection conn = url.openConnection();
            conn.setDoOutput(true);
            OutputStreamWriter wr = new OutputStreamWriter(conn.getOutputStream());

            //추가 할 내용 - 서버 on/off 검사

            // 문자열 전송
            Log.i("datavalueJOIN" , "value : " + data);
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
        Log.i("resultvalue" , "value : " + result);
        if(result.equals("Y")) {
            Toast.makeText(ManagementContext, "멤버추가 완료", Toast.LENGTH_SHORT).show();
        }
        else {
            Toast.makeText(ManagementContext, "존재하지 않는 아이디입니다.", Toast.LENGTH_SHORT).show();
        }
    }

    @Override
    protected void onProgressUpdate(Void... values) {
        super.onProgressUpdate(values);
    }
}
