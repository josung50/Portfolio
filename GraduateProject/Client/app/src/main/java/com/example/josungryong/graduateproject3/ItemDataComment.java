package com.example.josungryong.graduateproject3;

import android.widget.ImageView;

/**
 * Created by josungryong on 2017-04-07.
 */

public class ItemDataComment {
    public String resister; // 댓글 올린사람 이름
    public String content; // 댓글 내용
    public ImageView imageview;
    public String resisterseq; // 디자인 올린사람 seq
    public String commentseq; // 댓글 seq
    public String resisttime;
    public String URI;
    public String where_seq; // PROJECT_SEQ=14 .. DESIGN_SEQ=15 등..

    // 화면에 표시될 문자열 초기화
    public ItemDataComment(String commentseq , String resisterseq , String resister , String uri , String content , String resisttime , String where_seq) {
        this.commentseq = commentseq;
        this.resisterseq = resisterseq;
        this.URI = uri;
        this.content = content;
        this.resisttime = resisttime;
        this.resister = resister;
        this.where_seq = where_seq;
    }
}
