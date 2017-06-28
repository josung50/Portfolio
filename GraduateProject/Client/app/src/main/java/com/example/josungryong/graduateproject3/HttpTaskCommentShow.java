package com.example.josungryong.graduateproject3;

import android.os.AsyncTask;
import android.support.v7.widget.StaggeredGridLayoutManager;
import android.util.Log;
import android.widget.TextView;
import android.widget.Toast;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.UnsupportedEncodingException;
import java.net.URL;
import java.net.URLConnection;
import java.util.ArrayList;

import static com.example.josungryong.graduateproject3.Comment.adapterCardview_comment;
import static com.example.josungryong.graduateproject3.Comment.linearLayoutManager_comment;
import static com.example.josungryong.graduateproject3.Comment.listCommentDB_comment;
import static com.example.josungryong.graduateproject3.Comment.list_comment;
import static com.example.josungryong.graduateproject3.Comment.recyclerView_comment;
import static com.example.josungryong.graduateproject3.Comment.Comment;

/**
 * Created by josungryong on 2017-05-25.
 */

public class HttpTaskCommentShow extends AsyncTask<String, String, String> {
    String WHERE_SEQ;
    String urlPath ;
    protected String doInBackground(String... params) {
        String WHERE = params[0];
        String SEQ = params[1];
        // TODO Auto-generated method stub
        try {
            String data = null;
            if(WHERE.equals("PROJECTINFO2")) {
                urlPath = "http://58.142.149.131/grad/Grad_work_comment.php";
                data = "PROJECT_WORK_SEQ=" + SEQ;
                WHERE_SEQ = data;
            }
            else if(WHERE.equals("DESIGNINFO")) {
                urlPath = "http://58.142.149.131/grad/Grad_work_comment.php";
                data = "DESIGN_WORK_SEQ=" + SEQ;
                WHERE_SEQ = data;
            }

            // 내가 보낼 데이터 (쿼리, SUBSEQ 전역변수, switch 에서 정해준다.)
            //String data = "PROJECT_WORK_SEQ=" + PROJECT_WORK_SEQ ;

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
            Log.i("commentreadvalue" , "value : " + sb.toString());
            CheckNull = sb.toString();

            if (sb.toString() != "") {
                listCommentDB_comment = sb.toString().split("<br>"); // <br> comment seq # member seq # 작성자 이름 # 프로필 사진 uri # 내용 # 등록시간
                //        0               1              2               3            4       5

                // 개행 문자 변환 (readline은 \n을 기준을 데이터를 받아오기 때문에 개행이 따로 없다.)
                for(int i=1; i<listCommentDB_comment.length ; i++) {
                    listCommentDB_comment[i] = listCommentDB_comment[i].replace("ReAdLiNe","\n");
                }
            }
            return sb.toString();

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
        // 리사이클 뷰 셋팅 , 어뎁터에 내용 추가가
        if(listCommentDB_comment == null) {
            Toast.makeText(Comment,"등록된 댓글이 없습니다." , Toast.LENGTH_SHORT).show();
        }
        else if(listCommentDB_comment.length>=0) {
            list_comment = createContactsList(listCommentDB_comment.length);

            adapterCardview_comment = new CommentViewAdapter(Comment, list_comment);
            linearLayoutManager_comment = new StaggeredGridLayoutManager(1, StaggeredGridLayoutManager.VERTICAL);
            recyclerView_comment.setLayoutManager(linearLayoutManager_comment);
            recyclerView_comment.setAdapter(adapterCardview_comment);
        }

        super.onPostExecute(value);
    }

    // DB에서 찾은 내용을 what 단위로 끊어서 반환
    public String[] split(String temp123 , String what) {
        String[] temp2 = temp123.split(what);
        return temp2;
    }

    // 카드에 데이터를 넣어준다.. 어뎁터에 list에 contacts를 복사해서 붙이는 것
    public ArrayList<ItemDataComment> createContactsList(int numContacts) {
        String[] temp;

        ArrayList<ItemDataComment> contacts = new ArrayList<ItemDataComment>();
        for (int i = 1; i < numContacts; i++) {
            temp = split(listCommentDB_comment[i],"#");
            // <br> comment seq # member seq # 작성자 이름 # 프로필 사진 uri # 내용 # 등록시간
            //        0               1              2               3            4       5
            contacts.add(new ItemDataComment(temp[0],temp[1],temp[2],temp[3],temp[4],temp[5],WHERE_SEQ));
            Log.i("WHERE_SEQ" , "value : " +  WHERE_SEQ);
        }
        return contacts;
    }
}
