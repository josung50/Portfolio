package com.example.josungryong.graduateproject3.Message;

import android.content.Context;
import android.support.v7.widget.RecyclerView;
import android.text.Layout;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ImageView;
import android.widget.TextView;

import com.example.josungryong.graduateproject3.R;
import com.squareup.picasso.Picasso;

import java.util.ArrayList;
import java.util.List;

/**
 * Created by josungryong on 2017-05-24.
 */

public class MessageInViewAdapter extends RecyclerView.Adapter<MessageInViewAdapter.Holder> {
    private Context context;
    private List<ItemDataMessageIn> list = new ArrayList<>();

    public MessageInViewAdapter(Context context, List<ItemDataMessageIn> list) {
        this.context = context;
        this.list = list;
    }

    // ViewHolder 생성
    // row layout을 화면에 뿌려주고 holder에 연결
    @Override
    public Holder onCreateViewHolder(ViewGroup parent, int viewType) {
        View view = LayoutInflater.from(parent.getContext()).inflate(R.layout.item_messagein_cardview, parent, false);
        Holder holder = new Holder(view);
        return holder;
    }

    /* Todo 만들어진 ViewHolder에 data 삽입 ListView의 getView와 동일 */
    @Override
    public void onBindViewHolder(final Holder holder, int position) {
        int itemposition = position;
        holder.type = list.get(itemposition).type;

        // 메세지를 보낸 쪽(왼쪽에 위치)
        if(holder.type.equals("S")) {
            holder.content_right.setText(list.get(itemposition).content);
            holder.content_right.setVisibility(View.VISIBLE);
            holder.time_right.setText(list.get(itemposition).time);
            holder.time_right.setVisibility(View.VISIBLE);
        }
        else {
            holder.content_left.setText(list.get(itemposition).content);
            holder.content_left.setVisibility(View.VISIBLE);
            holder.time_left.setText(list.get(itemposition).time);
            holder.time_left.setVisibility(View.VISIBLE);
        }
    }

    // 몇개의 데이터를 리스트로 뿌려줘야하는지 반드시 정의해줘야한다
    @Override
    public int getItemCount() {
        return list.size(); // RecyclerView의 size return
    }

    // ViewHolder는 하나의 View를 보존하는 역할을 한다
    public class Holder extends RecyclerView.ViewHolder{
        public TextView content_left;
        public TextView time_left;
        public TextView content_right;
        public TextView time_right;
        public String type;

        public Holder(View view){
            super(view);

            content_left = (TextView) view.findViewById(R.id.messagein_left_content);
            time_left = (TextView) view.findViewById(R.id.messagein_left_time);
            content_right = (TextView) view.findViewById(R.id.messagein_right_content);
            time_right = (TextView) view.findViewById(R.id.messagein_right_time);
        }
    }
}
