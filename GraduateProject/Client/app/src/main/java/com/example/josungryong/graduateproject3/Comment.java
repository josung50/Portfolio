package com.example.josungryong.graduateproject3;

import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.content.SharedPreferences;
import android.os.AsyncTask;
import android.os.Bundle;
import android.support.annotation.Nullable;
import android.support.v7.app.AppCompatActivity;
import android.support.v7.widget.RecyclerView;
import android.support.v7.widget.StaggeredGridLayoutManager;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.Toast;

import org.w3c.dom.Text;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.UnsupportedEncodingException;
import java.net.URL;
import java.net.URLConnection;
import java.util.ArrayList;

import static com.example.josungryong.graduateproject3.Login.preferences;

/**
 * Created by josungryong on 2017-04-07.
 */

public class Comment extends AppCompatActivity {

    public static Context Comment;

    private Button comment_delete;
    private EditText comment_editcomment;
    private TextView likenumber_view;
    private TextView commentnumber_view;

    public static RecyclerView recyclerView_comment;
    public static CommentViewAdapter adapterCardview_comment;
    public static StaggeredGridLayoutManager linearLayoutManager_comment;
    public static ArrayList<ItemDataComment> list_comment = new ArrayList<>(); // 리사이클 ( 카드 뷰 ) 를 위한 list
    public static String[] listCommentDB_comment;

    public static String WHERE; // 어디에서 넘어온 댓글창인지 확인
    public static String PROJECT_WORK_SEQ;
    public static String DESIGN_WORK_SEQ;

    private String content;

    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        setContentView(R.layout.activity_comment);
        Comment = this;
        comment_editcomment = (EditText) findViewById(R.id.comment_editcomment);

        recyclerView_comment = (RecyclerView) findViewById(R.id.recyclerViewComment);
        recyclerView_comment.setHasFixedSize(true);
        adapterCardview_comment = new CommentViewAdapter(this,list_comment);
        linearLayoutManager_comment = new StaggeredGridLayoutManager(1,StaggeredGridLayoutManager.VERTICAL);
        recyclerView_comment.setLayoutManager(linearLayoutManager_comment);
        recyclerView_comment.setAdapter(adapterCardview_comment);

        Intent intent = getIntent();
        WHERE = intent.getStringExtra("WHERE");
        if(WHERE.equals("PROJECTINFO2")) {
            PROJECT_WORK_SEQ = intent.getStringExtra("PROJECT_WORK_SEQ");
            new HttpTaskCommentShow().execute(WHERE , PROJECT_WORK_SEQ);
        }
        else if(WHERE.equals("DESIGNINFO")) {
            DESIGN_WORK_SEQ = intent.getStringExtra("DESIGN_WORK_SEQ");
            new HttpTaskCommentShow().execute(WHERE , DESIGN_WORK_SEQ);
        }

        super.onCreate(savedInstanceState);
    }

    // 댓글 전송
    public void submit(View v) {
        if(comment_editcomment.getText().toString() == null || comment_editcomment.getText().toString().replace(" ","").equals("") ||
                comment_editcomment.getText().toString().replace("\n","").equals("")) {
            Toast.makeText(this,"내용이 없습니다.",Toast.LENGTH_SHORT).show();
            return;
        }
        content = comment_editcomment.getText().toString().replace("\n","ReAdLiNe"); // readline에서 개행을 기준으로 받기 때문에 새로운 문자로 바꿔준다.
        new HttpTaskCommentSubmit().execute();
        comment_editcomment.setText("");
    }

    // 댓글 전성 HTTP
    public class HttpTaskCommentSubmit extends AsyncTask<String, Void, String> {
        SharedPreferences preferences = getSharedPreferences("login_prefs", MODE_PRIVATE);
        String urlPath ;
        /* Bitmap bitmap , String image는 전역변수 */
        protected String doInBackground(String... params) {
            // TODO Auto-generated method stub
            try {

                String data = null;
                Intent intent = getIntent();

                if(WHERE.equals("PROJECTINFO2")) {
                    urlPath = "http://58.142.149.131/grad/Grad_work_comment.php";
                    preferences = getSharedPreferences("login_prefs", MODE_PRIVATE);
                    data = "REGI_PROJECT_WORK_SEQ=" + intent.getStringExtra("PROJECT_WORK_SEQ");
                    data +="&REGI_PCOMMENT=" + content;
                    data +="&REGI_MEMBER_SEQ=" + preferences.getString("MEMBERSEQ","");
                }
                else if(WHERE.equals("DESIGNINFO")) {
                    urlPath = "http://58.142.149.131/grad/Grad_work_comment.php";
                    preferences = getSharedPreferences("login_prefs", MODE_PRIVATE);
                    data = "REGI_DESIGN_WORK_SEQ=" + intent.getStringExtra("DESIGN_WORK_SEQ");
                    data +="&REGI_DCOMMENT=" + content;
                    data +="&REGI_D_MEMBER_SEQ=" + preferences.getString("MEMBERSEQ","");
                }

                // 내가 보낼 데이터 (쿼리, SUBSEQ 전역변수, switch 에서 정해준다.)
                //String data = "PROJECT_WORK_SEQ=" + PROJECT_WORK_SEQ ;

                URL url = new URL(urlPath);
                Log.i("urlPathis" , "value : " + url);
                URLConnection conn = url.openConnection();
                conn.setDoOutput(true);
                OutputStreamWriter wr = new OutputStreamWriter(conn.getOutputStream());

                //추가 할 내용 - 서버 on/off 검사

                Log.i("queryvalue" , "value : " + data);
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
            if(WHERE.equals("PROJECTINFO2")) {
                new HttpTaskCommentShow().execute(WHERE , PROJECT_WORK_SEQ);
            }
            else if(WHERE.equals("DESIGNINFO")) {
                new HttpTaskCommentShow().execute(WHERE , DESIGN_WORK_SEQ);
            }
            super.onPostExecute(value);
        }

        @Override
        protected void onProgressUpdate(Void... values) {
            super.onProgressUpdate(values);
        }
    }
}
