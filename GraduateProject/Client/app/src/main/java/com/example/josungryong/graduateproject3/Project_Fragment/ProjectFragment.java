package com.example.josungryong.graduateproject3.Project_Fragment;


import android.content.Intent;
import android.os.AsyncTask;
import android.os.Bundle;
import android.support.v4.app.Fragment;
import android.support.v7.widget.RecyclerView;
import android.support.v7.widget.StaggeredGridLayoutManager;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.TextView;
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
 * A simple {@link Fragment} subclass.
 */
public class ProjectFragment extends Fragment {

    private RecyclerView recyclerView;
    private ProjectViewAdapter adapter;
    private StaggeredGridLayoutManager linearLayoutManager;
    private ArrayList<ItemDataProject> list = new ArrayList<>();

    // DB 관련 변수 //
    private static String[] listDB; // DB의 결과를 받아오는 변수
    private static String[] temp; // listDB를 <br> 단위로 끊어서 받음
    private static String CODE; // 서버로 보낼 쿼리

    private ViewGroup rootView;

    // 탭 //
    private Button project_write;

    private String where;

    @Override
    public void onResume() {
        super.onResume();
        recyclerView.removeAllViews();
        if(getArguments() != null) {
            where = getArguments().getString("WHERE");
            new HttpTask().executeOnExecutor(AsyncTask.THREAD_POOL_EXECUTOR);
        }
        else {
            where = "";
            CODE="CODE=";
            new HttpTask().executeOnExecutor(AsyncTask.THREAD_POOL_EXECUTOR);
        }
    }

    @Override
    public void onPause() {
        super.onPause();
        list.clear();
        adapter.notifyDataSetChanged();
        recyclerView.removeAllViews();
    }

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {
        if(getArguments() != null) {
            where = getArguments().getString("WHERE");
            new HttpTask().executeOnExecutor(AsyncTask.THREAD_POOL_EXECUTOR);
        }
        else {
            where = "";
            CODE="CODE=";
            new HttpTask().executeOnExecutor(AsyncTask.THREAD_POOL_EXECUTOR);
        }

        rootView = (ViewGroup)inflater.inflate(R.layout.fragment_project, container, false);
        recyclerView = (RecyclerView) rootView.findViewById(R.id.recyclerViewProject);

        recyclerView.setHasFixedSize(true);
        adapter = new ProjectViewAdapter(getActivity(), list);
        linearLayoutManager = new StaggeredGridLayoutManager(2,StaggeredGridLayoutManager.VERTICAL);
        recyclerView.setLayoutManager(linearLayoutManager);
        recyclerView.setAdapter(adapter);
        Log.e("Frag", "ProjectFragment:"+recyclerView.getAdapter().getItemCount());

        return rootView;
        // Inflate the layout for this fragment
        //return inflater.inflate(R.layout.fragment_main, container, false);
    }

