package com.example.josungryong.graduateproject3.Project_Fragment;

import android.content.Context;
import android.content.Intent;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.os.StrictMode;
import android.support.v7.widget.RecyclerView;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ImageView;
import android.widget.TextView;
import android.widget.Toast;

import com.example.josungryong.graduateproject3.R;
import com.squareup.picasso.Picasso;

import org.w3c.dom.Text;

import java.io.BufferedInputStream;
import java.io.IOException;
import java.net.HttpURLConnection;
import java.net.URL;
import java.util.ArrayList;
import java.util.List;

/**
 * Created by josungryong on 2017-03-12.
 */

public class ProjectViewAdapter extends RecyclerView.Adapter<ProjectViewAdapter.Holder> {
    private Context context;
    private List<ItemDataProject> list = new ArrayList<>();

    public ProjectViewAdapter(Context context, List<ItemDataProject> list) {
        this.context = context;
        this.list = list;
    }

    // ViewHolder 생성
    // row layout을 화면에 뿌려주고 holder에 연결
    @Override
    public Holder onCreateViewHolder(ViewGroup parent, int viewType) {
        View view = LayoutInflater.from(parent.getContext()).inflate(R.layout.item_project_cardview, parent, false);
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
        int itemposition = position;
        holder.titleText.setText(list.get(itemposition).title);
        holder.masterText.setText(list.get(itemposition).master);
        holder.materseq = list.get(itemposition).masterseq;
        holder.membernumberText.setText(list.get(itemposition).membernumber);
        holder.filenumberText.setText(list.get(itemposition).filenumber);
        holder.URI=list.get(itemposition).URI;

        Picasso.with(context).load("http://58.142.149.131/"+holder.URI).fit().into(holder.imageView);

        holder.projectseq=list.get(itemposition).projectseq;
        holder.memberSeqGroup=list.get(itemposition).memberSeqGroup;
        Log.i("testValue" , "Value : " + holder.memberSeqGroup);

        holder.imageView.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                //Toast.makeText(context, "test"+position, Toast.LENGTH_SHORT).show();
                Intent intent = new Intent(v.getContext(), ProjectInfo.class);
                intent.putExtra("PROJ_SEQ" , holder.projectseq);
                intent.putExtra("MEMBER_SEQ_GROUP" , holder.memberSeqGroup);
                intent.putExtra("MASTER_SEQ" , holder.materseq);
                Log.i("Member_Seq_Group" , "Value : " + holder.memberSeqGroup);
                v.getContext().startActivity(intent);
            }
        });
        //Log.e("StudyApp", "onBindViewHolder" + itemposition);
    }

    // 몇개의 데이터를 리스트로 뿌려줘야하는지 반드시 정의해줘야한다
    @Override
    public int getItemCount() {
        return list.size(); // RecyclerView의 size return
    }

    // ViewHolder는 하나의 View를 보존하는 역할을 한다
    public class Holder extends RecyclerView.ViewHolder{
        public TextView titleText;
        public TextView masterText;
        public String materseq;
        public TextView membernumberText;
        public TextView filenumberText;
        public String URI;
        public String projectseq;
        public String memberSeqGroup;
        ImageView imageView;

        public Holder(View view){
            super(view);
            titleText = (TextView) view.findViewById(R.id.title_project_cardview);
            masterText = (TextView) view.findViewById(R.id.masteruser_project_cardview);
            membernumberText = (TextView) view.findViewById(R.id.membernumber_project_cardview);
            filenumberText = (TextView) view.findViewById(R.id.filenumber_project_cardview);
            imageView = (ImageView) view.findViewById(R.id.imageView_project_cardview);
        }
    }
}
