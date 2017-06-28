package com.example.josungryong.graduateproject3.Design_Fragment;

import android.widget.ImageView;

/**
 * Created by josungryong on 2017-04-04.
 */

public class ItemDataDesignInfo {
    public String URI;
    public String SEQ;

    // 화면에 표시될 문자열 초기화
    public ItemDataDesignInfo(String SEQ , String URI) {
        this.URI = URI;
        this.SEQ = SEQ;
    }
}
