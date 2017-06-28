package com.example.josungryong.graduateproject3.Project_Fragment;

import android.widget.ImageView;

/**
 * Created by josungryong on 2017-03-14.
 */

public class ItemDataProjectInfo {
    public String title; // 디자인 이름
    public String master; // 올린 사람
    public ImageView imageview; // 프로젝트 섬네일
    public String URI; // 프로젝트 섬네일 경로
    public String commentnumber; // 댓글 수
    public String likenumber; // 좋아요 수
    public String projectinfoseq; // 프로젝트 seq
    public String workseq; // 워크 seq(상세 상세를 위한 seq)
    public String memberseq; // 올린 사람 SEQ

    // 화면에 표시될 문자열 초기화
    public ItemDataProjectInfo(String URI, String title, String master, String commentnumber, String likenumber, String projectinfoseq , String workseq , String memberseq) {
        this.URI = URI;
        this.title = title;
        this.master = master;
        this.commentnumber = commentnumber;
        this.likenumber = likenumber;
        this.projectinfoseq = projectinfoseq;
        this.workseq = workseq;
        this.memberseq = memberseq;
    }
}
