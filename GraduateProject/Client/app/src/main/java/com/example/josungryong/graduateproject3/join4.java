package com.example.josungryong.graduateproject3;

import android.content.Intent;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ImageView;
import android.widget.Toast;

/**
 * Created by hyeeeeeiny on 2017. 3. 30..
 */

public class join4 extends AppCompatActivity {

    String id;//넘어온 아이디 변수
    String password;//비밀번호
    ImageView imgview;
    Button tomain;//메인으로가는버튼

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_join4);

        tomain=(Button)  findViewById(R.id.tomain);

        Intent intent = getIntent();
        String name = intent.getStringExtra("name");//join3에서 넘어온 아이디 받기(넘어온데이터 저장)
        String pw=intent.getStringExtra("pw");//join3에서 넘어온 비번 받기
        //Bitmap

//        imgview=(ImageView) findViewById(R.id.cc);

        Toast.makeText(getApplicationContext(),name,Toast.LENGTH_LONG).show();
        Toast.makeText(getApplicationContext(),pw,Toast.LENGTH_LONG).show();


    }

    public void ToMain(View v){
        join1.join1.finish();
        join2.join2.finish();
        join3.join3.finish();
        Intent intent = new Intent(join4.this,Login.class);//메인화면으로 이동
        Toast.makeText(this, "로그인을 해주세요.", Toast.LENGTH_SHORT).show();
        startActivity(intent);
        finish();

    }
}