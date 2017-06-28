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
import static com.example.josungryong.graduateproject3.Message.MessageIn.adapter_messagein;
import static com.example.josungryong.graduateproject3.Message.MessageIn.linearLayoutManager_messagein;
import static com.example.josungryong.graduateproject3.Message.MessageIn.listDB_messagein;
import static com.example.josungryong.graduateproject3.Message.MessageIn.list_messagein;
import static com.example.josungryong.graduateproject3.Message.MessageIn.recyclerView_messagein;
import static com.example.josungryong.graduateproject3.Message.MessageIn.temp_messagein;

/**
 * Created by josungryong on 2017-05-24.
 */

public class HttpTaskMessageInShow extends AsyncTask<String, Void, String> {

    protected String doInBackground(String... params) {
        String SENDER_SEQ = params[0];
        // TODO Auto-generated method stub
        try {
            String urlPath = "http://58.142.149.131/grad/Grad_message.php";

            // 내가 보낼 데이터 (쿼리, SUBSEQ 전역변수, switch 에서 정해준다.)
            String data = "MEMBER_SEQ=" +preferences.getString("MEMBERSEQ","");
            data +="&SENDER_SEQ=" + SENDER_SEQ;
            data +="&COMMAND=LIST_MESSAGE";

            URL url = new URL(urlPath);
            URLConnection conn = url.openConnection();
            conn.setDoOutput(true);
            OutputStreamWriter wr = new OutputStreamWriter(conn.getOutputStream());

            //추가 할 내용 - 서버 on/off 검사

            // 문자열 전송
            Log.i("MESSAGEINDATA" , "value ; " + data);
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
            Log.i("MESSAGEINDATA2" , "value ; " + sb.toString());
            // <BR> 메세지 내용 / 받거나 보낸 시간 / 보낸 메시지인지 받은 메세지 인지 (R || S)

            if (sb.toString() != "") {
                listDB_messagein = sb.toString().split("<br>");
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
        if(listDB_messagein != null) {
            list_messagein = createContactsList(listDB_messagein.length);
            adapter_messagein = new MessageInViewAdapter(MessageIn, list_messagein);
            linearLayoutManager_messagein = new StaggeredGridLayoutManager(1, StaggeredGridLayoutManager.VERTICAL);
            recyclerView_messagein.setLayoutManager(linearLayoutManager_messagein);
            recyclerView_messagein.setAdapter(adapter_messagein);
        }
        else {
            Toast.makeText(MessageIn, "받은 메세지가 없습니다.", Toast.LENGTH_SHORT).show();
        }
    }

    @Override
    protected void onProgressUpdate(Void... values) {
        super.onProgressUpdate(values);
    }

    public ArrayList<ItemDataMessageIn> createContactsList(int numContacts) {
        ArrayList<ItemDataMessageIn> contacts = new ArrayList<ItemDataMessageIn>();
        for (int i = 1; i < numContacts; i++) {
            temp_messagein = split(listDB_messagein[i] , "a!PJP"); // <BR> 메세지 내용 / 받거나 보낸 시간 / 보낸 메시지인지 받은 메세지 인지 (R || S)
            contacts.add(new ItemDataMessageIn(temp_messagein[0] , temp_messagein[1] , temp_messagein[2]));
        }
        return contacts;
    }

    public String[] split(String temp123 , String what) {
        String[] temp2 = temp123.split(what);
        return temp2;
    }
}
