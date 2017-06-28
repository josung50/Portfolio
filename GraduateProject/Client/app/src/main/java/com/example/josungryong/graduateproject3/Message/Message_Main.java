package com.example.josungryong.graduateproject3.Message;

import android.content.Context;
import android.os.Bundle;
import android.support.annotation.Nullable;
import android.support.v7.app.AppCompatActivity;
import android.support.v7.widget.RecyclerView;
import android.support.v7.widget.StaggeredGridLayoutManager;

import com.example.josungryong.graduateproject3.R;

import java.util.ArrayList;

/**
 * Created by josungryong on 2017-05-23.
 */

public class Message_Main extends AppCompatActivity {

    public static RecyclerView recyclerView_message;
    public static MessageViewAdapter adapter_message;
    public static StaggeredGridLayoutManager linearLayoutManager_message;
    public static ArrayList<ItemDataMessage> list_message = new ArrayList<>();

    // DB 관련 변수 //
    public static String[] listDB_message; // DB의 결과를 받아오는 변수
    public static Context Message_Main;
    public static String[] temp_message; // listDB를 <br> 단위로 끊어서 받음

    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_message_main);
        Message_Main = this;

        recyclerView_message = (RecyclerView) findViewById(R.id.recyclerViewMessageMain);
        recyclerView_message.setHasFixedSize(true);
        adapter_message = new MessageViewAdapter(this, list_message);
        linearLayoutManager_message = new StaggeredGridLayoutManager(1,StaggeredGridLayoutManager.VERTICAL);
        recyclerView_message.setLayoutManager(linearLayoutManager_message);
        recyclerView_message.setAdapter(adapter_message);

        new HttpTaskMessageShow().execute();
    }
}
