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
import static com.example.josungryong.graduateproject3.Message.Message_Main.Message_Main;
import static com.example.josungryong.graduateproject3.Message.Message_Main.adapter_message;
import static com.example.josungryong.graduateproject3.Message.Message_Main.linearLayoutManager_message;
import static com.example.josungryong.graduateproject3.Message.Message_Main.listDB_message;
import static com.example.josungryong.graduateproject3.Message.Message_Main.list_message;
import static com.example.josungryong.graduateproject3.Message.Message_Main.recyclerView_message;
import static com.example.josungryong.graduateproject3.Message.Message_Main.temp_message;

/**
 * Created by josungryong on 2017-05-23.
 */

public class HttpTaskMessageShow extends AsyncTask<String, Void, String> {

    protected String doInBackground(String... params) {

        // TODO Auto-generated method stub
        try {
            String urlPath = "http://58.142.149.131/grad/Grad_message.php";

            // 내가 보낼 데이터 (쿼리, SUBSEQ 전역변수, switch 에서 정해준다.)
            String data = "MEMBER_SEQ=" +preferences.getString("MEMBERSEQ","");
            data +="&COMMAND=GET_LIST";

            URL url = new URL(urlPath);
            URLConnection conn = url.openConnection();
            conn.setDoOutput(true);
            OutputStreamWriter wr = new OutputStreamWriter(conn.getOutputStream());

            //추가 할 내용 - 서버 on/off 검사

            // 문자열 전송
            Log.i("MESSAGEDATA" , "value ; " + data);
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
            Log.i("MESSAGEDATA2" , "value ; " + sb.toString());
            // <BR> 메세지 보낸 사람이름 / 메세지 내용 / 메세지 보낸 사람 SEQ / 메세지 받은 시간

            if (sb.toString() != "") {
                listDB_message = sb.toString().split("<br>");
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
        if(listDB_message != null) {
            list_message = createContactsList(listDB_message.length);
            adapter_message = new MessageViewAdapter(Message_Main, list_message);
            linearLayoutManager_message = new StaggeredGridLayoutManager(1,StaggeredGridLayoutManager.VERTICAL);
            recyclerView_message.setLayoutManager(linearLayoutManager_message);
            recyclerView_message.setAdapter(adapter_message);
        }
        else {
            Toast.makeText(Message_Main, "받은 메세지가 없습니다.", Toast.LENGTH_SHORT).show();
        }
    }

    @Override
    protected void onProgressUpdate(Void... values) {
        super.onProgressUpdate(values);
    }

    public ArrayList<ItemDataMessage> createContactsList(int numContacts) {
        ArrayList<ItemDataMessage> contacts = new ArrayList<ItemDataMessage>();
        for (int i = 1; i < numContacts; i++) {
            temp_message = split(listDB_message[i] , "a!PJP"); // <BR> 메세지 보낸 사람이름 / 프로파일uri / 메세지 내용 / 메세지 보낸 사람 SEQ / 메세지 받은 시간
                                                                 //          0                          1             2                     3       4
            contacts.add(new ItemDataMessage(temp_message[0] , temp_message[1] , temp_message[2] , temp_message[3] , temp_message[4]));
        }
        return contacts;
    }

    public String[] split(String temp123 , String what) {
        String[] temp2 = temp123.split(what);
        return temp2;
    }
}