package com.example.josungryong.graduateproject3.Design_Fragment;

import android.content.Context;
import android.support.v7.widget.RecyclerView;
import android.support.v7.widget.StaggeredGridLayoutManager;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ImageView;
import android.widget.TextView;
import android.widget.Toast;

import com.example.josungryong.graduateproject3.R;
import com.squareup.picasso.Picasso;

import java.util.ArrayList;
import java.util.List;

import static java.security.AccessController.getContext;

public class TagViewAdapter extends RecyclerView.Adapter<TagViewAdapter.Holder> {
    private Context context;
    private List<ItemDataTag> list = new ArrayList<>();

    public TagViewAdapter(Context context, List<ItemDataTag> list) {
        this.context = context;
        this.list = list;
    }

    // ViewHolder 생성
    // row layout을 화면에 뿌려주고 holder에 연결
    @Override
    public Holder onCreateViewHolder(ViewGroup parent, int viewType) {
        View view = LayoutInflater.from(parent.getContext()).inflate(R.layout.item_designwrite2_tag_cardview, parent, false);
        Holder holder = new Holder(view);
        return holder;
    }

    /*
    * Todo 만들어진 ViewHolder에 data 삽입 ListView의 getView와 동일
    *
    * */
    @Override
    public void onBindViewHolder(final Holder holder, final int position) {
        // 각 위치에 문자열 세팅
        final int itemposition = position;
        holder.text.setText("#"+list.get(itemposition).text);

        holder.delete.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                list.remove(itemposition);
                notifyItemRemoved(itemposition);
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
    public class Holder extends RecyclerView.ViewHolder {
        public TextView text;
        public ImageView delete;

        public Holder(View view) {
            super(view);
            text = (TextView) view.findViewById(R.id.designwrite2_tag_text_cardview);
            delete = (ImageView) view.findViewById(R.id.designwrite2_tag_delete_cardview);
        }
    }
}