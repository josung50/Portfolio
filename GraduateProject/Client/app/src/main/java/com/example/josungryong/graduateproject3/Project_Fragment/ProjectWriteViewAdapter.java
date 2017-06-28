package com.example.josungryong.graduateproject3.Project_Fragment;

import android.content.Context;
import android.content.Intent;
import android.support.v7.widget.RecyclerView;
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
 * Created by josungryong on 2017-05-20.
 */

public class ProjectWriteViewAdapter extends RecyclerView.Adapter<ProjectWriteViewAdapter.Holder> {
    private Context context;
    private List<ItemDataProjectWrite> list = new ArrayList<>();

    public ProjectWriteViewAdapter(Context context, List<ItemDataProjectWrite> list) {
        this.context = context;
        this.list = list;
    }

    // ViewHolder 생성
    // row layout을 화면에 뿌려주고 holder에 연결
    @Override
    public Holder onCreateViewHolder(ViewGroup parent, int viewType) {
        View view = LayoutInflater.from(parent.getContext()).inflate(R.layout.item_projectwrite_cardview, parent, false);
        Holder holder = new Holder(view);
        return holder;
    }

    /*
    * Todo 만들어진 ViewHolder에 data 삽입 ListView의 getView와 동일
    *
    * */
    @Override
    public void onBindViewHolder(final Holder holder, int position) {
        // 각 위치에 문자열 세팅
        int itemposition = position;
        holder.position = position;
        holder.designer_seq = list.get(itemposition).designer_seq;
        holder.designer_name.setText(list.get(itemposition).designer_name);

        /* 제거 */
        holder.designer_name.setOnLongClickListener(new View.OnLongClickListener() {
            @Override
            public boolean onLongClick(View v) {
                list.remove(holder.position);
                return false;
            }
        });
    }

    // 몇개의 데이터를 리스트로 뿌려줘야하는지 반드시 정의해줘야한다
    @Override
    public int getItemCount() {
        return list.size(); // RecyclerView의 size return
    }

    // ViewHolder는 하나의 View를 보존하는 역할을 한다
    public class Holder extends RecyclerView.ViewHolder{
        public String designer_seq;
        public TextView designer_name;
        public int position;

        public Holder(View view){
            super(view);
            designer_name = (TextView) view.findViewById(R.id.projectwrite_name_cardview);
        }
    }
}
