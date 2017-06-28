package com.example.josungryong.graduateproject3.Mypage;

import android.os.Bundle;
import android.support.annotation.Nullable;
import android.support.v4.app.Fragment;
import android.support.v4.app.FragmentManager;
import android.support.v4.app.FragmentTransaction;
import android.support.v7.app.AppCompatActivity;
import android.util.Log;
import android.view.View;

import com.example.josungryong.graduateproject3.Design_Fragment.DesignFragment;
import com.example.josungryong.graduateproject3.MainActivity;
import com.example.josungryong.graduateproject3.Project_Fragment.ProjectFragment;
import com.example.josungryong.graduateproject3.R;

/**
 * Created by josungryong on 2017-05-16.
 */

public class Mypage extends AppCompatActivity {

    // fragment //
    private Fragment fr = null;
    Bundle args = null; // fragment를 호출 한 곳을 알려주기 위함.

    // fragment 교체 애니메이션을 위한 변수 1:프로젝트 2:관심디자인 3:최근 내가 등록한 디자인
    int positionFR_current = 0;
    int positionFR_after = -999;

    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_mypage);
    }

    public void Tab(View v) {
        int id = v.getId();
        switch (id) {
            case R.id.mypage_tab_like:
                positionFR_after = 1;
                fr = new DesignFragment();
                args = new Bundle();
                args.putString("WHERE","MYPAGE_LIKE");
                fr.setArguments(args);
                selectFragment(fr);
                positionFR_current = 1;
                break;
            case R.id.mypage_tab_project:
                positionFR_after = 2;
                fr = new ProjectFragment();
                args = new Bundle();
                args.putString("WHERE","MYPAGE_PROJECT");
                fr.setArguments(args);
                selectFragment(fr);
                positionFR_current = 2;
                break;
            case R.id.mypage_tab_upload:
                positionFR_after = 3;
                fr = new DesignFragment();
                args = new Bundle();
                args.putString("WHERE","MYPAGE_UPLOAD");
                fr.setArguments(args);
                selectFragment(fr);
                positionFR_current = 3;
                break;
        }
    }

    // fragment 교체 //
    public void selectFragment(Fragment fr) {

        FragmentManager fm = getSupportFragmentManager();
        FragmentTransaction fragmentTransaction = fm.beginTransaction();

        switch (MainActivity.leftORrightFR(positionFR_current , positionFR_after)){
            case 0: //
                break;
            case 1: // 왼쪽으로 이동
                Log.i("positionvalue" , "value : " + positionFR_current + " " + positionFR_after);
                fragmentTransaction.setCustomAnimations(R.anim.anim_slide_in_left, R.anim.anim_slide_out_right , R.anim.anim_slide_out_right , R.anim.anim_slide_in_left);

                break;
            case 2: // 오른쪽으로 이동
                Log.i("positionvalue" , "value : " + positionFR_current + " " + positionFR_after);
                fragmentTransaction.setCustomAnimations(R.anim.anim_slide_in_right, R.anim.anim_slide_out_left , R.anim.anim_slide_out_left , R.anim.anim_slide_in_right);
                break;
            case -1: // 메인에서 이동
                break;
        }
        fragmentTransaction.replace(R.id.fragment_container_mypage, fr);
        fragmentTransaction.commit();
    }
}
