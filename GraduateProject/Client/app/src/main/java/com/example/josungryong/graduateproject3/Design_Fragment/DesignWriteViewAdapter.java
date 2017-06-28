package com.example.josungryong.graduateproject3.Design_Fragment;

import android.content.Context;
import android.support.v7.widget.RecyclerView;
import android.support.v7.widget.StaggeredGridLayoutManager;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ImageView;
import android.widget.Toast;

import com.example.josungryong.graduateproject3.R;
import com.squareup.picasso.Picasso;

import java.util.ArrayList;
import java.util.List;

import static com.example.josungryong.graduateproject3.Design_Fragment.DesignWrite.adapterCardview;
import static com.example.josungryong.graduateproject3.Design_Fragment.DesignWrite.linearLayoutManager;
import static com.example.josungryong.graduateproject3.Design_Fragment.DesignWrite.mainimage;
import static com.example.josungryong.graduateproject3.Design_Fragment.DesignWrite.recyclerView;
import static java.security.AccessController.getContext;

/**
 * Created by josungryong on 2017-04-12.
 */

public class DesignWriteViewAdapter extends RecyclerView.Adapter<DesignWriteViewAdapter.Holder> {
    private Context context;
    private List<ItemDataDesignWrite> list = new ArrayList<>();

    public DesignWriteViewAdapter(Context context, List<ItemDataDesignWrite> list) {
        this.context = context;
        this.list = list;
    }

    // ViewHolder 생성
    // row layout을 화면에 뿌려주고 holder에 연결
    @Override
    public Holder onCreateViewHolder(ViewGroup parent, int viewType) {
        View view = LayoutInflater.from(parent.getContext()).inflate(R.layout.item_designwirte_cardview, parent, false);
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
        holder.position = position;

        holder.URI = list.get(position).URI;
        //holder.imageView.setImageBitmap(getPic(holder.URI));
        Picasso.with(context).load(holder.URI).fit().into(holder.imageView);

        holder.imageView.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Picasso.with(context).load(holder.URI).into(mainimage);
            }
        });

        holder.imageView.setOnLongClickListener(new View.OnLongClickListener() {
            @Override
            public boolean onLongClick(View v) {
                list.remove(holder.position);
                adapterCardview = new DesignWriteViewAdapter(context, list);
                linearLayoutManager = new StaggeredGridLayoutManager(2,StaggeredGridLayoutManager.HORIZONTAL);
                recyclerView.setLayoutManager(linearLayoutManager);
                recyclerView.setAdapter(adapterCardview);
             return true;
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
        ImageView imageView;
        public String URI;
        public int position;

        public Holder(View view) {
            super(view);
            imageView = (ImageView) view.findViewById(R.id.designwrite_image);
        }
    }

    // URL을 통해 이미지를 서버로 부터 불러온다. //
    /*
    public Bitmap getPic(String imagePath) {
        StrictMode.ThreadPolicy policy = new StrictMode.ThreadPolicy.Builder().permitAll().build();
        StrictMode.setThreadPolicy(policy);

        HttpURLConnection connection = null;
        String imageURL;
        imageURL = "http://113.198.210.237:80/" + imagePath;
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
            Log.e("이미지", "실패");
            e.printStackTrace();
            return null;
        } finally {
            Log.e("이미지", "커밋성공");
            if (connection != null) connection.disconnect();
        }//
    }*/
}