package com.example.josungryong.graduateproject3.Search.Design_Search_Fragment;

import android.widget.ImageView;

/**
 * Created by josungryong on 2017-05-18.
 */

public class ItemDataSDesign {
    public String designseq; // 디자인 seq
    public String URI;
    public String likecheck;
    public String designerseq;

    // 화면에 표시될 문자열 초기화
    //<br>181 #제작자 seq#/resources/km_upload/product/201705202041_20170520_132621.jpg # 좋아요 유무
    public ItemDataSDesign(String designseq, String designerseq , String URI , String likecheck) {
        this.designseq = designseq;
        this.URI = URI;
        this.designerseq = designerseq;
        this.likecheck = likecheck;
    }
}
