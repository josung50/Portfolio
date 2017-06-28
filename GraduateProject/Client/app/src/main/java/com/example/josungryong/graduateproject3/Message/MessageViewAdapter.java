package com.example.josungryong.graduateproject3.Message;

import android.content.Context;
import android.content.Intent;
import android.support.v7.widget.RecyclerView;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ImageView;
import android.widget.LinearLayout;
import android.widget.TextView;

import com.example.josungryong.graduateproject3.R;
import com.squareup.picasso.Picasso;

import org.w3c.dom.Text;

import java.util.ArrayList;
import java.util.List;

/**
 * Created by josungryong on 2017-05-23.
 */

public class MessageViewAdapter extends RecyclerView.Adapter<MessageViewAdapter.Holder> {
    private Context context;
    private List<ItemDataMessage> list = new ArrayList<>();

    public MessageViewAdapter(Context context, List<ItemDataMessage> list) {
        this.context = context;
        this.list = list;
    }

    // ViewHolder 생성
    // row layout을 화면에 뿌려주고 holder에 연결
    @Override
    public Holder onCreateViewHolder(ViewGroup parent, int viewType) {
        View view = LayoutInflater.from(parent.getContext()).inflate(R.layout.item_message_cardview, parent, false);
        Holder holder = new Holder(view);

        return holder;
    }

    /* Todo 만들어진 ViewHolder에 data 삽입 ListView의 getView와 동일 */
    @Override
    public void onBindViewHolder(final Holder holder, int position) {
        // 디자이너 seq , 디자이너 이름 , 디자이너 프로필사진 uri , 분야 , 자기소개 내용 , 올린 게시물 갯수 , 조회수 , 받은 좋아요 수 , URI::SEQ
        // 각 위치에 문자열 세팅
        final int itemposition = position;
        holder.designerNickName.setText(list.get(itemposition).designerNickName);
        holder.time.setText(list.get(itemposition).time);
        holder.content.setText(list.get(itemposition).content);
        holder.designerseq = list.get(itemposition).designerseq;
        holder.profileimgURI = list.get(itemposition).profileimgURI;
        Picasso.with(context).load("http://58.142.149.131/"+list.get(itemposition).profileimgURI).fit().into(holder.imageView);

        holder.layout.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent intent = new Intent(v.getContext(), MessageIn.class);
                intent.putExtra("WHO" , list.get(itemposition).designerNickName);
                intent.putExtra("WHO_SEQ" , list.get(itemposition).designerseq);
                v.getContext().startActivity(intent);
            }
        });
        Log.e("StudyApp", "onBindViewHolder" + itemposition);
    }

    // 몇개의 데이터를 리스트로 뿌려줘야하는지 반드시 정의해줘야한다
    @Override
    public int getItemCount() {
        return list.size(); // RecyclerView의 size return
    }

    // ViewHolder는 하나의 View를 보존하는 역할을 한다
    public class Holder extends RecyclerView.ViewHolder{
        public String designerseq;
        public TextView designerNickName;
        public String profileimgURI;
        public TextView content;
        public TextView time;
        public ImageView imageView;
        public LinearLayout layout;

        public Holder(View view){
            super(view);
            layout = (LinearLayout) view.findViewById(R.id.message_layout);
            designerNickName = (TextView) view.findViewById(R.id.name_message);
            content = (TextView) view.findViewById(R.id.content_message);
            imageView = (ImageView) view.findViewById(R.id.img_message);
            time = (TextView) view.findViewById(R.id.time_message);
        }
    }
}