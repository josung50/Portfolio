package com.example.josungryong.graduateproject3;

import android.app.Activity;
import android.app.ProgressDialog;
import android.content.Context;
import android.content.Intent;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.net.Uri;
import android.os.AsyncTask;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.util.Log;
import android.view.View;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.EditText;
import android.widget.ImageView;
import android.widget.Spinner;
import android.widget.Toast;

import java.io.BufferedReader;
import java.io.DataOutputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.net.HttpURLConnection;
import java.net.MalformedURLException;
import java.net.URL;
import java.net.URLConnection;
import java.net.URLEncoder;
import java.sql.Time;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.regex.Pattern;

import static com.example.josungryong.graduateproject3.R.id.section1;
import static com.example.josungryong.graduateproject3.join2.mImageCaptureUri_join;


/**
 * Created by hyeeeeeiny on 2017. 3. 30..
 */



public class join3 extends AppCompatActivity {
    public static Activity join3;

    /* 이미지 통신에 필요한 변수 */
    int serverResponseCode = 0; // 서버 상태 반환 (이미지 통신)
    public String FilePath; // 이미지 절대경로(총 경로)
    public String FileName; // 절대경로에서 파일명만 스플릿(이미지 이름)

    Spinner section1;//= (Spinner)findViewById(R.id.section1);
    Spinner section2;//=(Spinner) findViewById((R.id.section2);
    Spinner residence;

    EditText presentation;

    String cate_mark="3";

    String id;//넘어온 아이디를 저장할 전역변수
    String password;//넘어온 비번을 저장할 전역변수
    String uri;//불러온 프로필사진 저장할 전역변수
    String nick;// 넘어온 닉네임을 저장할 전역변수
    String sec1;//넘겨줄 카테고리 1
    String sec2;//넘겨줄 캬테고리 2
    String Residece;//넘겨줄 거주지
    String pre;//  넘겨줄 자기소개란

    String mark= "3";//데이터 넘길때 주는 마크 =3

