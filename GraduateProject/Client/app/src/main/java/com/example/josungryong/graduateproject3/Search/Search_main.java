package com.example.josungryong.graduateproject3.Search;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.support.v4.app.Fragment;
import android.support.v4.app.FragmentManager;
import android.support.v4.app.FragmentTransaction;
import android.support.v7.app.AppCompatActivity;
import android.util.Log;
import android.view.View;
import android.widget.TextView;

import com.example.josungryong.graduateproject3.R;
import com.example.josungryong.graduateproject3.Search.Design_Search_Fragment.SDesignFragment;
import com.example.josungryong.graduateproject3.Search.Designer_Search_Fragment.SDesignerFragment;
import com.example.josungryong.graduateproject3.Search.Project_Search_Fragment.SProjectFragment;

/**
 * Created by josungryong on 2017-05-17.
 */

public class Search_main extends AppCompatActivity{

    public static String query;
    private Intent intent;

    /* 탭 버튼 */
    private TextView design;
    //private TextView project;
    //private TextView designer;
    private TextView result;

    /* 프레그먼트와 이동 애니메이션 */
    private Fragment fr = null;
    // 1:디자인 2:프로젝트 3:디자이너
    int positionFR_current = 0;
    int positionFR_after = -999;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_search_main);
        design = (TextView) findViewById(R.id.search_design_tab);
        //project = (TextView) findViewById(R.id.search_project_tab);
        //designer = (TextView) findViewById(R.id.search_designer_tab);
        result = (TextView) findViewById(R.id.search_result);

        intent = getIntent();
        query = intent.getStringExtra("QUERY");
        result.setText("'" + query + "' 에 대한 검색결과 입니다.");

        fr = new SDesignFragment();
        selectFragment(fr);
    }

    /*
    public void onClick(View v) {
        int id = v.getId();
        switch (id) {
            case R.id.search_design_tab:
                design.setTextSize(22);                designer.setTextSize(15);                project.setTextSize(15);
                positionFR_after = 1;
                fr = new SDesignFragment();
                selectFragment(fr);
                positionFR_current = 1;
                break;
            case R.id.search_project_tab:
                design.setTextSize(15);                designer.setTextSize(15);                project.setTextSize(22);
                positionFR_after = 2;
                fr = new SProjectFragment();
                selectFragment(fr);
                positionFR_current = 2;
                break;
            case R.id.search_designer_tab:
                design.setTextSize(15);                designer.setTextSize(22);                project.setTextSize(15);
                positionFR_after = 3;
                fr = new SDesignerFragment();
                selectFragment(fr);
                positionFR_current = 3;
                break;
        }
    }
    */

    // fragment 교체 //
    public void selectFragment(Fragment fr) {
        int currentPosition = 0;

        FragmentManager fm = getSupportFragmentManager();
        FragmentTransaction fragmentTransaction = fm.beginTransaction();

        switch (leftORrightFR(positionFR_current , positionFR_after)){
            case 0: // 메인으로 이동
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
        fragmentTransaction.replace(R.id.fragment_container_search, fr);
        fragmentTransaction.commit();
    }
    // fragment 교체 애니메이션을 위한 현재 프레그먼트 찾기 //
    public static int leftORrightFR(int current_position , int after_position ) {
        if(current_position > after_position) { // 왼쪽 이동
            return 1;
        }
        else if(current_position < after_position) // 오른쪽 이동
            return 2;
        else if(after_position == 0) {
            return 0; // 메인 이동
        }
        else return -1; // 메인에서 이동
    }
}
