package com.example.josungryong.graduateproject3.Designer_Fragment;

import android.content.Intent;
import android.os.Bundle;
import android.support.annotation.Nullable;
import android.support.v4.app.Fragment;
import android.support.v4.app.FragmentManager;
import android.support.v4.app.FragmentTransaction;
import android.support.v7.app.AppCompatActivity;
import android.util.Log;

import com.example.josungryong.graduateproject3.Design_Fragment.DesignFragment;
import com.example.josungryong.graduateproject3.MainActivity;
import com.example.josungryong.graduateproject3.R;

/**
 * Created by josungryong on 2017-05-25.
 */

public class DesignerIn extends AppCompatActivity {

    String DESIGNER_SEQ;

    private Fragment fr = null;
    Bundle args = null; // fragment를 호출 한 곳을 알려주기 위함.

    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_designerin);

        Intent intent = getIntent();
        DESIGNER_SEQ = intent.getStringExtra("DESIGNER_SEQ");

        fr = new DesignFragment();
        args = new Bundle();
        args.putString("WHERE","DesignerIn");
        args.putString("DESIGNER_SEQ" , DESIGNER_SEQ);
        fr.setArguments(args);
        selectFragment(fr);
    }

    // fragment 교체 //
    public void selectFragment(Fragment fr) {
        FragmentManager fm = getSupportFragmentManager();
        FragmentTransaction fragmentTransaction = fm.beginTransaction();
        fragmentTransaction.replace(R.id.fragment_container_designer, fr);
        fragmentTransaction.commit();
    }
}
