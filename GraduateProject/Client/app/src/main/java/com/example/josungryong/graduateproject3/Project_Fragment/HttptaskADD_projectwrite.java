package com.example.josungryong.graduateproject3.Project_Fragment;

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

import static com.example.josungryong.graduateproject3.Login.preferences;
import static com.example.josungryong.graduateproject3.Project_Fragment.ProjectWrite.ProjectWrite;
import static com.example.josungryong.graduateproject3.Project_Fragment.ProjectWrite.adapter_projectwrite;
import static com.example.josungryong.graduateproject3.Project_Fragment.ProjectWrite.linearLayoutManager_projectwrite;
import static com.example.josungryong.graduateproject3.Project_Fragment.ProjectWrite.list_projectwrite;
import static com.example.josungryong.graduateproject3.Project_Fragment.ProjectWrite.recyclerView_projectwrite;

/**
 * Created by josungryong on 2017-05-20.
 */

public class HttptaskADD_projectwrite extends AsyncTask<String, Void, String> {
    String result;
    protected String doInBackground(String... params) {
        // TODO Auto-generated method stub
        String NewMemeberID = params[0]; // 추가하고자 하는 멤버의 e mail

        try {
            String urlPath = "http://58.142.149.131/grad/Grad_project_member_search.php";
            Log.i("urlPat", "value:" + urlPath);

            // 내가 보낼 데이터 (쿼리, CODE는 전역변수, switch 에서 정해준다.)
            //String data = "&MEMBER_SEQ=" + preferences.getString("MEMBERSEQ","");
            String data = "&email=" + NewMemeberID;

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
            Log.i("textvaleadd" , "value : " + sb.toString());

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
        if(result == null || result.equals("N")) { // 아이디가 존재하지 않을 경우
            Toast.makeText(ProjectWrite, "ID가 존재하지 않습니다.", Toast.LENGTH_SHORT).show();
        }
        else {
            String temp[] = result.split("#"); // seq # 디자이너 닉네임 # Y
            Log.i("tempvalue", " value:" + temp[0] + " " + temp[1] + " " + temp[2]);
            if(IsInList(temp[0]) == true) {
                Toast.makeText(ProjectWrite, "이미 추가된 ID 입니다.", Toast.LENGTH_SHORT).show();
                return;
            }
            if(CheckMySelt(temp[0]) == true) {
                Toast.makeText(ProjectWrite, "자기 자신은 추가할 수 없습니다.", Toast.LENGTH_SHORT).show();
                return;
            }
            Toast.makeText(ProjectWrite, "추가가 되었습니다.", Toast.LENGTH_SHORT).show();
            list_projectwrite.add(new ItemDataProjectWrite(temp[0],temp[1]));
            adapter_projectwrite = new ProjectWriteViewAdapter(ProjectWrite, list_projectwrite);
            linearLayoutManager_projectwrite = new StaggeredGridLayoutManager(1,StaggeredGridLayoutManager.VERTICAL);
            recyclerView_projectwrite.setLayoutManager(linearLayoutManager_projectwrite);
            recyclerView_projectwrite.setAdapter(adapter_projectwrite);
        }
    }

    @Override
    protected void onProgressUpdate(Void... values) {
        super.onProgressUpdate(values);
    }

    private Boolean IsInList(String seq) {
        for(int i=0; i<list_projectwrite.size(); i++) {
            if(list_projectwrite.get(i).designer_seq.equals(seq))
                return true;
        }
        return false;
    }

    private Boolean CheckMySelt(String seq) {
        if(preferences.getString("MEMBERSEQ","").equals(seq)) {
            return true;
        }
        return false;
    }
}
