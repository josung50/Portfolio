package com.example.josungryong.graduateproject3.Design_Fragment;

import android.Manifest;
import android.app.Activity;
import android.content.ClipData;
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
import android.widget.ImageView;
import android.widget.Toast;

import com.example.josungryong.graduateproject3.R;
import com.squareup.picasso.Picasso;

import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Calendar;
import java.util.Date;

/**
 * Created by josungryong on 2017-03-22.
 */

public class DesignWrite extends Activity {

    public static Activity designwrite;
    public static RecyclerView recyclerView;
    public static DesignWriteViewAdapter adapterCardview;
    public static StaggeredGridLayoutManager linearLayoutManager;
    public static ArrayList<ItemDataDesignWrite> list = new ArrayList<>(); // 리사이클 ( 카드 뷰 ) 를 위한 list 여기서는 앨범의 uri를 받아온다.
    public static ArrayList<String> Time_FileName = new ArrayList<>(); // 시간 + 파일 이미지

    public static ImageView mainimage; // 선택된 사진을 보여주는 큰 이미지 뷰
    public static ClipData clipData; // 여러장 선택시 uri값을 가지고 있는 변수
    public static Uri uri; // 한장 선택시 uri값을 가지고 있는 변수

    // constant (앨범 불러오는 코드)
    final int PICTURE_REQUEST_CODE = 100;
    final int CAMERA_REQUEST_CODE = 200;

    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_designwrite);
        designwrite = this;
        /* 퍼미션 체크
        PermissionListener permissionlistener = new PermissionListener() {
            @Override
            public void onPermissionGranted() {
                Toast.makeText(DesignWrite.this, "권한 허가", Toast.LENGTH_SHORT).show();
            }

            @Override
            public void onPermissionDenied(ArrayList<String> deniedPermissions) {
                Toast.makeText(DesignWrite.this, "권한 거부\n" + deniedPermissions.toString(), Toast.LENGTH_SHORT).show();
            }
        };
        new TedPermission(this)
                .setPermissionListener(permissionlistener)
                .setRationaleMessage("저장장치에 접근하기 위한 권한이 필요합니다.")
                .setDeniedMessage("[설정] > [권한] 에서 권한을 허용할 수 있습니다.")
                .setPermissions(Manifest.permission.WRITE_EXTERNAL_STORAGE)
                .check();
                */

        mainimage = (ImageView) findViewById(R.id.designwrite_selectBigimage);

        Toast.makeText(this, "포토 혹은 사진의 경우 여러 사진을 등록합니다.", Toast.LENGTH_SHORT).show();

        Intent intent3 = getIntent();

        if(intent3.getStringExtra("CAMERAORIMG").equals("1")) {
            /* 카메라 호출 */
            Intent intent2 = new Intent(MediaStore.ACTION_IMAGE_CAPTURE);
            startActivityForResult(intent2, CAMERA_REQUEST_CODE);
        }
        else if(intent3.getStringExtra("CAMERAORIMG").equals("2")) {
            /* 앨범 호출 */
            Intent intent = new Intent(Intent.ACTION_PICK, MediaStore.Audio.Media.EXTERNAL_CONTENT_URI);
            intent.putExtra(Intent.EXTRA_ALLOW_MULTIPLE, true);
            intent.setType("image/*");
            startActivityForResult(Intent.createChooser(intent, "Select Picture"), PICTURE_REQUEST_CODE);
        }

        // 이미지 출력
        recyclerView = (RecyclerView) findViewById(R.id.recyclerViewDesignWrite);
        recyclerView.setHasFixedSize(true);
        adapterCardview = new DesignWriteViewAdapter(this,list);
        linearLayoutManager = new StaggeredGridLayoutManager(2,StaggeredGridLayoutManager.HORIZONTAL);
        recyclerView.setLayoutManager(linearLayoutManager);
        recyclerView.setAdapter(adapterCardview);
    }

    @Override
    protected void onDestroy() {
        list.clear(); // 초기화
        super.onDestroy();
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
            uri = data.getData();
            clipData = data.getClipData();
            if (resultCode == RESULT_OK) {
                //이미지 URI 를 이용하여 이미지뷰에 순서대로 세팅한다.
                if (clipData != null) {
                    for (int i = 0; i < clipData.getItemCount(); i++) {
                        list.add(new ItemDataDesignWrite(clipData.getItemAt(i).getUri().toString()));
                    }
                }
                adapterCardview = new DesignWriteViewAdapter(getApplicationContext(), list);
                linearLayoutManager = new StaggeredGridLayoutManager(2,StaggeredGridLayoutManager.HORIZONTAL);
                recyclerView.setLayoutManager(linearLayoutManager);
                recyclerView.setAdapter(adapterCardview);
            }

            if(clipData != null) {
                Picasso.with(this).load(list.get(0).URI).fit().into(mainimage); // 기본 mainimage view 셋팅
            }
            else {
                Picasso.with(this).load(uri.toString()).fit().into(mainimage); // 기본 mainimage view 셋팅
            }

            Log.i("listsize","value:" + list.size());
            Toast.makeText(this,"사진을 길게 누르시면 삭제됩니다.",Toast.LENGTH_SHORT).show();
        }
    }

    public void onClick(View v) {
        switch (v.getId()) {
            case R.id.designwrite_next:
                Intent intent2 = new Intent(DesignWrite.this, DesignWrite2.class);

                if(clipData != null) { // clipData는 갤러리부터 URI를 여러장 혹은 한 장 선택시..
                    //intent2.putExtra("multi", list.size());
                    //Log.i("listsize2","value:" + list.size());
                }
                else {
                    Log.i("urivalue","value:" +uri.toString());
                    intent2.putExtra("sole", uri.toString());
                }
                startActivity(intent2);
                break;

            case R.id.designwrite_close:
                finish();
                break;
        }
    }
}