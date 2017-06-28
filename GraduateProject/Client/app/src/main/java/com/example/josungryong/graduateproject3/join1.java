package com.example.josungryong.graduateproject3;

import android.app.Activity;
import android.app.ProgressDialog;
import android.content.Context;
import android.content.Intent;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.util.Log;
import android.view.View;
import android.widget.EditText;
import android.widget.Toast;
import android.os.AsyncTask;


import java.io.BufferedReader;
import java.io.OutputStreamWriter;
import java.net.URLConnection;
import java.net.URLEncoder;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.util.regex.Matcher;
import java.util.regex.Pattern;
import java.net.URL;
import java.io.InputStreamReader;

/**
 * Created by hyeeeeeiny on 2017. 3. 30..
 */

public class join1 extends AppCompatActivity {

    private String rtnSHA; // 암호화 된 PASSWORD
    public static Activity join1;

    EditText pass;//패스워드 입력
    EditText pass_confirm;//패스워드 확인
    EditText id;//id
    EditText id1;
    String id_Result="1";//1
    String id_mark="1";//id중복체크 마크:1



    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_join1);
        join1 = this;
        pass=(EditText) findViewById(R.id.password);//패스워드
        pass_confirm=(EditText) findViewById(R.id.password_confirm);//패스워드 확인

        id=(EditText) findViewById(R.id.id);//다음 버튼

        id1=(EditText) findViewById(R.id.id);// id 중복체크


    }



    public void id_check(View v){//id 중복체크 버튼
        String id_check=id1.getText().toString();//id check
        ID_CHECK(id_check,id_mark);
    }

    public void next(View v){//다음버튼 누르면 실행
        String id_join= id.getText().toString();// id 입력받기
        String PW = pass.getText().toString();//비밀번호 스트링 받기(입력)
        String PW_confirm=pass_confirm.getText().toString();//비밀번호 확인란 스트링 받기

        if(id_join.length()==0)//id 입력하지 않을 경우
        {
            Toast.makeText(getApplicationContext(),"id를 입력해주세요!.",Toast.LENGTH_SHORT).show();
            return;
        }

        //id 이메일 형식 체크
        if(!Pattern.matches("^[_a-zA-Z0-9-\\.]+@[\\.a-zA-Z0-9-]+\\.[a-zA-Z]+$",id_join)){
            Toast.makeText(getApplicationContext(),"이메일 형식의 id를 입력해주세요",Toast.LENGTH_SHORT).show();
            return;
        }
        //비밀번호 유효성
        if(PW.length()==0)//비밀번호 입력하지 않을 경우
        {
            Toast.makeText(getApplicationContext(),"비밀번호를 입력해주세요!.",Toast.LENGTH_SHORT).show();
            return;
        }


        if(!PW.equals(PW_confirm)){//비밀번호가 비밀번호 확인과 같지 않을 때
            pass.setText("");//다시 입력하도록 초기화
            pass_confirm.setText("");
            Toast.makeText(getApplicationContext(),"비밀번호가 일치하지 않습니다.",Toast.LENGTH_SHORT).show();
            return;
        }

        if(!Pattern.matches("^(?=.*\\d)(?=.*[!@])(?=.*[a-zA-Z]).{8,20}$" , PW))//영문+숫자+특수기호로 비번지정
        {
            Toast.makeText(getApplicationContext(),"8자 이상 20자이하로 *영문자, 숫자, 특수기호(!,@)를 포함시켜주세요*.",Toast.LENGTH_SHORT).show();
            return;
        }


        if(id_Result.equals("0") && Pattern.matches("^[_a-zA-Z0-9-\\.]+@[\\.a-zA-Z0-9-]+\\.[a-zA-Z]+$", id_join))//id 중복체크- id 없으면 (마크0)
        {
            Intent intent = new Intent(join1.this, join2.class);// 모든 조건이 만족되면 다음 액티비티로 넘어감
            try {
                MessageDigest sh = MessageDigest.getInstance("SHA-256");
                sh.update(PW.getBytes());
                byte byteData[] = sh.digest();
                StringBuffer sb = new StringBuffer();
                for (int i = 0; i < byteData.length; i++) {
                    sb.append(Integer.toString((byteData[i] & 0xff) + 0x100, 16).substring(1));
                }
                rtnSHA = sb.toString();
                PW = rtnSHA;
            } catch (NoSuchAlgorithmException e) {
                e.printStackTrace();
                rtnSHA = null;
            }
            intent.putExtra("name",id_join); // 아이디(중복체크 다된 아이디)를 다음 액티비티로 넘김.
            intent.putExtra("pw",PW);//비번을 다음 액티비티로 넘김
            startActivity(intent);
        }

        else if(!id_Result.equals("0")){
            Toast.makeText(getApplicationContext(),"id 중복체크를 해주세요!",Toast.LENGTH_SHORT).show();

            return;

        }
    }

    private void insertToDatabase(String name, String address){
        class InsertData extends AsyncTask<String, Void, String>{
            ProgressDialog loading;
            @Override
            protected void onPreExecute() {
                super.onPreExecute();
                loading = ProgressDialog.show(join1.this, "Please Wait", null, true, true);
            }

            @Override
            protected void onPostExecute(String s) {
                super.onPostExecute(s);
                loading.dismiss();
                Toast.makeText(getApplicationContext(),s,Toast.LENGTH_LONG).show();
            }

            @Override
            protected String doInBackground(String... params) {

                try{
                    String ID = (String)params[0];//넘어가는 변수
                    String PWD = (String)params[1];//넘어가는 변수


                    String link="http://58.142.149.131/grad/test.php";
                    String data  = URLEncoder.encode("ID", "UTF-8") + "=" + URLEncoder.encode(ID, "UTF-8");
                    data += "&" + URLEncoder.encode("PWD", "UTF-8") + "=" + URLEncoder.encode(PWD, "UTF-8");

                    URL url = new URL(link);
                    URLConnection conn = url.openConnection();

                    conn.setDoOutput(true);
                    OutputStreamWriter wr = new OutputStreamWriter(conn.getOutputStream());

                    wr.write( data );
                    wr.flush();

                    BufferedReader reader = new BufferedReader(new InputStreamReader(conn.getInputStream()));

                    StringBuilder sb = new StringBuilder();
                    String line = null;

                    // Read Server Response
                    while((line = reader.readLine()) != null)
                    {
                        sb.append(line);
                        break;
                    }
                    return sb.toString();

                }
                catch(Exception e){
                    return new String("Exception: " + e.getMessage());
                }

            }
        }

        InsertData task = new InsertData();

        task.execute(name,address);

    }


    private void ID_CHECK(String id,String mark){//id보내주는 함수

        id1= (EditText) findViewById(R.id.id);
        final String id_join=id1.getText().toString();
        class idcheck extends AsyncTask<String, Void, String>{

            ProgressDialog loading;


            @Override
            protected String doInBackground(String... params) {
                try {
                    String JOIN_ID = (String) params[0];//넘어가는 변수
                    String MARK = (String) params[1];// 중복체크 마크 1


                    //  if(!Pattern.matches("^[_a-zA-Z0-9-\\.]+@[\\.a-zA-Z0-9-]+\\.[a-zA-Z]+$", JOIN_ID))

                    String link = "http://58.142.149.131/grad/Grad_Join.php";
                    String data = "";

                    if (!Pattern.matches("^[_a-zA-Z0-9-\\.]+@[\\.a-zA-Z0-9-]+\\.[a-zA-Z]+$", JOIN_ID)) {
                        id_Result="2";
                        return id_Result;
                    }
                    else {
                        data = URLEncoder.encode("JOIN_ID", "UTF-8") + "=" + URLEncoder.encode(JOIN_ID, "UTF-8");
                        data += "&" + URLEncoder.encode("MARK", "UTF-8") + "=" + URLEncoder.encode(MARK, "UTF-8");
                    }



                    URL url = new URL(link);
                    URLConnection conn = url.openConnection();

                    conn.setDoOutput(true);
                    OutputStreamWriter wr = new OutputStreamWriter(conn.getOutputStream());

                    wr.write(data);
                    wr.flush();

                    BufferedReader reader = new BufferedReader(new InputStreamReader(conn.getInputStream()));

                    StringBuilder sb = new StringBuilder();
                    String line = null;

                    // Read Server Response
                    while ((line = reader.readLine()) != null) {
                        sb.append(line);
                        break;
                    }

                    id_Result = sb.toString();

                    return id_Result;


                }
                catch(Exception e){
                    return new String("Exception: " + e.getMessage());
                }

            }

            @Override
            protected void onPreExecute() {
                super.onPreExecute();
                loading = ProgressDialog.show(join1.this, "Please Wait", null, true, true);
            }

            @Override
            protected void onPostExecute(String s) {
                super.onPostExecute(s);
                loading.dismiss();

                if(id_Result.equals("0"))
                {
                    s= "사용가능한 ID 입니다." ;
                }
                else if(id_Result.equals("1"))
                {
                    s= "이미 존재하는 ID 입니다" ;
                }

                else if (id_Result.equals("2"))
                {

                    s="올바른 이메일형식이 아닙니다.";
                }

                Toast.makeText(getApplicationContext(),s,Toast.LENGTH_LONG).show();
            }

        }

        idcheck task = new idcheck();
        task.execute(id,mark);

    }
}