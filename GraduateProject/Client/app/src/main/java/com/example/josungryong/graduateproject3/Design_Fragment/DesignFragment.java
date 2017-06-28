package com.example.josungryong.graduateproject3.Design_Fragment;


import android.content.DialogInterface;
import android.content.Intent;
import android.graphics.Color;
import android.os.AsyncTask;
import android.os.Bundle;
import android.support.design.widget.FloatingActionButton;
import android.support.v4.app.Fragment;
import android.support.v4.app.FragmentActivity;
import android.support.v4.app.FragmentManager;
import android.support.v7.app.AlertDialog;
import android.support.v7.widget.AppCompatAutoCompleteTextView;
import android.support.v7.widget.RecyclerView;
import android.support.v7.widget.StaggeredGridLayoutManager;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.Spinner;
import android.widget.TextView;
import android.widget.Toast;

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
import static com.example.josungryong.graduateproject3.MainActivity.DesignSpinner;
import static com.example.josungryong.graduateproject3.MainActivity.MainActivity;


/**
 * A simple {@link Fragment} subclass.
 */
public class DesignFragment extends Fragment {

    private RecyclerView recyclerView;
    private DesignViewAdapter adapter;
    private StaggeredGridLayoutManager linearLayoutManager;
    private ArrayList<ItemDataDesign> list = new ArrayList<>();

    // DB 관련 변수 //
    private static String[] listDB; // DB의 결과를 받아오는 변수
    private static String[] temp; // listDB를 <br> 단위로 끊어서 받음
    private static String CODE; // 서버로 보낼 쿼리

    private ViewGroup rootView;

    public String where; // mypage에서 온 fragment인지 , 메인의 tab에서 온 fragment인지 판단.
    public String DESIGNER_SEQ; // 디자이너의 업로드 내역을 보여주기 위함.

    @Override
    public void onResume() {
        super.onResume();
        /* 마이페이지 , 메인액티비티 중 어느 곳에서 호출 되었는지 를 표기 */
        if(getArguments() != null) {
            where = getArguments().getString("WHERE");
            if(where.equals("DesignerIn")) {
                DESIGNER_SEQ = getArguments().getString("DESIGNER_SEQ");
            }
            new HttpTask().executeOnExecutor(AsyncTask.THREAD_POOL_EXECUTOR);
        }
        else {
            where = "";
            DesignSpinner.setSelection(0);
            CODE="CODE=";
            new HttpTask().executeOnExecutor(AsyncTask.THREAD_POOL_EXECUTOR);
        }
    }

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {
        /* 마이페이지 , 메인액티비티 중 어느 곳에서 호출 되었는지 를 표기 */
        if(getArguments() != null) {
            where = getArguments().getString("WHERE");
            if(where.equals("DesignerIn")) {
                DESIGNER_SEQ = getArguments().getString("DESIGNER_SEQ");
            }
            new HttpTask().executeOnExecutor(AsyncTask.THREAD_POOL_EXECUTOR);
        }
        else {
            where = "";
            DesignSpinner.setSelection(0);
            CODE="CODE=";
            new HttpTask().executeOnExecutor(AsyncTask.THREAD_POOL_EXECUTOR);
        }

        rootView = (ViewGroup)inflater.inflate(R.layout.fragment_design, container, false);
        recyclerView = (RecyclerView) rootView.findViewById(R.id.recyclerViewDesign);
        recyclerView.setHasFixedSize(true);
        list.clear();
        adapter = new DesignViewAdapter(getActivity(), list);
        linearLayoutManager = new StaggeredGridLayoutManager(2,StaggeredGridLayoutManager.VERTICAL);
        recyclerView.setLayoutManager(linearLayoutManager);
        recyclerView.setAdapter(adapter);

        DesignSpinner.setOnItemSelectedListener(new AdapterView.OnItemSelectedListener() {
            @Override
            public void onItemSelected(AdapterView<?> parent, View view, int position, long id) {
                // 0:전체 1:패션 2:제품 3:커뮤니케이션 4:공예 5:엔터테인먼트 6:공간 7:새분야
                switch (position) {
                    case 0: // 전체
                        CODE="CODE=";
                        new HttpTask().executeOnExecutor(AsyncTask.THREAD_POOL_EXECUTOR);
                        break;
                    case 1: // 패션
                        CODE = "CODE=001";
                        new HttpTask().executeOnExecutor(AsyncTask.THREAD_POOL_EXECUTOR);
                        break;
                    case 2: // 제품
                        CODE = "CODE=002";
                        new HttpTask().executeOnExecutor(AsyncTask.THREAD_POOL_EXECUTOR);
                        break;
                    case 3: // 커뮤니케이션
                        CODE = "CODE=003";
                        new HttpTask().executeOnExecutor(AsyncTask.THREAD_POOL_EXECUTOR);
                        break;
                    case 4: // 공예
                        CODE = "CODE=004";
                        new HttpTask().executeOnExecutor(AsyncTask.THREAD_POOL_EXECUTOR);
                        break;
                    case 5: // 엔터테인먼트
                        CODE = "CODE=005";
                        new HttpTask().executeOnExecutor(AsyncTask.THREAD_POOL_EXECUTOR);
                        break;
                    case 6: // 공강
                        CODE = "CODE=006";
                        new HttpTask().executeOnExecutor(AsyncTask.THREAD_POOL_EXECUTOR);
                        break;
                    case 7: // 새분야
                        CODE = "CODE=007";
                        new HttpTask().executeOnExecutor(AsyncTask.THREAD_POOL_EXECUTOR);
                        break;
                }
            }

            @Override
            public void onNothingSelected(AdapterView<?> parent) {

            }
        });
        return rootView;
    }

