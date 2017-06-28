package com.example.josungryong.graduateproject3;

import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.os.StrictMode;
import android.support.v7.widget.RecyclerView;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.TextView;
import android.widget.Toast;

import com.squareup.picasso.Picasso;

import java.io.BufferedInputStream;
import java.io.IOException;
import java.net.HttpURLConnection;
import java.net.URL;
import java.util.ArrayList;
import java.util.List;

import static com.example.josungryong.graduateproject3.Login.preferences;

/**
 * Created by josungryong on 2017-04-07.
 */

public class CommentViewAdapter extends RecyclerView.Adapter<CommentViewAdapter.Holder> {
    private Context context;
    private List<ItemDataComment> list = new ArrayList<>();

    public CommentViewAdapter(Context context, List<ItemDataComment> list) {
        this.context = context;
        this.list = list;
    }

    // ViewHolder 생성
    // row layout을 화면에 뿌려주고 holder에 연결
    @Override
    public Holder onCreateViewHolder(ViewGroup parent, int viewType) {
        View view = LayoutInflater.from(parent.getContext()).inflate(R.layout.item_comment_cardview, parent, false);
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
        //holder.meaningText.setText(list.get(itemposition).meaning);
        holder.URI=list.get(itemposition).URI; // 프로필 사진 uri
        holder.resister.setText(list.get(itemposition).resister); // 댓글 등록자
        holder.content.setText(list.get(itemposition).content); // 댓글 내용
        holder.resisterseq = list.get(itemposition).resisterseq; // 등록자 seq
        holder.commentseq = list.get(itemposition).commentseq; // 댓글 seq
        holder.resisttime.setText(list.get(itemposition).resisttime); // 댓글 등록 시간
        holder.where_seq=list.get(itemposition).where_seq; // 어디서 왔는지, 그에 대한 seq (프로젝트_seq ~~ ,, 디자인_seq~~)
        //holder.imageView.setImageBitmap(getPic(holder.URI)); // 이미지 붙이기

        Picasso.with(context).load("http://58.142.149.131/"+holder.URI).into(holder.imageView);

        // 댓글 작성자 이면 삭제버튼 보이기
        if(preferences.getString("MEMBERSEQ","").equals(holder.resisterseq)) {
            holder.deleteButton.setVisibility(View.VISIBLE);
        }
        holder.deleteButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Log.i("valuecommentview" , "value : " + holder.where_seq + " " + holder.commentseq);
                new HttpTaskCommentDelete().execute(holder.where_seq , holder.commentseq);
            }
        });
        holder.imageView.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                /*
                Intent intent = new Intent(v.getContext(), DesignInfo.class);
                intent.putExtra("DESIGN_WORK_SEQ" , holder.designseq);
                intent.putExtra("RESISTER_SEQ", holder.resisterseq);
                v.getContext().startActivity(intent);
                */
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
        public TextView resister;
        public TextView content;
        public String resisterseq;
        public String commentseq;
        public TextView resisttime;
        ImageView imageView;
        public String URI;
        public Button deleteButton;
        public String where_seq;

        public Holder(View view){
            super(view);
            resister = (TextView) view.findViewById(R.id.comment_resister);
            resisttime = (TextView) view.findViewById(R.id.comment_resisttime);
            content = (TextView) view.findViewById(R.id.comment_content);
            resisttime = (TextView) view.findViewById(R.id.comment_resisttime);
            imageView = (ImageView) view.findViewById(R.id.comment_profileimg);
            deleteButton = (Button) view.findViewById(R.id.comment_delete);
        }
    }
}