package com.example.josungryong.graduateproject3.Search.Design_Search_Fragment;

import android.content.Intent;
import android.os.AsyncTask;
import android.os.Bundle;
import android.support.v4.app.Fragment;
import android.support.v7.widget.GridLayoutManager;
import android.support.v7.widget.RecyclerView;
import android.support.v7.widget.StaggeredGridLayoutManager;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Toast;

import com.example.josungryong.graduateproject3.Project_Fragment.MemeberManagement.Management;
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
import static com.example.josungryong.graduateproject3.Search.Search_main.query;

/**
 * A simple {@link Fragment} subclass.
 */
public class SDesignFragment extends Fragment {

    private RecyclerView recyclerView_search;
    private SDesignViewAdapter adapter_search;
    private StaggeredGridLayoutManager linearLayoutManager_search;
    private ArrayList<ItemDataSDesign> list_search = new ArrayList<>();
    // DB 관련 변수 //
    private static String[] listDB; // DB의 결과를 받아오는 변수
    private static String[] temp; // listDB를 <br> 단위로 끊어서 받음

    private ViewGroup rootView;

    public SDesignFragment() {
        // Required empty public constructor
    }

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {
        // Inflate the layout for this fragment
        rootView = (ViewGroup)inflater.inflate(R.layout.fragment_sdesign, container, false);
        recyclerView_search = (RecyclerView) rootView.findViewById(R.id.recyclerViewSDesign);
        recyclerView_search.setHasFixedSize(true);
        list_search.clear();
        adapter_search = new SDesignViewAdapter(getActivity(), list_search);
        linearLayoutManager_search = new StaggeredGridLayoutManager(4,StaggeredGridLayoutManager.VERTICAL);
        recyclerView_search.setLayoutManager(linearLayoutManager_search);
        recyclerView_search.setAdapter(adapter_search);

        new HttpTask().execute(query);

        return rootView;
    }

    // PHP 검색 쿼리 보내는 class
    public class HttpTask extends AsyncTask<String,Void,String> {
        /* Bitmap bitmap , String image는 전역변수 */
        protected String doInBackground(String... params) {
            String query = params[0];
            // TODO Auto-generated method stub
            try{
                String urlPath = "http://58.142.149.131/grad/Grad_search.php";
                Log.i("urlPat" , "value:" + urlPath);

                // 내가 보낼 데이터 (쿼리)
                String data = "SEARCH_TEXT=" + query;
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
                String line;

                while((line = reader.readLine()) != null) {
                    sb.append(line);
                }

                CheckNull = sb.toString();

                if(sb.toString() != "") {
                    Log.d("디버깅_서치", "sb.toString:"+sb.toString());
                    listDB = sb.toString().split("<br>");

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
            Toast.makeText(getActivity(),"로딩중",Toast.LENGTH_LONG).show();
            super.onPreExecute();
        }

        //asyonTask 3번째 인자와 일치 매개변수값 -> doInBackground 리턴값이 전달됨
        //AsynoTask 는 preExcute - doInBackground - postExecute 순으로 자동으로 실행됩니다.
        //ui는 여기서 변경
        protected void onPostExecute(String value){

            if(listDB != null) {
                list_search = createContactsList(listDB.length);
                adapter_search = new SDesignViewAdapter(getActivity(), list_search);
                linearLayoutManager_search = new StaggeredGridLayoutManager(4,StaggeredGridLayoutManager.VERTICAL);
                recyclerView_search.setLayoutManager(linearLayoutManager_search);
                recyclerView_search.setAdapter(adapter_search);
            }
            else {
                Toast.makeText(getContext(), "결과가 없습니다.", Toast.LENGTH_SHORT).show();
            }
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

    // 카드에 데이터를 넣어준다.. 어뎁터에 list에 contacts를 복사해서 붙이는 것
    public ArrayList<ItemDataSDesign> createContactsList(int numContacts) {
        ArrayList<ItemDataSDesign> contacts = new ArrayList<ItemDataSDesign>();
        for (int i = 1; i < numContacts; i++) { // <br>181 #제작자 seq#/resources/km_upload/product/201705202041_20170520_132621.jpg # 좋아요 유무
            temp = split(listDB[i] , "#");
            Log.i("search_tmep" , "value : " + temp[0] + " " + temp[1]);
            contacts.add(new ItemDataSDesign(temp[0], temp[1] , temp[2] , temp[3]));
        }
        return contacts;
    }
}
