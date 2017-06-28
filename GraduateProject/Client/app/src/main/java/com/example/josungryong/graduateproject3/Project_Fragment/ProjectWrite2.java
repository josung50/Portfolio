package com.example.josungryong.graduateproject3.Project_Fragment;

import android.content.DialogInterface;
import android.content.Intent;
import android.net.Uri;
import android.os.Bundle;
import android.provider.MediaStore;
import android.support.annotation.Nullable;
import android.support.v7.app.AlertDialog;
import android.support.v7.app.AppCompatActivity;
import android.util.Log;
import android.view.View;
import android.widget.EditText;
import android.widget.ImageView;
import android.widget.TextView;
import android.widget.Toast;

import com.example.josungryong.graduateproject3.ImageUtill;
import com.example.josungryong.graduateproject3.R;
import com.squareup.picasso.Picasso;

import org.w3c.dom.Text;

import java.io.DataOutputStream;
import java.io.File;
import java.io.FileInputStream;
import java.net.HttpURLConnection;
import java.net.MalformedURLException;
import java.net.URL;
import java.text.SimpleDateFormat;
import java.util.Date;

/**
 * Created by josungryong on 2017-05-21.
 */

public class ProjectWrite2 extends AppCompatActivity{
    // constant (앨범 || 카메라)
    final int PICTURE_REQUEST_CODE = 100;
    final int CAMERA_REQUEST_CODE = 200;
    /* 이미지 통신에 필요한 변수 */
    int serverResponseCode = 0; // 서버 상태 반환 (이미지 통신)
    public String FilePath; // 이미지 절대경로(총 경로)
    public String FileName; // 절대경로에서 파일명만 스플릿(이미지 이름)

    private String SUBJ_SEQ;

    private EditText title;
    private ImageView image;
    private EditText content;
    private TextView cancel;
    private TextView send;
    private Uri ImageCaptureUri; // 앨범으로 부터 받아온 URI

    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_projectwrite2);
        Intent intent = getIntent();
        SUBJ_SEQ = intent.getStringExtra("SUBJ_SEQ");


        title = (EditText) findViewById(R.id.title_projectwrite2);
        image = (ImageView) findViewById(R.id.image_projectwrite2);
        content = (EditText) findViewById(R.id.content_projectwrite2);
        cancel = (TextView) findViewById(R.id.cancel_projectwrite2);
        send = (TextView) findViewById(R.id.send_projectwrite2);
    }

    public void onClick(View v) {
        int id = v.getId();
        switch (id) {
            case R.id.cancel_projectwrite2: // 취소
                finish();
                break;
            case R.id.image_projectwrite2: // 이미지 등록
                PickImage_alert();
                break;
            case R.id.send_projectwrite2: // 등록
                if( CheckNull() == true){
                    send();
                    Toast.makeText(this, "등록 완료", Toast.LENGTH_SHORT).show();
                    finish();
                }
                break;
        }
    }

    private void PickImage_alert() {
        AlertDialog.Builder alert = new AlertDialog.Builder(this);
        alert.setTitle("어디서 디자인을 가져올까?");
        alert.setPositiveButton("카메라", new DialogInterface.OnClickListener() {
            @Override
            public void onClick(DialogInterface dialog, int which) {
                Pick_Camera();
            }
        });
        alert.setNeutralButton("취소", new DialogInterface.OnClickListener() {
            @Override
            public void onClick(DialogInterface dialog, int which) {
                dialog.dismiss();
            }
        });
        alert.setNegativeButton("갤러리", new DialogInterface.OnClickListener() {
            @Override
            public void onClick(DialogInterface dialog, int which) {
                Pick_Album();
            }
        });
        alert.show();
    }

    private void Pick_Camera() {
        Intent intent2 = new Intent(MediaStore.ACTION_IMAGE_CAPTURE);
        startActivityForResult(intent2, CAMERA_REQUEST_CODE);
    }
    private void Pick_Album() {
        Intent intent = new Intent(Intent.ACTION_PICK);
        intent.setType(MediaStore.Images.Media.CONTENT_TYPE);
        startActivityForResult(intent, PICTURE_REQUEST_CODE);
    }
    @Override
    public void onActivityResult(int requestCode, int resultCode, Intent data) {
        if( resultCode == RESULT_CANCELED) { // 취소
            return; }

        if (requestCode == PICTURE_REQUEST_CODE || requestCode == CAMERA_REQUEST_CODE) {
            //ClipData 또는 Uri를 가져온다
            if( data.getData() == null ) {
                return;
            }
            if (resultCode == RESULT_OK) {
                ImageCaptureUri = data.getData();
                Picasso.with(this).load(ImageCaptureUri).fit().into(image);
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
        new HttptaskSEND_projectwrite2().execute(title.getText().toString() , Time_FileName_temp , SUBJ_SEQ , content.getText().toString());
        uploadFile(FilePath , Time_FileName_temp);
    }

    /* 서버로 이미지 파일을 보내는 함수 */
    private int uploadFile(String sourceFileUri , String Time_FileName_temp) {
        String upLoadServerUri = "http://58.142.149.131/grad/imgUpload_proj_work.php";

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

    public Boolean CheckNull() { // false : null 존재
        if( title.length() <=1 || content.length() <=1) {
            Toast.makeText(this, "타이틀 혹은 상세내용을 입력해주세요.", Toast.LENGTH_SHORT).show();
            return false;
        }
        if( ImageCaptureUri == null ) {
            Toast.makeText(this, "이미지를 등록해 주세요.", Toast.LENGTH_SHORT).show();
            return false;
        }
        if( SUBJ_SEQ == null) {
            Toast.makeText(this, "주제가 없습니다.", Toast.LENGTH_SHORT).show();
            return false;
        }
        return true;
    }
}