    private void populateSpinners() { //나의 카테고리 첫번째 section
        ArrayAdapter<CharSequence> fAdapter;
        fAdapter = ArrayAdapter.createFromResource(this,
                R.array.depth1,
                android.R.layout.simple_spinner_item);
        fAdapter.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);
        section1.setAdapter(fAdapter);
    }
    private void residenceSpinners() { //거주지 선택(drop down)
        ArrayAdapter<CharSequence> fAdapter;
        fAdapter = ArrayAdapter.createFromResource(this,
                R.array.residence,
                android.R.layout.simple_spinner_item);
        fAdapter.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);
        residence.setAdapter(fAdapter);

    }

    private void populateSubSpinners(int itemNum) {//나의 카테고리 두번째 section
        ArrayAdapter<CharSequence> fAdapter;
        fAdapter = ArrayAdapter.createFromResource(this,
                itemNum,
                android.R.layout.simple_spinner_item);
        fAdapter.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);
        section2.setAdapter(fAdapter);

    }

    private AdapterView.OnItemSelectedListener spinSelectedlistener =
            new AdapterView.OnItemSelectedListener() {
                @Override
                public void onItemSelected(AdapterView<?> parent, View view,
                                           int position, long id) {
                    switch(position){
                        case (0):
                            populateSubSpinners(R.array.전체);
                            break;
                        case (1):
                            populateSubSpinners(R.array.패션);
                            break;
                        case (2):
                            populateSubSpinners(R.array.제품);
                            break;
                        case (3):
                            populateSubSpinners(R.array.커뮤니케이션);
                            break;
                        case (4):
                            populateSubSpinners(R.array.공예);
                            break;
                        case (5):
                            populateSubSpinners(R.array.공간);
                            break;
                        case (6):
                            populateSubSpinners(R.array.엔터테인먼트);
                            break;
                        case (7):
                            populateSubSpinners(R.array.새분야);
                            break;
                    }


                    sec1= (String)section1.getSelectedItem();

                }
                @Override
                public void onNothingSelected(AdapterView<?> parent) {

                }

            };
    private AdapterView.OnItemSelectedListener sec2Selectedlistener =
            new AdapterView.OnItemSelectedListener() {
                @Override
                public void onItemSelected(AdapterView<?> parent, View view,
                                           int position, long id) {


                    sec2=(String) section2.getSelectedItem();




                }
                @Override
                public void onNothingSelected(AdapterView<?> parent) {

                }

            };
    private AdapterView.OnItemSelectedListener resiSelectedlistener =
            new AdapterView.OnItemSelectedListener() {
                @Override
                public void onItemSelected(AdapterView<?> parent, View view,
                                           int position, long id) {

                    Residece=(String) residence.getSelectedItem();
                    // sec2=(String) section2.getSelectedItem();




                }
                @Override
                public void onNothingSelected(AdapterView<?> parent) {

                }

            };


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_join3);
        join3 = this;

        presentation=(EditText)  findViewById(R.id.presentation);//자기소개란
        //Spinner01초기화
        section1 = (Spinner)findViewById(R.id.section1);
        populateSpinners();

        //Spinner02초기화
        section2 = (Spinner)findViewById(R.id.section2);
        populateSubSpinners(R.array.depth1);


        residence= (Spinner) findViewById(R.id.residence);
        residenceSpinners();

        section1.setOnItemSelectedListener(spinSelectedlistener);
        section2.setOnItemSelectedListener(sec2Selectedlistener);
        residence.setOnItemSelectedListener(resiSelectedlistener);

        Intent intent = getIntent();

        id= intent.getStringExtra("name");//join2에서 넘어온 아이디 받기(넘어온데이터 저장)
        password=intent.getStringExtra("pw");//join2에서 넘어온 비번 받기
        nick=intent.getStringExtra("nickname");//join2에서 넘어온 닉네임 받기(스트링)
    }

    private void insertToDatabase(String id,String password,String uri,String nick,String sec1,String sec2,String pre,String Residence, String mark){
        class InsertData extends AsyncTask<String, Void, String>{
            ProgressDialog loading;
            @Override
            protected void onPreExecute() {
                super.onPreExecute();
                loading = ProgressDialog.show(join3.this, "Please Wait", null, true, true);
            }
            @Override
            protected void onPostExecute(String s) {
                super.onPostExecute(s);
                loading.dismiss();
            }

            @Override
            protected String doInBackground(String... params) {

                try{
                    String JOIN_ID = (String)params[0];//넘어가는 변수
                    String PW = (String)params[1];//넘어가는 변수
                    String URI=(String)params[2];
                    String U_NAME=(String)params[3];
                    String SEC1=(String)params[4];
                    String SEC2=(String)params[5];
                    String PRESENTATION=(String)params[6];
                    String RESIDENCE=(String)params[7];
                    String MARK=(String)params[8];


                    String link="http://58.142.149.131/grad/Grad_Join.php";

                    String data  = "JOIN_ID=" + JOIN_ID;//아이디 전달
                    data += "&PW=" + PW;//비밀번호 전달
                    data +="&URI=" + URI;//프로필사진 uri 전달

                    data +="&U_NAME=" + U_NAME;//닉네임전달
                    data +="&SEC1=" + SEC1;//카테고리1 전달

                    data +="&SEC2=" + SEC2;//카테고리2 전달

                    data +="&PRESENTATION=" + PRESENTATION;//자기소개 전달

                    data +="&RESIDENCE=" + RESIDENCE;//거주지 전달
                    data +="&MARK=" + MARK;//마크 3
                    /*
                    data += "&" + URLEncoder.encode("PW", "UTF-8") + "=" + URLEncoder.encode(PW, "UTF-8");//비밀번호 전달
                    data +="&" + URLEncoder.encode("URI", "UTF-8") + "=" + URLEncoder.encode(URI, "UTF-8");//프로필사진 uri 전달

                    data +="&" + URLEncoder.encode("U_NAME", "UTF-8") + "=" + URLEncoder.encode(U_NAME, "UTF-8");//닉네임전달
                    data +="&" + URLEncoder.encode("SEC1", "UTF-8") + "=" + URLEncoder.encode(SEC1, "UTF-8");//카테고리1 전달

                    data +="&" + URLEncoder.encode("SEC2", "UTF-8") + "=" + URLEncoder.encode(SEC2, "UTF-8");//카테고리2 전달

                    data +="&" + URLEncoder.encode("PRESENTATION", "UTF-8") + "=" + URLEncoder.encode(PRESENTATION, "UTF-8");//자기소개 전달

                    data +="&" + URLEncoder.encode("RESIDENCE", "UTF-8") + "=" + URLEncoder.encode(RESIDENCE, "UTF-8");//거주지 전달
                    data +="&" + URLEncoder.encode("MARK", "UTF-8") + "=" + URLEncoder.encode(MARK, "UTF-8");//마크 3
                    */


                    URL url = new URL(link);
                    URLConnection conn = url.openConnection();

                    conn.setDoOutput(true);
                    OutputStreamWriter wr = new OutputStreamWriter(conn.getOutputStream());

                    Log.i("datajoin" , "value :" + data);
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
                    return null;
                    //return new String("Exception: " + e.getMessage());
                }

            }
        }
        Log.i("valuevalue2" , " value : " + id + " " + password + " " + nick + " " + sec1);
        new InsertData().execute(id,password,uri,nick,sec1,sec2,pre,Residence,mark);
    }

    public void next(View v){
        pre= presentation.getText().toString();//자기소개란
        // sec1=section1.
        if(sec1.equals("전체") )// 카테고리 선택하지 않을 경우
        {
            Toast.makeText(getApplicationContext(),"카데고리를 선택해주세요!.",Toast.LENGTH_SHORT).show();
            return;
        }
        if(pre.length()==0){
            Toast.makeText(getApplicationContext(),"자기소개란을 입력해주세요",Toast.LENGTH_SHORT).show();
            return;
        }
        if(Residece.equals("전체")){
            Toast.makeText(getApplicationContext(),"거주지를 선택해주세요",Toast.LENGTH_SHORT).show();
            return;
        }

        FilePath = ImageUtill.getRealPathFromURI(this, mImageCaptureUri_join);
        FileName = ImageUtill.uploadFileName(FilePath);
        Log.i("urilistvalue" , "value : " + FilePath);
        Log.i("urilistvalue2" , "value : " + FileName);
        String Time_FileName_temp = CurrentTime() + FileName;
        uploadFile(FilePath , Time_FileName_temp);

        insertToDatabase(id,password,Time_FileName_temp,nick,sec1,sec2,pre,Residece,mark);
        Log.i("valuevalue" , " value : " + id + " " + password + " " + nick + " " + sec1);
        Intent intent = new Intent(join3.this, join4.class);
        startActivity(intent);
    }

    /* 서버로 이미지 파일을 보내는 함수 */
    public int uploadFile(String sourceFileUri , String Time_FileName_temp) {
        String upLoadServerUri = "http://58.142.149.131/grad/imgUpload_profile.php";

        HttpURLConnection conn = null;
        DataOutputStream dos = null;
        String lineEnd = "\r\n";
        String twoHyphens = "--";
        String boundary = "*****";
        int bytesRead, bytesAvailable, bufferSize;
        byte[] buffer;
        int maxBufferSize = 1 * 4024 * 4024;

        File sourceFile = new File(sourceFileUri);

        if (!sourceFile.isFile()) { // 파일이 존재 하지 않으면
            runOnUiThread(new Runnable() {
                public void run() {
                }
            });
            return 0;
        }

        else // 존재 하면
        {
            try {
                // open a URL connection to the Servlet
                FileInputStream fileInputStream = new FileInputStream(sourceFile);
                URL url = new URL(upLoadServerUri);

                // Open a HTTP  connection to  the URL
                conn = (HttpURLConnection) url.openConnection();
                conn.setDoInput(true); // Allow Inputs
                conn.setDoOutput(true); // Allow Outputs
                conn.setUseCaches(false); // Don't use a Cached Copy
                conn.setRequestMethod("POST");
                conn.setRequestProperty("Connection", "Keep-Alive");
                conn.setRequestProperty("ENCTYPE", "multipart/form-data");
                conn.setRequestProperty("Content-Type", "multipart/form-data;boundary=" + boundary);
                conn.setRequestProperty("uploaded_file", sourceFileUri);

                dos = new DataOutputStream(conn.getOutputStream());
                dos.writeBytes(twoHyphens + boundary + lineEnd);
                dos.writeBytes("Content-Disposition: form-data; name=\"uploaded_file\";filename=\"" + Time_FileName_temp + "\"" + lineEnd);
                dos.writeBytes(lineEnd);

                // create a buffer of  maximum size
                bytesAvailable = fileInputStream.available();
                bufferSize = Math.min(bytesAvailable, maxBufferSize);
                buffer = new byte[bufferSize];

                // read file and write it into form...
                bytesRead = fileInputStream.read(buffer, 0, bufferSize);
                while (bytesRead > 0) {
                    dos.write(buffer, 0, bufferSize);
                    bytesAvailable = fileInputStream.available();
                    bufferSize = Math.min(bytesAvailable, maxBufferSize);
                    bytesRead = fileInputStream.read(buffer, 0, bufferSize);
                }

                // send multipart form data necesssary after file data...
                dos.writeBytes(lineEnd);
                dos.writeBytes(twoHyphens + boundary + twoHyphens + lineEnd);

                // Responses from the server (code and message)
                serverResponseCode = conn.getResponseCode();
                String serverResponseMessage = conn.getResponseMessage();
                Log.i("uploadFile", "HTTP Response is : " + serverResponseMessage + ": " + serverResponseCode);
                if(serverResponseCode == 200){
                    runOnUiThread(new Runnable() {
                        public void run() {
                        }
                    });
                }

                //close the streams //
                fileInputStream.close();
                dos.flush();
                dos.close();
            } catch (MalformedURLException ex) {
                //dialog.dismiss();
                ex.printStackTrace();

                runOnUiThread(new Runnable() {
                    public void run() {
                    }
                });

                Log.e("Upload file to server", "error: " + ex.getMessage(), ex);
            } catch (Exception e) {
                //dialog.dismiss();
                e.printStackTrace();

                runOnUiThread(new Runnable() {
                    public void run() {
                        //Toast.makeText(Write.this, "Got Exception : see logcat ", Toast.LENGTH_SHORT).show();
                    }
                });
                //Log.e("Upload file to server Exception", "Exception : " + e.getMessage(), e);
            }

            //dialog.dismiss();
            return serverResponseCode;
        } // End else block
    }

    /* 작성 시간 체크 */
    public String CurrentTime() {
        SimpleDateFormat dateFormat = new  SimpleDateFormat("yyyyMMddHHmm", java.util.Locale.getDefault());
        Date date = new Date();
        String strDate = dateFormat.format(date) + "_";
        Log.i("datevalue" , "value : " + strDate);

        return strDate;
    }
}