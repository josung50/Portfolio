package com.example.josungryong.graduateproject3.Message;

/**
 * Created by josungryong on 2017-05-24.
 */

public class ItemDataMessageIn {
    // <br> / 메세지 내용 / 메세ㅂ지 받거나 보낸 시간 / 보낸 메시지 인지 받은 메세지인지 (R,S)
    String content;
    String time;
    String type;


    // 화면에 표시될 문자열 초기화
    public ItemDataMessageIn(String content , String time , String type) {
        this.content = content;
        this.time = time;
        this.type = type;
    }
}