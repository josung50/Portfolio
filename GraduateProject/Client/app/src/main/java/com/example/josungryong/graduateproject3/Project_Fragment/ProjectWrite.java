package com.example.josungryong.graduateproject3.Project_Fragment;

import android.content.Context;
import android.content.Intent;
import android.net.Uri;
import android.os.Bundle;
import android.provider.MediaStore;
import android.support.annotation.Nullable;
import android.support.v7.app.AppCompatActivity;
import android.support.v7.widget.RecyclerView;
import android.support.v7.widget.StaggeredGridLayoutManager;
import android.util.Log;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ImageView;
import android.widget.TextView;
import android.widget.Toast;

import com.example.josungryong.graduateproject3.ImageUtill;
import com.example.josungryong.graduateproject3.R;
import com.squareup.picasso.Picasso;

import java.io.DataOutputStream;
import java.io.File;
import java.io.FileInputStream;
import java.net.HttpURLConnection;
import java.net.MalformedURLException;
import java.net.URL;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Date;

/**
 * Created by josungryong on 2017-05-20.
 */

public class ProjectWrite extends AppCompatActivity {
    /* 멤버 추가를 위한 리사이클 뷰 */
    public static RecyclerView recyclerView_projectwrite;
    public static ProjectWriteViewAdapter adapter_projectwrite;
    public static StaggeredGridLayoutManager linearLayoutManager_projectwrite;
    public static ArrayList<ItemDataProjectWrite> list_projectwrite = new ArrayList<>();
    public static Context ProjectWrite;

    private static final int PICK_FROM_ALBUM = 1;

    private EditText title;
    private EditText memberID;
    private Button addmemberButton;
    private ImageView thumbnail;
    private TextView send;

    private Uri ImageCaptureUri; // 앨범으로 부터 받아온 URI
    public String FilePath; // 이미지 절대경로(총 경로)
    public String FileName; // 절대경로에서 파일명만 스플릿(이미지 이름)

    /* 이미지 통신에 필요한 변수 */
    int serverResponseCode = 0; // 서버 상태 반환 (이미지 통신)

    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_projectwrite);

        ImageCaptureUri = null;
        title = (EditText) findViewById(R.id.title_projectwrite);
        memberID = (EditText) findViewById(R.id.addmembertext_projectwrite);
        thumbnail = (ImageView) findViewById(R.id.thumbnail_projectwrite);
        addmemberButton = (Button) findViewById(R.id.addmemberbutton_projectwrite);
        send = (TextView) findViewById(R.id.send_projectwrite);

        /* 멤버추가 리사이클 뷰 세팅 */
        ProjectWrite = this;
        recyclerView_projectwrite = (RecyclerView) findViewById(R.id.recyclerViewProjectWrite);
        recyclerView_projectwrite.setHasFixedSize(true);
        list_projectwrite.clear();
        adapter_projectwrite = new ProjectWriteViewAdapter(this, list_projectwrite);
        linearLayoutManager_projectwrite = new StaggeredGridLayoutManager(1,StaggeredGridLayoutManager.VERTICAL);
        recyclerView_projectwrite.setLayoutManager(linearLayoutManager_projectwrite);
        recyclerView_projectwrite.setAdapter(adapter_projectwrite);
    }

    public void onClick(View v) {
        int id = v.getId();
        switch (id) {
            case R.id.thumbnail_projectwrite: // 섬네일 추가
                PickPhoto();
                break;

            case R.id.addmemberbutton_projectwrite: // 멤버 추가
                new HttptaskADD_projectwrite().execute(memberID.getText().toString());
                break;

            case R.id.send_projectwrite: // 프로젝트 생성
                if(CheckNullValue() == true) {
                    send();
                    Toast.makeText(this, "프로젝트 생성 완료.", Toast.LENGTH_SHORT).show();
                    finish();
                }
                else {
                    Toast.makeText(this, "타이틀 , 섬네일을 만들어주세요.", Toast.LENGTH_SHORT).show(); }
                break;
        }
    }

    /* send null값을 체크한다. (섬네일, 타이틀 체크)*/
    public Boolean CheckNullValue() {
        if(title.length() <= 1)
            return false;
        if(ImageCaptureUri == null)
            return false;
        return true;
    }

    /* 앨범에서 섬네일을 고른다. */
    public void PickPhoto() {
        Intent intent = new Intent(Intent.ACTION_PICK);
        intent.setType(MediaStore.Images.Media.CONTENT_TYPE);
        startActivityForResult(intent, PICK_FROM_ALBUM);
    }

    @Override
    public void onActivityResult(int requestCode, int resultCode, Intent data) {
        super.onActivityResult(requestCode, resultCode, data);
        if (resultCode != RESULT_OK)
            return;
        switch (requestCode) {
            case PICK_FROM_ALBUM: {
                ImageCaptureUri = data.getData();
                Picasso.with(this).load(ImageCaptureUri).fit().into(thumbnail);
                break;
            }
        }
    }

    /* 생성 */
    private void send() {
        /* 섬네일 전송 */
        FilePath = ImageUtill.getRealPathFromURI(this, ImageCaptureUri);
        FileName = ImageUtill.uploadFileName(FilePath);
        Log.i("URIofProjectWrite_1" , "value : " + FilePath);
        Log.i("URIofProjectWrite_2" , "value : " + FileName);
        String Time_FileName_temp = CurrentTime() + FileName;
        new HttptaskSEND_projectwrite().execute(title.getText().toString(),Time_FileName_temp);
        uploadFile(FilePath , Time_FileName_temp);
    }

    /* 서버로 이미지 파일을 보내는 함수 */
    private int uploadFile(String sourceFileUri , String Time_FileName_temp) {
        String upLoadServerUri = "http://58.142.149.131/grad/imgUpload_proj.php";

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
                            //Toast.makeText(Write.this, "File Upload Complete.",  Toast.LENGTH_SHORT).show();
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
                        //Toast.makeText(Write.this, "MalformedURLException", Toast.LENGTH_SHORT).show();
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
