package com.example.josungryong.graduateproject3.Main_Fragment;

import android.util.Log;
import android.widget.ImageView;
import java.util.ArrayList;

/**
 * Created by josungryong on 2017-03-12.
 */
public class WordItemData {
    public String title;
    public String meaning;
    public String resister;
    public String view;
    public ImageView imageview;
    public String URI;

    // 화면에 표시될 문자열 초기화
    public WordItemData(String title, String meaning, String URI, String resister, String view) {
        this.title = title; // 제목
        this.meaning = meaning; // 상세내용
        this.URI = URI; // 섬네일 주소
        this.resister = resister; // 제작자 혹은 등록자
        this.view = view; // 조회수
    }
}
