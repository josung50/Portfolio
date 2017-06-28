package com.example.josungryong.graduateproject3.Main_Fragment;

import android.app.Activity;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.os.AsyncTask;
import android.os.Bundle;
import android.os.StrictMode;
import android.support.v4.app.Fragment;
import android.support.v7.widget.GridLayoutManager;
import android.support.v7.widget.LinearLayoutManager;
import android.support.v7.widget.RecyclerView;
import android.support.v7.widget.StaggeredGridLayoutManager;
import android.text.Layout;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Toast;

import com.example.josungryong.graduateproject3.MainActivity;
import com.example.josungryong.graduateproject3.R;
import com.example.josungryong.graduateproject3.TestServer;

import java.io.BufferedInputStream;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.UnsupportedEncodingException;
import java.net.HttpURLConnection;
import java.net.URL;
import java.net.URLConnection;
import java.util.ArrayList;


/**
 * A simple {@link Fragment} subclass.
 */
public class MainFragment extends Fragment {

    private StaggeredGridLayoutManager linearLayoutManager;
    private RecyclerView recyclerView;
    private MainViewAdapter adapter;
    private ArrayList<WordItemData> list = new ArrayList<>();
    public ArrayList<WordItemData> contacts = new ArrayList<WordItemData>();

    // DB 관련 변수 //
    private static String[] listDB; // DB의 결과를 받아오는 변수
    private static String[] temp; // listDB를 <br> 단위로 끊어서 받음

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {
        ViewGroup rootView = (ViewGroup)inflater.inflate(R.layout.fragment_main, container, false);

        new HttpTask().executeOnExecutor(AsyncTask.THREAD_POOL_EXECUTOR);

        recyclerView = (RecyclerView) rootView.findViewById(R.id.recyclerView);
        recyclerView.setHasFixedSize(true);
        Log.i("list55" , "time");
        adapter = new MainViewAdapter(getActivity(), list);
        linearLayoutManager = new StaggeredGridLayoutManager(2,StaggeredGridLayoutManager.VERTICAL);
        recyclerView.setLayoutManager(linearLayoutManager);
        recyclerView.setAdapter(adapter);

        return rootView;
    }

    // PHP 검색 쿼리 보내는 class
    public class HttpTask extends AsyncTask<String,Void,String> {
        /* Bitmap bitmap , String image는 전역변수 */
        protected String doInBackground(String... params) {
            // TODO Auto-generated method stub
            try{
                String urlPath = "http://58.142.149.131/grad/Grad_main.php";
                Log.i("urlPat" , "value:" + urlPath);

                // 내가 보낼 데이터 (쿼리)
                //String data = "";
                //String data = "lat=" + latitude;
                //data += "&lng=" + longitude;

                URL url = new URL(urlPath);
                URLConnection conn = url.openConnection();
                conn.setDoOutput(true);
                OutputStreamWriter wr = new OutputStreamWriter(conn.getOutputStream());

                //추가 할 내용 - 서버 on/off 검사

                // 문자열 전송
                //wr.write(data);
                //wr.flush();

                BufferedReader reader = new BufferedReader(new InputStreamReader(conn.getInputStream()));

                StringBuilder sb = new StringBuilder();
                String CheckNull = "0";
                String line;

                while((line = reader.readLine()) != null) {
                    sb.append(line);
                }

                CheckNull = sb.toString();
                Log.d("testquery", "test:" + sb.toString()); // 제목 / 조회수 / 썸네일경로 / 작품설명 / 제작자 넘버 <br>

                if(sb.toString() != "") {
                    Log.d("디버깅123", "sb.toString:"+sb.toString());
                    listDB = sb.toString().split("<br>");
                    Log.d("listDB??" , "listDB:"+listDB);

                    /* 데이터 로그용
                    for (int i = 0; i < listDB.length; i++) {
                        temp = split(listDB[i]); // 제목 / 조회수 / 썸네일경로 / 작품설명 / 제작자 넘버 <br>
                                                //  0         1        2        3           4
                        Log.i("ListTemp" , "value: " + temp[0] + " " + temp[1] + " " + temp[2] + " " + temp[3] + " " + temp[4]);
                    }*/
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

        @Override
        protected void onPreExecute() {
            //Toast.makeText(getActivity(),"로딩중",Toast.LENGTH_LONG).show();
            super.onPreExecute();
        }

        //asyonTask 3번째 인자와 일치 매개변수값 -> doInBackground 리턴값이 전달됨
        //AsynoTask 는 preExcute - doInBackground - postExecute 순으로 자동으로 실행됩니다.
        //ui는 여기서 변경
        protected void onPostExecute(String value){

            // 추가작업.. 익셉션 처리
            Log.i("ListDB.length", "value:" + listDB.length);

            list = createContactsList(listDB.length);
            adapter = new MainViewAdapter(getActivity(), list);
            linearLayoutManager = new StaggeredGridLayoutManager(2,StaggeredGridLayoutManager.VERTICAL);
            recyclerView.setLayoutManager(linearLayoutManager);
            recyclerView.setAdapter(adapter);
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
    public ArrayList<WordItemData> createContactsList(int numContacts) {
        ArrayList<WordItemData> contacts = new ArrayList<WordItemData>();
        for (int i = 1; i < numContacts; i++) {
            temp = split(listDB[i]); // 제목 / 조회수 / 썸네일경로 / 작품설명 / 제작자 넘버 <br>
                                    //      0   1       2               3           4
            Log.i("tempsize" , "value:" + temp.length + "//" + temp[0] + " " + temp[1] + " " + temp[2] + " " + temp[3]);
            contacts.add(new WordItemData(temp[0], temp[3], temp[2], temp[4] , temp[1]));
        }
        return contacts;
    }

    @Override
    public void onResume() {
        super.onResume();
        new HttpTask().executeOnExecutor(AsyncTask.THREAD_POOL_EXECUTOR);
    }

    @Override
    public void onPause() {
        super.onPause();
        list.clear();
        adapter.notifyDataSetChanged();
        recyclerView.removeAllViews();
    }
}