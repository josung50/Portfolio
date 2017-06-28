package com.example.josungryong.graduateproject3.Design_Fragment;

import android.widget.ImageView;

/**
 * Created by josungryong on 2017-03-14.
 */

public class ItemDataDesign {
    public String title; // 제목
    public String resister; // 디자인 올린사람 이름
    public String view; // 조회수
    public ImageView imageview;
    public String designseq; // 디자인 seq
    public String resisterseq; // 디자인 올린사람 seq
    public String URI;
    public String likecheck;

    // 화면에 표시될 문자열 초기화
    public ItemDataDesign(String designseq, String resisterseq, String title, String URI, String resister, String view, String likecheck) {
        this.title = title;
        this.URI = URI;
        this.resister = resister;
        this.view = view;
        this.designseq = designseq;
        this.resisterseq = resisterseq;
        this.likecheck = likecheck;
    }
}
