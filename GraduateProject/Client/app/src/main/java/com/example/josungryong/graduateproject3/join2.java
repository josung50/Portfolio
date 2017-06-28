package com.example.josungryong.graduateproject3;

import android.app.Activity;
import android.app.ProgressDialog;
import android.content.Context;
import android.content.Intent;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.os.AsyncTask;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.view.View;
import android.app.AlertDialog;
import android.content.DialogInterface;
import android.net.Uri;
import android.provider.MediaStore;
import android.util.Log;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ImageView;
import android.widget.Toast;
import com.squareup.picasso.Picasso;
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.net.URL;
import java.net.URLConnection;
import java.net.URLEncoder;

/**
 * Created by hyeeeeeiny on 2017. 3. 30..
 */

public class join2 extends AppCompatActivity {
    public static Activity join2;

    private static final int PICK_FROM_CAMERA = 0;
    private static final int PICK_FROM_ALBUM = 1;

    public static Uri mImageCaptureUri_join;
    private ImageView iv_UserPhoto;
    private int id_view;
    private String absoultePath;

    Button nickname;
    Button next2;

    EditText user_nickname;

    String nick_Result="1";//1
    String nick_mark="2";//2
    String id;//넘어온 아이디 저장할 변수
    String password;//넘어온 비번 저장할 변수

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_join2);
        join2 = this;
        iv_UserPhoto = (ImageView) this.findViewById(R.id.profile);

        nickname= (Button) findViewById(R.id.nickname_confirm);
        next2=(Button) findViewById(R.id.next2);

        user_nickname=(EditText)findViewById(R.id.nick);

        Intent intent = getIntent();
        id = intent.getStringExtra("name");//join1에서 넘어온 아이디 받기(넘어온데이터 저장)
        password=intent.getStringExtra("pw");//join1에서 넘어온 비번 받기
    }

    /**
     * 카메라에서 사진 촬영
     */
    public void doTakePhotoAction() // 카메라 촬영 후 이미지 가져오기
    {
        Intent intent = new Intent(MediaStore.ACTION_IMAGE_CAPTURE);
        startActivityForResult(intent, PICK_FROM_CAMERA);
    }

    /**
     * 앨범에서 이미지 가져오기
     */
    public void doTakeAlbumAction() // 앨범에서 이미지 가져오기
    {
        // 앨범 호출
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
                mImageCaptureUri_join = data.getData();
                Log.i("imgvalue" , "value : " + mImageCaptureUri_join);
                Picasso.with(this).load(mImageCaptureUri_join).fit().into(iv_UserPhoto);
                Log.d("SmartWheel", mImageCaptureUri_join.getPath().toString());
                break;
            }

            case PICK_FROM_CAMERA: {
                mImageCaptureUri_join = data.getData();
                Picasso.with(this).load(data.getData()).fit().into(iv_UserPhoto);
                break;
            }
        }
    }

    public void nickname(View v){
        String u_name= user_nickname.getText().toString();
        nickname_check(u_name,nick_mark);
    }


    public void next2(View v){
        Bitmap profile= BitmapFactory.decodeResource(getResources(),R.id.profile);

        if(user_nickname.length()==0)//닉네임 입력하지 않을 경우
        {
            Toast.makeText(getApplicationContext(),"닉네임을 입력해주세요!.",Toast.LENGTH_SHORT).show();
            return;

        }

        if(nick_Result.equals("0")){
            Intent intent = new Intent(join2.this, join3.class);
            // Intent intent = new Intent(join1.this, join2.class);// 모든 조건이 만족되면 다음 액티비티로 넘어감
            intent.putExtra("name",id); // 아이디(중복체크 다된 아이디)를 다음 액티비티로 넘김.
            intent.putExtra("pw",password);//비번을 다음 액티비티로 넘김
            intent.putExtra("nickname",user_nickname.getText().toString());
            if(mImageCaptureUri_join == null) {
                Toast.makeText(join2, "프로필 이미지를 넣어주세요.", Toast.LENGTH_SHORT).show();
                return;
            }
            Log.i("mImageCaptureUri_join", "value : " + mImageCaptureUri_join.toString());
            intent.putExtra("uri",mImageCaptureUri_join.toString());
            startActivity(intent);
        }
        else if(!nick_Result.equals("0")){
            Toast.makeText(getApplicationContext(),"닉네임 중복체크를 해주세요!",Toast.LENGTH_SHORT).show();

            return;
        }
    }
    public void onClick(View v) {
        id_view = v.getId();
        if(v.getId() == R.id.next2) {
            Intent intent = new Intent(join2.this, join3.class);
            startActivity(intent);
            //  dbmanger.select(user_id,user_name,user_password, user_phone, user_email);
            //  dbmanger.selectPhoto(user_name, mImageCaptureUri, absoultePath);

            //      Intent mainIntent = new Intent(SignUpPhotoActivity.this, LoginActivity.class);
            //      SignUpPhotoActivity.this.startActivity(mainIntent);
            //      SignUpPhotoActivity.this.finish();
            //      Toast.makeText(this, "회원가입이 완료되었습니다.", Toast.LENGTH_SHORT).show();
        }
        else if(v.getId() == R.id.profile_button) {
            DialogInterface.OnClickListener cameraListener = new DialogInterface.OnClickListener() {
                @Override
                public void onClick(DialogInterface dialog, int which) {
                    doTakePhotoAction();
                }
            };
            DialogInterface.OnClickListener albumListener = new DialogInterface.OnClickListener() {
                @Override
                public void onClick(DialogInterface dialog, int which) {
                    doTakeAlbumAction();
                }
            };
            DialogInterface.OnClickListener cancelListener = new DialogInterface.OnClickListener() {
                @Override
                public void onClick(DialogInterface dialog, int which) {
                    dialog.dismiss();
                }
            };

            new AlertDialog.Builder(this)
                    .setTitle("업로드할 이미지 선택")
                    .setPositiveButton("사진촬영", cameraListener)
                    .setNeutralButton("취소", cancelListener)
                    .setNegativeButton("앨범선택", albumListener)
                    .show();
        }
    }

    private void nickname_check(String nickname,String nick_mark){//id보내주는 함수
        class idcheck extends AsyncTask<String, Void, String> {
            ProgressDialog loading;

            @Override
            protected void onPreExecute() {
                super.onPreExecute();
                loading = ProgressDialog.show(join2.this, "Please Wait", null, true, true);
            }

            @Override
            protected void onPostExecute(String s) {
                super.onPostExecute(s);
                loading.dismiss();

                if(nick_Result.equals("0"))
                {
                    s= "사용가능한 닉네임 입니다." ;
                }
                else if(!nick_Result.equals("0"))
                {
                    s= "이미 존재하는 닉네임 입니다" ;
                }
                Toast.makeText(getApplicationContext(),s,Toast.LENGTH_LONG).show();
            }

            @Override
            protected String doInBackground(String... params) {

                try{
                    String U_NAME = (String)params[0];//넘어가는 변수
                    String MARK=(String)params[1];//닉네임 중복체크 마크 :2

                    String link="http://58.142.149.131/grad/Grad_Join.php";
                    String data  = URLEncoder.encode("U_NAME", "UTF-8") + "=" + URLEncoder.encode(U_NAME, "UTF-8");
                    data += "&" + URLEncoder.encode("MARK", "UTF-8") + "=" + URLEncoder.encode(MARK, "UTF-8");

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
                    nick_Result=sb.toString();

                    return nick_Result;
                }
                catch(Exception e){
                    return new String("Exception: " + e.getMessage());
                }
            }
        }

        idcheck task = new idcheck();
        task.execute(nickname,nick_mark);

    }
}