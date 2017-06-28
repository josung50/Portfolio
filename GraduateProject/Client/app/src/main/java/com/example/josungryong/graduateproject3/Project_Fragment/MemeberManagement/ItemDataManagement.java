package com.example.josungryong.graduateproject3.Project_Fragment.MemeberManagement;

import android.widget.ImageView;

/**
 * Created by josungryong on 2017-05-15.
 */

public class ItemDataManagement {
    // 순서대로 디자이너 seq , 디자이너 이름 , 디자이너 프로필사진 uri , 분야 , 자기소개 내용 , 올린 게시물 갯수 , 조회수 , 받은 좋아요 수 , SEQ&URI::(uriset)
    // 구분은 a!PJP 로 구분
    public String designerseq;
    public String designerNickName;
    public String profileimgURI;
    public String content_in;
    public String field;
    public String uploadCount;
    public String viewCount;
    public String likeCount;
    public String URIset;
    public ImageView imageView;
    public String PROJ_SEQ;


    // 화면에 표시될 문자열 초기화
    public ItemDataManagement(String designerseq , String designerNickName , String profileimgURI , String field , String content_in ,  String uploadCount , String viewCount , String likeCount , String URIset , String PROJ_SEQ) {
        this.designerseq = designerseq;
        this.designerNickName = designerNickName;
        this.profileimgURI = profileimgURI;
        this.content_in = content_in;
        this.field = field;
        this.uploadCount = uploadCount;
        this.viewCount = viewCount;
        this.likeCount = likeCount;
        this.URIset = URIset;
        this.PROJ_SEQ = PROJ_SEQ;
    }
}
