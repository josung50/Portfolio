package com.example.josungryong.graduateproject3.Project_Fragment;


import android.app.Activity;
import android.content.Intent;
import android.os.AsyncTask;
import android.os.Bundle;
import android.support.annotation.Nullable;
import android.support.v7.app.AppCompatActivity;
import android.support.v7.widget.RecyclerView;
import android.support.v7.widget.StaggeredGridLayoutManager;
import android.text.method.ScrollingMovementMethod;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;
import android.widget.Toast;

import com.example.josungryong.graduateproject3.Comment;
import com.example.josungryong.graduateproject3.R;

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
 * Created by josungryong on 2017-04-06.
 */
public class ProjectInfo2 extends AppCompatActivity {

    private RecyclerView recyclerView;
    private ProjectInfo2ViewAdapter adapterCardview;
    private StaggeredGridLayoutManager linearLayoutManager;
    private ArrayList<ItemDataProjectInfo2> list = new ArrayList<>(); // 리사이클 ( 카드 뷰 ) 를 위한 list
    private String[] listProjectInfo2DB;
    private String[] listProjectInfo2SEQandURI; // 내부 이미지들의 seq , uri의 스플릿 전
    private String[] tempSeqUri; // 내부 이미지들의 seq , uri를 가지고 있음

    private String PROJECT_WORK_SEQ; // 주제의 seq

    // 제작자 / 제목 / 워크 seq / 제작자 seq / 상세 내용 / 등록 시간 / 댓글 수 / 좋아요 수 / 내부이미지(SEQ&URI::)
    //   0       1        2         3               4       5           6           7           8

    private TextView ProjectInfo2_title; // 제목
    private TextView ProjectInfo2_content; // 설명 (상세 내용)
    private TextView ProjectInfo2_resisttime; // 등록시간
    private TextView ProjectInfo2_resistername; // 등록한 사람 (제작자)
    private TextView ProjectInfo2_likenumber; // 좋아요 수
    private TextView ProjectInfo2_commentnumber; // 코멘트 수 (댓글 수)
    private Button ProjectInfo2_like;

    private String putextra_likenumber; // 댓글 창으로 넘기기 위한 변수
    private String putextra_commentnumber; // 댓글 창으로 넘기기 위한 변수

    private Intent intent;

    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        setContentView(R.layout.activity_projectinfo2);
        Intent intent = getIntent();
        PROJECT_WORK_SEQ = intent.getStringExtra("PROJECT_WORK_SEQ"); // 주제에 관한 work seq;

        recyclerView = (RecyclerView) findViewById(R.id.recyclerViewProjectInfo2);
        recyclerView.setHasFixedSize(true);
        adapterCardview = new ProjectInfo2ViewAdapter(this,list);
        linearLayoutManager = new StaggeredGridLayoutManager(1,StaggeredGridLayoutManager.VERTICAL);
        recyclerView.setLayoutManager(linearLayoutManager);
        recyclerView.setAdapter(adapterCardview);
        new HttpTaskProjectInfo2Show().execute();

        ProjectInfo2_title = (TextView) findViewById(R.id.projectinfo2_title);
        ProjectInfo2_commentnumber = (TextView) findViewById(R.id.projectinfo2_commentnumber);
        ProjectInfo2_content = (TextView) findViewById(R.id.projectinfo2_content);
        ProjectInfo2_content.setMovementMethod(ScrollingMovementMethod.getInstance());
        ProjectInfo2_resisttime = (TextView) findViewById(R.id.projectinfo2_resisttime);
        ProjectInfo2_resistername = (TextView) findViewById(R.id.projectinfo2_resistername);
        ProjectInfo2_like = (Button) findViewById(R.id.projectinfo2_like);
        ProjectInfo2_likenumber = (TextView) findViewById(R.id.projectinfo2_likenumber);

