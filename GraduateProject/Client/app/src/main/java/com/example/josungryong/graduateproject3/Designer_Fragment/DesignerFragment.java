package com.example.josungryong.graduateproject3.Designer_Fragment;


import android.os.AsyncTask;
import android.os.Bundle;
import android.support.design.widget.NavigationView;
import android.support.v4.app.Fragment;
import android.support.v4.widget.DrawerLayout;
import android.support.v7.app.ActionBarDrawerToggle;
import android.support.v7.widget.RecyclerView;
import android.support.v7.widget.StaggeredGridLayoutManager;
import android.support.v7.widget.Toolbar;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.AdapterView;
import android.widget.Toast;

import com.example.josungryong.graduateproject3.R;
import com.ramotion.foldingcell.FoldingCell;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.UnsupportedEncodingException;
import java.net.URL;
import java.net.URLConnection;
import java.util.ArrayList;

import static com.example.josungryong.graduateproject3.MainActivity.DesignerSpinner;
import static com.example.josungryong.graduateproject3.MainActivity.MainActivity;


/**
 * A simple {@link Fragment} subclass.
 */
public class DesignerFragment extends Fragment {

    public static RecyclerView recyclerView;
    private DesignerViewAdapter adapter;
    private StaggeredGridLayoutManager linearLayoutManager;
    private ArrayList<ItemDataDesigner> list = new ArrayList<>();

    // DB 관련 변수 //
    private static String[] listDB; // DB의 결과를 받아오는 변수
    private static String[] temp; // listDB를 <br> 단위로 끊어서 받음
    private static String CODE; // 서버로 보낼 쿼리

    private ViewGroup rootView;
    public DesignerFragment() {
        // Required empty public constructor
    }

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {
        rootView = (ViewGroup)inflater.inflate(R.layout.fragment_designer, container, false);

        DesignerSpinner.setSelection(0);
        CODE="CODE=";
        new HttpTask().executeOnExecutor(AsyncTask.THREAD_POOL_EXECUTOR);

        recyclerView = (RecyclerView) rootView.findViewById(R.id.recyclerViewDesigner);
        recyclerView.setHasFixedSize(true);
        adapter = new DesignerViewAdapter(getActivity(), list);
        linearLayoutManager = new StaggeredGridLayoutManager(1,StaggeredGridLayoutManager.VERTICAL);
        recyclerView.setLayoutManager(linearLayoutManager);
        recyclerView.setAdapter(adapter);

        DesignerSpinner.setOnItemSelectedListener(new AdapterView.OnItemSelectedListener() {
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
        // Inflate the layout for this fragment
        return rootView;
    }

    @Override
    public void onResume() {
        super.onResume();
        recyclerView.removeAllViews();
        CODE="";
        new HttpTask().executeOnExecutor(AsyncTask.THREAD_POOL_EXECUTOR);
    }

    @Override
    public void onPause() {
        super.onPause();
        list.clear();
        adapter.notifyDataSetChanged();
        recyclerView.removeAllViews();
    }

    // PHP 검색 쿼리 보내는 class
    public class HttpTask extends AsyncTask<String,Void,String> {
        protected String doInBackground(String... params) {
            // TODO Auto-generated method stub
            try{
                String urlPath = "http://58.142.149.131/grad/Grad_designer.php";
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

                CheckNull = sb.toString();
                Log.d("testquerydesigner", "test:" + sb.toString());

                if(sb.toString() != "") {
                    listDB = sb.toString().split("<br>");
                    //Log.d("listDB??" , "listDB:"+listDB);

                    for (int i = 1; i < listDB.length; i++) {
                        Log.i("designervalue" , "value : " + listDB[i]);
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
            adapter = new DesignerViewAdapter(getActivity(), list);
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
    public ArrayList<ItemDataDesigner> createContactsList(int numContacts) {
        ArrayList<ItemDataDesigner> contacts = new ArrayList<ItemDataDesigner>();
        for (int i = 1; i < numContacts; i++) {
            temp = split(listDB[i] , "a!PJP"); // 순서대로 디자이너 seq , 디자이너 이름 , 디자이너 프로필사진 uri , 자기소개 내용 , 분야 , 올린 게시물 갯수 , 조회수 , 받은 좋아요 수 , SEQ&URI::(uriset)
                                                //          0                   1               2                       3               4           5               6       7               8
            if(temp.length <9) { // 업로드 게시물이 없는 경우
                contacts.add(new ItemDataDesigner(temp[0], temp[1], temp[2], temp[3], temp[4], temp[5], temp[6], temp[7], "NOTUPLOAD"));
            }

            else { // 업로드 게시물이 존재하는 경우
                contacts.add(new ItemDataDesigner(temp[0], temp[1], temp[2], temp[3], temp[4], temp[5], temp[6], temp[7], temp[8]));
            }
        }
        return contacts;
    }
}