    // PHP 검색 쿼리 보내는 class
    public class HttpTask extends AsyncTask<String,Void,String> {
        /* Bitmap bitmap , String image는 전역변수 */
        protected String doInBackground(String... params) {
            // TODO Auto-generated method stub
            Log.i("wherevalue" , "value : " + where);

            if(where.equals("MYPAGE_PROJECT")){ // 마이페이지에서 프로젝트 프래그먼트 호출
                try{
                    String urlPath = "http://58.142.149.131/grad/Grad_mypage.php";
                    Log.i("urlPat" , "value:" + urlPath);

                    // 내가 보낼 데이터 (쿼리, CODE는 전역변수, switch 에서 정해준다.)
                    String data = "MENU=myProject";
                    data +="&MEMBER_SEQ=" + preferences.getString("MEMBERSEQ","");

                    URL url = new URL(urlPath);
                    URLConnection conn = url.openConnection();
                    conn.setDoOutput(true);
                    OutputStreamWriter wr = new OutputStreamWriter(conn.getOutputStream());

                    //추가 할 내용 - 서버 on/off 검사

                    // 문자열 전송
                    wr.write(data);
                    wr.flush();

                    Log.i("datavalue" , "value :" + data);
                    BufferedReader reader = new BufferedReader(new InputStreamReader(conn.getInputStream()));

                    StringBuilder sb = new StringBuilder();
                    String CheckNull = "0";
                    String line = null;

                    while((line = reader.readLine()) != null) {
                        sb.append(line);
                    }

                    CheckNull = sb.toString();
                    Log.i("sbvalueproject", " value :" + sb.toString());

                    if(sb.toString() != "") {
                        listDB = sb.toString().split("<br>");
                        for (int i = 1; i < listDB.length; i++) {
                            Log.d("listDBmypage" , "listDB :"+ listDB[i]);
                            temp = split(listDB[i]); // 프로젝트 이름 / 프로젝트 생성자 / 프로젝트 생성자 seq / 썸네일경로 / 멤버수 / 파일수 / 프로젝트 고유 SEQ / 그룹 멤버 전원 SEQ<br>
                                                    //          0         1                     2        3          4       5                   6                   7
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
            }
            else{ // 메인액티비티에서 프래그먼트 호출
                try{
                    String urlPath = "http://58.142.149.131/grad/Grad_project_list.php";
                    Log.i("urlPat" , "value:" + urlPath);

                    // 내가 보낼 데이터 (쿼리, CODE는 전역변수, switch 에서 정해준다.)
                    String data = CODE;

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
                    Log.i("mainprojectvale" , "value : " + sb.toString());

                    CheckNull = sb.toString();

                    if(sb.toString() != "") {
                        listDB = sb.toString().split("<br>");
                        //Log.d("listDB??" , "listDB:"+listDB);

                        for (int i = 1; i < listDB.length; i++) {
                            Log.i("mainprojectvalue" , "value : " + listDB[i]);
                            temp = split(listDB[i]); // 프로젝트 이름 / 프로젝트 생성자 / 프로젝트 생성자 seq / 썸네일경로 / 멤버수 / 파일수 / 프로젝트 고유 SEQ / 그룹 멤버 전원 SEQ<br>
                                                    //          0         1                     2                   3          4       5                   6            7
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

            }
            //오류시 null 반환
            return null;
        }

        @Override
        protected void onPreExecute() {
            //Toast.makeText(getActivity(),"로딩중",Toast.LENGTH_LONG).show();
            super.onPreExecute();
        }

        //asyonTask 3번째 인자와 일치 매개변수값 -> doInBackground 리턴값이 전달됨
        //AsynoTask 는 preExcute - doInBackground - postExecute 순으로 자동으로 실행됩니다.
        //ui는 여기서 변경
        protected void onPostExecute(String value){
            if(listDB == null) {
                recyclerView.removeAllViews();
                Toast.makeText(getContext(), "참여하고 있는 프로젝트가 업습니다.", Toast.LENGTH_SHORT).show();
                return;
            }
            // 추가작업.. 익셉션 처리해 줄것
            Log.i("ListDB.length.Design", "value:" + listDB.length);
            //list = createContactsList(10);
            list = createContactsList(listDB.length);
            adapter = new ProjectViewAdapter(getActivity(), list);
            linearLayoutManager = new StaggeredGridLayoutManager(2,StaggeredGridLayoutManager.VERTICAL);
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
    public String[] split(String temp123) {
        String[] temp2 = temp123.split("#");
        return temp2;
    }

    // 카드에 데이터를 넣어준다.. 어뎁터에 list에 contacts를 복사해서 붙이는 것
    public ArrayList<ItemDataProject> createContactsList(int numContacts) {
        ArrayList<ItemDataProject> contacts = new ArrayList<ItemDataProject>();
        for (int i = 1; i < numContacts; i++) {
            temp = split(listDB[i]); // 프로젝트 이름 / 프로젝트 제작자 / 프로젝트 생성자 seq / 썸네일경로 / 멤버 수 / 파일 수 / 고유 seq  / 멤버들의 전원 SEQ<BR>
                                    //     0                    1           2                   3           4               5          6            7
            contacts.add(new ItemDataProject(temp[0], temp[1] , temp[2], temp[3], temp[4] , temp[5] , temp[6] , temp[7]));
            Log.i("projectinfovalue" , "value : " + temp[0] + " " + temp[1] + " " + temp[2] + " " + temp[3] + " " + temp[4] + " " + temp[5] + " " + temp[6] + " " + temp[7]);
            // 썸네일 경로 , 프로젝트 이름, 프로젝즈 제작자 , 제작자 seq , 멤버 수 , 파일 수 순 // 고유 seq(프로젝트) 는 변수에만 저장 추가적으로 그룹 멤버들의 SEQ
        }
        return contacts;
    }
}