        super.onCreate(savedInstanceState);
    }

    // PHP 디자인에 해당하는 파일 불러오는 통신 class
    public class HttpTaskProjectInfo2Show extends AsyncTask<String, Void, String> {
        /* Bitmap bitmap , String image는 전역변수 */
        protected String doInBackground(String... params) {
            // TODO Auto-generated method stub
            try {
                preferences = getSharedPreferences("login_prefs", MODE_PRIVATE);

                String urlPath = "http://58.142.149.131/grad/Grad_project_list_subject_card_info.php";
                String data = "PROJECT_WORK_SEQ="+PROJECT_WORK_SEQ;
                data += "&LOGIN_USER_SEQ="+preferences.getString("MEMBERSEQ","");
                Log.i("testvalue" , "value data : " + data);

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
                Log.i("testvalueprojectinfo2" ,"value : " + sb.toString());
                CheckNull = sb.toString();

                if (sb.toString() != "") {
                    listProjectInfo2DB = sb.toString().split("a!PJP"); // 태그에서 #이 있을 수 있으므로 split을 a!PJP로 한다.
                    // 제작자 / 제목 / 워크 seq / 제작자 seq / 상세 내용 / 등록 시간 / 댓글 수 / 좋아요 수 / 로그인 한 사람이 좋아요 눌럿는지 여부/ 내부이미지(SEQ&URI::)
                    //   0       1        2         3               4       5           6           7               8                                       9

                    if(listProjectInfo2DB.length < 10) { // SEQ & URI 가 비었을 때를 체크
                        listProjectInfo2SEQandURI = null;
                    }
                    else {
                        listProjectInfo2SEQandURI = split(listProjectInfo2DB[9], "::"); // seq & uri
                    }
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
            if(listProjectInfo2DB[8].equals("\\(CHECKED\\)")) {
                ProjectInfo2_like.setBackgroundResource(R.drawable.like_after);
            }
            // 리사이클 뷰 셋팅 , 어뎁터에 내용 추가가
            // 제작자 / 제목 / 워크 seq / 제작자 seq / 상세 내용 / 등록 시간 / 댓글 수 / 좋아요 수 / 로그인 한 사람이 좋아요 눌럿는지 여부/ 내부이미지(SEQ&URI::)
            //   0       1        2         3               4       5           6           7               8                                       9
            if(listProjectInfo2DB.length < 9) { // SEQ & URI 가 비었을 때를 체크
                ProjectInfo2_title.setText(listProjectInfo2DB[1]); // 제목
                listProjectInfo2DB[4] = listProjectInfo2DB[4].replace("ReAdLiNe","\n");
                ProjectInfo2_content.setText(listProjectInfo2DB[4]); // 설명 (상세 내용)
                ProjectInfo2_resisttime.setText(listProjectInfo2DB[5]); // 등록시간
                ProjectInfo2_resistername.setText(listProjectInfo2DB[0]); // 등록한 사람 (제작자)
                ProjectInfo2_likenumber.setText(listProjectInfo2DB[7]); // 좋아요 수
                ProjectInfo2_commentnumber.setText(listProjectInfo2DB[6]); // 코멘트 수 (댓글 수)

                putextra_commentnumber = listProjectInfo2DB[6];
                putextra_likenumber = listProjectInfo2DB[7];
            }
            else {
                ProjectInfo2_title.setText(listProjectInfo2DB[1]); // 제목
                listProjectInfo2DB[4] = listProjectInfo2DB[4].replace("ReAdLiNe","\n");
                ProjectInfo2_content.setText(listProjectInfo2DB[4]); // 설명 (상세 내용)
                ProjectInfo2_resisttime.setText(listProjectInfo2DB[5]); // 등록시간
                ProjectInfo2_resistername.setText(listProjectInfo2DB[0]); // 등록한 사람 (제작자)
                ProjectInfo2_likenumber.setText("좋아요 : " + listProjectInfo2DB[7]); // 좋아요 수
                ProjectInfo2_commentnumber.setText("댓글 : " + listProjectInfo2DB[6]); // 코멘트 수 (댓글 수)

                // 추가작업.. 익셉션 처리해 줄것
                list = createContactsList(listProjectInfo2SEQandURI.length);
                adapterCardview = new ProjectInfo2ViewAdapter(getApplicationContext(), list);
                linearLayoutManager = new StaggeredGridLayoutManager(1,StaggeredGridLayoutManager.VERTICAL);
                recyclerView.setLayoutManager(linearLayoutManager);
                recyclerView.setAdapter(adapterCardview);
            }

            super.onPostExecute(value);
        }

        @Override
        protected void onProgressUpdate(Void... values) {
            super.onProgressUpdate(values);
        }
    }

    // DB에서 찾은 내용을 what 단위로 끊어서 반환
    public String[] split(String temp123 , String what) {
        String[] temp2 = temp123.split(what);
        return temp2;
    }

    // 카드에 데이터를 넣어준다.. 어뎁터에 list에 contacts를 복사해서 붙이는 것
    public ArrayList<ItemDataProjectInfo2> createContactsList(int numContacts) {

        ArrayList<ItemDataProjectInfo2> contacts = new ArrayList<ItemDataProjectInfo2>();
        for (int i = 0; i < numContacts; i++) { // <BR> 구분이 아니라 단일이라 바로 0부터 시작
            tempSeqUri = split(listProjectInfo2SEQandURI[i],"&");
            contacts.add(new ItemDataProjectInfo2(tempSeqUri[0] , tempSeqUri[1])); // seq , uri
        }
        return contacts;
    }

    public void onClick(View v) {
        switch (v.getId()) {
            case R.id.projectinfo2_comment:
                intent = new Intent(ProjectInfo2.this, Comment.class);
                intent.putExtra("WHERE","PROJECTINFO2");
                intent.putExtra("PROJECT_WORK_SEQ" , PROJECT_WORK_SEQ);
                Log.i("extravalue" , "value : " + putextra_commentnumber + putextra_likenumber);
                startActivity(intent);
                break;
            case R.id.projectinfo2_like:
                break;
        }
    }
}
