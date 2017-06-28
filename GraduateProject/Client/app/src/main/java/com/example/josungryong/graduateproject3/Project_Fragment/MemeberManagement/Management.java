package com.example.josungryong.graduateproject3.Project_Fragment.MemeberManagement;

import android.content.Context;
import android.content.DialogInterface;
import android.content.Intent;
import android.os.AsyncTask;
import android.os.Bundle;
import android.support.annotation.Nullable;
import android.support.v7.app.AlertDialog;
import android.support.v7.app.AppCompatActivity;
import android.support.v7.widget.RecyclerView;
import android.support.v7.widget.StaggeredGridLayoutManager;
import android.util.Log;
import android.view.View;
import android.view.ViewGroup;
import android.widget.EditText;
import android.widget.Toast;

import com.example.josungryong.graduateproject3.R;

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
 * Created by josungryong on 2017-05-15.
 */

public class Management extends AppCompatActivity {

    public static Context ManagementContext;

    private RecyclerView recyclerView;
    private ManagementViewAdapter adapter;
    private StaggeredGridLayoutManager linearLayoutManager;
    private ArrayList<ItemDataManagement> list = new ArrayList<>();

    // DB 관련 변수 //
    private static String[] listDB; // DB의 결과를 받아오는 변수
    private static String[] temp; // listDB를 <br> 단위로 끊어서 받음
    private static String CODE; // 서버로 보낼 쿼리

    private String PROJ_SEQ;
    private String MASTER_SEQ;

    @Override
    protected void onStop() {
        super.onStop();
    }

    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_management);
        ManagementContext = this;

        Intent intent = getIntent();
        PROJ_SEQ = intent.getStringExtra("PROJ_SEQ");
        MASTER_SEQ = intent.getStringExtra("MASTER_SEQ");
        new HttpTask().execute();

        // 이미지 출력
        recyclerView = (RecyclerView) findViewById(R.id.recyclerViewManagement);
        recyclerView.setHasFixedSize(true);
        adapter = new ManagementViewAdapter(this, list);
        linearLayoutManager = new StaggeredGridLayoutManager(1,StaggeredGridLayoutManager.VERTICAL);
        recyclerView.setLayoutManager(linearLayoutManager);
        recyclerView.setAdapter(adapter);
    }

    // PHP 멤버를 불러오는 통신
    public class HttpTask extends AsyncTask<String, Void, String> {
        protected String doInBackground(String... params) {
            // TODO Auto-generated method stub
            try{
                String urlPath = "http://58.142.149.131/grad/Grad_project_member_list.php";
                Log.i("urlPat" , "value:" + urlPath);

                // 내가 보낼 데이터 (쿼리, CODE는 전역변수, switch 에서 정해준다.)
                String data = "PROJECT_SEQ=" + PROJ_SEQ;
                data +="&MEMBER_SEQ=" + preferences.getString("MEMBERSEQ","");
                Log.i("datalog" , "value : " + data);

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

                while((line = reader.readLine()) != null) {
                    sb.append(line);
                }

                CheckNull = sb.toString();
                Log.d("testquerymanagement", "test:" + sb.toString()); // 제목 / 조회수 / 썸네일경로 / 작품설명 / 제작자 넘버 <br>

                if(sb.toString() != "") {
                    listDB = sb.toString().split("<br>");
                    //Log.d("listDB??" , "listDB:"+listDB);

                    for (int i = 1; i < listDB.length; i++) {
                        temp = split(listDB[i] , "a!PJP"); // 순서대로 디자이너 seq , 디자이너 이름 , 디자이너 프로필사진 uri , 자기소개 내용 , 분야 , 올린 게시물 갯수 , 조회수 , 받은 좋아요 수 , SEQ&URI::(uriset)
                                                            //          0                  1                   2                      3               4           5             6       7               8
                                                            // 각 속성의 split 값은 a!PJP
                    }
                    return sb.toString();
                }
                else {
                    return null;
                }

            }catch(UnsupportedEncodingException e){
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

            // 추가작업.. 익셉션 처리해 줄것
            Log.i("ListDB.length.Designer", "value:" + listDB.length);
            //list = createContactsList(10);
            list = createContactsList(listDB.length);
            adapter = new ManagementViewAdapter(getApplicationContext(), list);
            linearLayoutManager = new StaggeredGridLayoutManager(1,StaggeredGridLayoutManager.VERTICAL);
            recyclerView.setLayoutManager(linearLayoutManager);
            recyclerView.setAdapter(adapter);

            CODE = null;
            super.onPostExecute(value);
        }

        @Override
        protected void onProgressUpdate(Void... values) {
            super.onProgressUpdate(values);
        }
    }

    // listDB를 #단위로 끊어서 반환
    public String[] split(String temp123 , String what) {
        String[] temp2 = temp123.split(what);
        return temp2;
    }
    //commit
    // 카드에 데이터를 넣어준다.. 어뎁터에 list에 contacts를 복사해서 붙이는 것
    public ArrayList<ItemDataManagement> createContactsList(int numContacts) {
        ArrayList<ItemDataManagement> contacts = new ArrayList<ItemDataManagement>();
        for (int i = 1; i < numContacts; i++) {
            temp = split(listDB[i] , "a!PJP"); // 순서대로 디자이너 seq , 디자이너 이름 , 디자이너 프로필사진 uri , 자기소개 내용 , 분야 , 올린 게시물 갯수 , 조회수 , 받은 좋아요 수 , SEQ&URI::(uriset)
                                                //          0                   1               2                       3               4           5               6       7               8
            contacts.add(new ItemDataManagement(temp[0],temp[1],temp[2],temp[3],temp[4],temp[5],temp[6],temp[7],temp[8],PROJ_SEQ));
        }
        return contacts;
    }

    public void onClick(View v) {
        int id = v.getId();
        switch (id) {
            case R.id.management_add: // 멤버 추가
                final EditText name = new EditText(this);
                AlertDialog.Builder alert = new AlertDialog.Builder(Management.this);
                alert.setView(name);
                alert.setTitle("추가할 멤버의 이메일을 입력해주세요.");
                alert.setPositiveButton("추가", new DialogInterface.OnClickListener() {
                    @Override
                    public void onClick(DialogInterface dialog, int which) {
                        new HttptaskADD().execute(PROJ_SEQ,name.getText().toString());
                        new HttpTask().execute(); // 새로고침 효과
                    }
                });
                alert.setNegativeButton("취소", new DialogInterface.OnClickListener() {
                    @Override
                    public void onClick(DialogInterface dialog, int which) {
                        dialog.dismiss(); // 닫기
                    }
                });
                alert.show();
                break;

            case R.id.management_delete: // 탈퇴
                if(MASTER_SEQ.equals(preferences.getString("MEMBERSEQ",""))) {
                    Toast.makeText(ManagementContext, "프로젝트 장은 탈퇴가 불가능 합니다.", Toast.LENGTH_SHORT).show();
                    break;
                }
                AlertDialog.Builder alert2 = new AlertDialog.Builder(this);
                alert2.setTitle("정말 탈퇴 하시겠습니까?");
                alert2.setPositiveButton("예", new DialogInterface.OnClickListener() {
                    @Override
                    public void onClick(DialogInterface dialog, int which) {
                        new HttptaskOUT().execute(PROJ_SEQ);
                        new HttpTask().execute(); // 새로고침 효과
                    }
                });
                alert2.setNegativeButton("아니오", new DialogInterface.OnClickListener() {
                    @Override
                    public void onClick(DialogInterface dialog, int which) {
                        dialog.dismiss(); // 닫기
                    }
                });
                alert2.show();
                break;
        }
    }
}
