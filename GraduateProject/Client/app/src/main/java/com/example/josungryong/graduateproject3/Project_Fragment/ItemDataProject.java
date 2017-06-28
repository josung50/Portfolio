package com.example.josungryong.graduateproject3.Project_Fragment;

import android.widget.ImageView;

/**
 * Created by josungryong on 2017-03-14.
 */

public class ItemDataProject {
    public String title; // 프로젝트 이름
    public String master; // 프로젝트 생성자
    public String masterseq; // 프로젝트 생성자 seq
    public String membernumber; // 멤버 수
    public String filenumber; // 파일 수
    public ImageView imageview; // 프로젝트 섬네일
    public String URI; // 프로젝트 섬네일 경로
    public String projectseq;
    public String memberSeqGroup; // 멤버 전원의 seq를 담는 스트링

    // 화면에 표시될 문자열 초기화
    // 프로젝트 이름 / 프로젝트 생성자 / 프로젝트 생성자 seq / 썸네일경로 / 멤버수 / 파일수 / 프로젝트 고유 SEQ / 그룹 멤버 전원 SEQ<br>
    public ItemDataProject(String title, String master, String masterseq, String URI, String membernumber, String filenumber, String projectseq , String memberSeqGroup) {
        this.title = title;
        this.master = master;
        this.masterseq = masterseq;
        this.URI = URI;
        this.membernumber = membernumber;
        this.filenumber = filenumber;
        this.projectseq = projectseq;
        this.memberSeqGroup = memberSeqGroup;
    }
}