    @Override
    public void onPause() {
        super.onPause();
        recyclerView.removeAllViews();
        clear();
    }

    // PHP 검색 쿼리 보내는 class
    public class HttpTask extends AsyncTask<String,Void,String> {
        /* Bitmap bitmap , String image는 전역변수 */
        protected String doInBackground(String... params) {
            // TODO Auto-generated method stub
            if(where.equals("MYPAGE_LIKE")) { // fragment가 mypage의 "관심 디자인"에서 호출 됨 - seq를 전송해야 한다.
                try{
                    String urlPath = "http://58.142.149.131/grad/Grad_mypage.php";
                    Log.i("urlPat" , "value:" + urlPath);

                    String data ="MENU=likeDesign";
                    data += "&MEMBER_SEQ=" + preferences.getString("MEMBERSEQ","");

                    URL url = new URL(urlPath);
                    URLConnection conn = url.openConnection();
                    conn.setDoOutput(true);
                    OutputStreamWriter wr = new OutputStreamWriter(conn.getOutputStream());

                    //추가 할 내용 - 서버 on/off 검사

                    // 문자열 전송
                    Log.i("datavaluelike" , "value:" + data);
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
                    Log.d("mypage_like", "test:" + sb.toString()); // 제목 / 조회수 / 썸네일경로 / 작품설명 / 제작자 넘버 <br>

                    if(sb.toString() != "") {
                        listDB = sb.toString().split("<br>");
                        //Log.d("listDB??" , "listDB:"+listDB);

                        for (int i = 1; i < listDB.length; i++) {
                            temp = split(listDB[i]); // 제작자seq / 디자인카드 SEQ /제목 / 조회수 / 썸네일경로 / 제작자 ,등록자 / 좋아요 유무 \(CHECKED\) , \(UNCHECKED\)<br>
                                                    //          0         1          2        3           4           5                 6
                            Log.i("ListTemp" , "value: " + temp[0] + " " + temp[1] + " " + temp[2] + " " + temp[3] + " " + temp[4] + temp[5] + " " + temp[6]);
                        }
                        return sb.toString();
                    }
                    else {
                        listDB = null;
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

            else if(where.equals("MYPAGE_UPLOAD")) { // fragment가 mypage의 "내가 최근에 등록한 디자인"에서 호출 됨 - seq를 전송해야 한다.
                try{
                    String urlPath = "http://58.142.149.131/grad/Grad_mypage.php";
                    Log.i("urlPat" , "value:" + urlPath);

                    String data ="MENU=uploadDesign";
                    data += "&MEMBER_SEQ=" + preferences.getString("MEMBERSEQ","");

                    URL url = new URL(urlPath);
                    URLConnection conn = url.openConnection();
                    conn.setDoOutput(true);
                    OutputStreamWriter wr = new OutputStreamWriter(conn.getOutputStream());

                    //추가 할 내용 - 서버 on/off 검사

                    // 문자열 전송
                    Log.i("mypage_upload_data" , "value : " + data);
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
                    Log.d("mypage_upload", "test:" + sb.toString()); // 제목 / 조회수 / 썸네일경로 / 작품설명 / 제작자 넘버 / 좋아요 유무 <br>

                    if(sb.toString() != "") {
                        listDB = sb.toString().split("<br>");
                        //Log.d("listDB??" , "listDB:"+listDB);

                        for (int i = 1; i < listDB.length; i++) {
                            temp = split(listDB[i]); // 제작자 seq / 디자인카드 SEQ / 제목 / 조회수 / 썸네일경로 / 제작자 ,등록자 / 좋아요 유무 <br>
                                                    //          0         1             2        3           4           5              6
                            Log.i("ListTemp" , "value: " + temp[0] + " " + temp[1] + " " + temp[2] + " " + temp[3] + " " + temp[4]);
                        }
                        return sb.toString();
                    }
                    else {
                        listDB = null;
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

            else if(where.equals("DesignerIn")) { // fragment가 mypage의 "내가 최근에 등록한 디자인"에서 호출 됨 - seq를 전송해야 한다.
                try{
                    String urlPath = "http://58.142.149.131/grad/Grad_mypage.php";
                    Log.i("urlPat" , "value:" + urlPath);

                    String data ="MENU=uploadDesign";
                    data += "&MEMBER_SEQ=" + DESIGNER_SEQ;

                    URL url = new URL(urlPath);
                    URLConnection conn = url.openConnection();
                    conn.setDoOutput(true);
                    OutputStreamWriter wr = new OutputStreamWriter(conn.getOutputStream());

                    //추가 할 내용 - 서버 on/off 검사

                    // 문자열 전송
                    Log.i("mypage_upload_data" , "value : " + data);
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
                    Log.d("mypage_upload", "test:" + sb.toString()); // 제목 / 조회수 / 썸네일경로 / 작품설명 / 제작자 넘버 / 좋아요 유무 <br>

                    listDB = null;

                    if(sb.toString() != "") {
                        listDB = sb.toString().split("<br>");
                        //Log.d("listDB??" , "listDB:"+listDB);

                        for (int i = 1; i < listDB.length; i++) {
                            temp = split(listDB[i]); // 제작자 seq / 디자인카드 SEQ / 제목 / 조회수 / 썸네일경로 / 제작자 ,등록자 / 좋아요 유무 <br>
                            //          0         1             2        3           4           5              6
                            Log.i("ListTemp" , "value: " + temp[0] + " " + temp[1] + " " + temp[2] + " " + temp[3] + " " + temp[4]);
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

            else { // fragment가 mainactivity에서 호출 됨 - 탭 번호에 따른 값만 받으면 됨
                try{
                    String urlPath = "http://58.142.149.131/grad/Grad_design_list_cate.php";
                    Log.i("urlPat" , "value:" + urlPath);

                    String data = CODE;
                    data += "&MEMBER_SEQ=" + preferences.getString("MEMBERSEQ","");

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
                    Log.d("testquerydesign", "test:" + sb.toString()); // 제목 / 조회수 / 썸네일경로 / 작품설명 / 제작자 넘버 <br>

                    if(sb.toString() != "") {
                        listDB = sb.toString().split("<br>");
                        //Log.d("listDB??" , "listDB:"+listDB);

                        for (int i = 1; i < listDB.length; i++) {
                            temp = split(listDB[i]); // 제작자 seq / 디자인카드 SEQ / 제목 / 조회수 / 썸네일경로 / 제작자 ,등록자 / 좋아요 유무 <br>
                                                    //          0         1             2        3           4           5              6
                            Log.i("ListTemp" , "value: " + temp[0] + " " + temp[1] + " " + temp[2] + " " + temp[3] + " " + temp[4] + " " + temp[5] + " " + temp[6]);
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
        }

        //asyonTask 3번째 인자와 일치 매개변수값 -> doInBackground 리턴값이 전달됨
        //AsynoTask 는 preExcute - doInBackground - postExecute 순으로 자동으로 실행됩니다.
        //ui는 여기서 변경
        protected void onPostExecute(String value){

            if(listDB == null) {
                Toast.makeText(MainActivity, "디자인이 없습니다.", Toast.LENGTH_SHORT).show();
            }
            // 추가작업.. 익셉션 처리해 줄것
            else {
                Log.i("ListDB.length.Design", "value:" + listDB.length);
                //list = createContactsList(10);
                list = createContactsList(listDB.length);
                adapter = new DesignViewAdapter(getActivity(), list);
                linearLayoutManager = new StaggeredGridLayoutManager(2, StaggeredGridLayoutManager.VERTICAL);
                recyclerView.setLayoutManager(linearLayoutManager);
                recyclerView.setAdapter(adapter);

                CODE = null;
            }
            super.onPostExecute(value);
        }

        @Override
        protected void onProgressUpdate(Void... values) {
            super.onProgressUpdate(values);
        }
    }

    // listDB를 #단위로 끊어서 반환
    public String[] split(String temp123) {
        String[] temp2 = temp123.split("#");
        return temp2;
    }
    //commit
    // 카드에 데이터를 넣어준다.. 어뎁터에 list에 contacts를 복사해서 붙이는 것
    public ArrayList<ItemDataDesign> createContactsList(int numContacts) {
        ArrayList<ItemDataDesign> contacts = new ArrayList<ItemDataDesign>();
        for (int i = 1; i < numContacts; i++) {
            temp = split(listDB[i]); // 제작자 seq / 디자인카드 SEQ / 제목 / 조회수 / 썸네일경로 / 제작자 ,등록자 / 좋아요 유무 <br>
                                    //          0         1             2        3           4           5              6
            contacts.add(new ItemDataDesign(temp[1],temp[0],temp[2],temp[4],temp[5],temp[3] , temp[6]));
        }
        return contacts;
    }

    public void clear() {
        list.clear();
        adapter.notifyDataSetChanged();
    }
}