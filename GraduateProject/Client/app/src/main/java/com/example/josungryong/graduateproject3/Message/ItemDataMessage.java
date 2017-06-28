package com.example.josungryong.graduateproject3.Message;

import android.widget.ImageView;

/**
 * Created by josungryong on 2017-05-23.
 */

public class ItemDataMessage {
    // <BR> 메세지 보낸 사람이름 / 프로파일uri / 메세지 내용 / 메세지 보낸 사람 SEQ / 메세지 받은 시간
    // 구분은 a!PJP 로 구분
    public String designerseq;
    public String profileimgURI;
    public String content;
    public String designerNickName;
    public String time;
    public ImageView imageView;


    // 화면에 표시될 문자열 초기화
    public ItemDataMessage(String designerNickName , String profileimgURI , String content , String designerseq , String time) {
        this.designerseq = designerseq;
        this.designerNickName = designerNickName;
        this.profileimgURI = profileimgURI;
        this.content = content;
        this.time = time;
    }
}