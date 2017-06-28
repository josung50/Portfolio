package com.example.josungryong.graduateproject3;

import android.app.Activity;
import android.content.Intent;
import android.content.SharedPreferences;
import android.os.AsyncTask;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.support.v7.widget.StaggeredGridLayoutManager;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Toast;

import android.util.Base64;
import android.util.Log;
import android.widget.TextView;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.UnsupportedEncodingException;
import java.net.URL;
import java.net.URLConnection;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.security.SecureRandom;

import javax.crypto.Cipher;
import javax.crypto.KeyGenerator;
import javax.crypto.spec.SecretKeySpec;


/**
 * Created by josungryong on 2017-03-07.
 */

public class Login extends AppCompatActivity {

    static final String TAG = "SymmetricAlgorithmAES";

    private String str; // PASSWORD
    private String str2; // ID
    private String rtnSHA; // 암호화 된 PASSWORD
    private String[] resultLogin; // 로그인 fail , success
    private EditText password;
    private EditText id;
    Button btn;
    Button button;

    private Button FaceBookLoginButton;
    private Button JoinButton;
    private Button login;

    public static SharedPreferences preferences; // 로그인 정보를 담는다. (로그인 유지)

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_login);

        FaceBookLoginButton = (Button) findViewById(R.id.FacBookLoginButton);
        login = (Button) findViewById(R.id.Login);

        preferences = getSharedPreferences("login_prefs", MODE_PRIVATE);
        if(preferences.getString("LOGIN","").equals("success")) {
            Intent intent = new Intent(Login.this, MainActivity.class);
            startActivity(intent);
        }

    }

    public void onClick(View v) {
        switch (v.getId()) {
            case R.id.FacBookLoginButton: // 페이스북 로그인
                Toast.makeText(getApplicationContext(), "페이스북로그인클릭", Toast.LENGTH_SHORT).show();
                break;

            case R.id.Join: // 회원가입
                JoinButton = (Button) findViewById(R.id.Join);
                Intent intent = new Intent(Login.this, join1.class);
                startActivity(intent);
                break;

            case R.id.Login:
                password = (EditText) findViewById(R.id.Password_OSD);
                id = (EditText) findViewById(R.id.ID_OSD);

                str = password.getText().toString();
                str2 = id.getText().toString();

                new HttpTaskLogin().execute(); // 로그인

                break;
        }
    }

    // PHP 검색 쿼리 보내는 class
    public class HttpTaskLogin extends AsyncTask<String,Void,String> {
        /* Bitmap bitmap , String image는 전역변수 */
        protected String doInBackground(String... params) {
            // TODO Auto-generated method stub
            try{
                String urlPath = "http://58.142.149.131/grad/Grad_Login.php";

                try {
                    MessageDigest sh = MessageDigest.getInstance("SHA-256");
                    sh.update(str.getBytes());
                    byte byteData[] = sh.digest();
                    StringBuffer sb = new StringBuffer();
                    for (int i = 0; i < byteData.length; i++) {
                        sb.append(Integer.toString((byteData[i] & 0xff) + 0x100, 16).substring(1));
                    }
                    rtnSHA = sb.toString();
                } catch (NoSuchAlgorithmException e) {
                    e.printStackTrace();
                    rtnSHA = null;
                }

                // 내가 보낼 데이터 (쿼리, CODE는 전역변수, switch 에서 정해준다.)
                String data = "ID="+str2;
                data += "&PWD="+rtnSHA;

                URL url = new URL(urlPath);
                URLConnection conn = url.openConnection();
                conn.setDoOutput(true);
                OutputStreamWriter wr = new OutputStreamWriter(conn.getOutputStream());

                // 문자열 전송
                wr.write(data);
                wr.flush();
                Log.i("datavalue", " value:" + data);
                BufferedReader reader = new BufferedReader(new InputStreamReader(conn.getInputStream()));

                StringBuilder sb = new StringBuilder();
                String CheckNull = "0";
                String line = null;

                while((line = reader.readLine()) != null) {
                    sb.append(line);
                }
                Log.i("linevalue", "value : " + sb.toString());
                CheckNull = sb.toString();

                if(sb.toString() != "") {
                    resultLogin = split(sb.toString()); // 로그인 여부(success,failed) # 멤버SEQ # 멤버닉네임 # 자기소개 # 프로필URL # ID # PASSWORD
                                                            // 0                            1           2           3           4         5        6
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
            Log.i("resultLogin" , "value : " + resultLogin[0]);
            if ( resultLogin[0].equals("failed")) {
                Toast.makeText(Login.this, "일치하는 ID 혹은 PASSWORD가 없습니다.", Toast.LENGTH_LONG).show();
                preferences = getSharedPreferences("login_prefs", MODE_PRIVATE);
                SharedPreferences.Editor editor = preferences.edit();
                editor.putString("LOGIN" , "failed");
            }
            else if ( resultLogin[0].equals("success") ) {
                preferences = getSharedPreferences("login_prefs", MODE_PRIVATE);
                SharedPreferences.Editor editor = preferences.edit();
                // 로그인 여부(success,failed) # 멤버SEQ # 멤버닉네임 # 프로필URL # 자기소개 # ID # PASSWORD
                //      0                            1           2           3           4      5        6
                // LOGIN # MEMBERSEQ # MEMBERNICK # IMGURL # SELFINFO # ID # PASSWORD
                editor.putString("LOGIN" , "success");
                editor.putString("MEMBERSEQ", resultLogin[1]);
                editor.putString("MEMBERNICK", resultLogin[2]);
                editor.putString("IMGURL", resultLogin[3]);
                editor.putString("SELFINFO", resultLogin[4]);
                editor.putString("ID", resultLogin[5]);
                editor.putString("PASSWORD", resultLogin[6]);
                editor.commit();

                // 로그인 여부(success,failed) # 멤버SEQ # 멤버닉네임 # 프로필URL # 자기소개 # ID # PASSWORD
                //      0                            1           2           3           4      5        6
                Intent intent = new Intent(Login.this, MainActivity.class);
                startActivity(intent);
                finish();
            }
            super.onPostExecute(value);
        }

        @Override
        protected void onProgressUpdate(Void... values) {
            super.onProgressUpdate(values);
        }
    }

    // resultLogin을 #단위로 끊어서 반환
    public String[] split(String temp123) {
        String[] temp2 = temp123.split("#");
        return temp2;
    }
}
