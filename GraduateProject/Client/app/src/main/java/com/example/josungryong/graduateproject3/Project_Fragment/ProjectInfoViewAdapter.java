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

public class ProjectInfoViewAdapter extends RecyclerView.Adapter<ProjectInfoViewAdapter.Holder> {
    private Context context;
    private List<ItemDataProjectInfo> list = new ArrayList<>();

    public ProjectInfoViewAdapter(Context context, List<ItemDataProjectInfo> list) {
        this.context = context;
        this.list = list;
    }

    // ViewHolder 생성
    // row layout을 화면에 뿌려주고 holder에 연결
    @Override
    public Holder onCreateViewHolder(ViewGroup parent, int viewType) {
        View view = LayoutInflater.from(parent.getContext()).inflate(R.layout.item_projectinfo_cardview, parent, false);
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
        holder.commentnumberText.setText(list.get(itemposition).commentnumber);
        holder.likenumberText.setText(list.get(itemposition).likenumber);
        holder.URI=list.get(itemposition).URI;

        //holder.imageView.setImageBitmap(getPic(holder.URI));
        Picasso.with(context).load("http://58.142.149.131/"+holder.URI).fit().into(holder.imageView);

        holder.projectinfoseq=list.get(itemposition).projectinfoseq;
        holder.workseq=list.get(itemposition).workseq;
        holder.memberseq=list.get(itemposition).memberseq;

        holder.imageView.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                //Toast.makeText(context, "test"+position, Toast.LENGTH_SHORT).show();
                Intent intent = new Intent(v.getContext(), ProjectInfo2.class);
                intent.putExtra("PROJECT_WORK_SEQ" , holder.workseq);
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
        public TextView titleText; // 제목
        public TextView masterText; // 올린 사람
        public TextView commentnumberText; // 댓글 수
        public TextView likenumberText; // 좋아요 수
        public String URI; // 이미지 URL
        public String projectinfoseq; // 프로젝트 seq
        public String workseq; // 워크 seq
        public String memberseq;
        ImageView imageView;

        public Holder(View view){
            super(view);
            titleText = (TextView) view.findViewById(R.id.title_projectinfo_cardview);
            masterText = (TextView) view.findViewById(R.id.masteruser_projectinfo_cardview);
            commentnumberText = (TextView) view.findViewById(R.id.commentnumber_projectinfo_cardview);
            likenumberText = (TextView) view.findViewById(R.id.likenumber_projectinfo_cardview);
            imageView = (ImageView) view.findViewById(R.id.imageView_projectinfo_cardview);
        }
    }

    // URL을 통해 이미지를 서버로 부터 불러온다. //
    public Bitmap getPic(String imagePath) {
        StrictMode.ThreadPolicy policy = new StrictMode.ThreadPolicy.Builder().permitAll().build();
        StrictMode.setThreadPolicy(policy);

        HttpURLConnection connection = null;
        String imageURL;
        imageURL = "http://113.198.210.237:80/"+imagePath;
        Log.e("이미지", imageURL);
        try {
            URL url = new URL(imageURL);
            connection = (HttpURLConnection) url.openConnection();
            connection.setDoInput(true);
            connection.connect();

            BufferedInputStream bis = new BufferedInputStream(connection.getInputStream());
            Bitmap myBitmap = BitmapFactory.decodeStream(bis);

            Log.e("이미지", "성공" + myBitmap);
            return myBitmap;
        } catch (IOException e) {
            Log.e("이미지" , "실패");
            e.printStackTrace();
            return null;
        }finally{
            Log.e("이미지","커밋성공");
            if(connection!=null)connection.disconnect();
        }//
    }
}
