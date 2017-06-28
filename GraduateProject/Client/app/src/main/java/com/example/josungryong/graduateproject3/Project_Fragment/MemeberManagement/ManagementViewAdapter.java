package com.example.josungryong.graduateproject3.Project_Fragment.MemeberManagement;

import android.content.Context;
import android.content.DialogInterface;
import android.support.v7.app.AlertDialog;
import android.support.v7.widget.RecyclerView;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ImageView;
import android.widget.TextView;

import com.example.josungryong.graduateproject3.R;
import com.ramotion.foldingcell.FoldingCell;
import com.squareup.picasso.Picasso;

import org.w3c.dom.Text;

import java.util.ArrayList;
import java.util.List;

import static com.example.josungryong.graduateproject3.Login.preferences;

/**
 * Created by josungryong on 2017-05-15.
 */

public class ManagementViewAdapter extends RecyclerView.Adapter<ManagementViewAdapter.Holder> {
    private Context context;
    private List<ItemDataManagement> list = new ArrayList<>();

    public ManagementViewAdapter(Context context, List<ItemDataManagement> list) {
        this.context = context;
        this.list = list;
    }

    // ViewHolder 생성
    // row layout을 화면에 뿌려주고 holder에 연결
    @Override
    public Holder onCreateViewHolder(ViewGroup parent, int viewType) {
        View view = LayoutInflater.from(parent.getContext()).inflate(R.layout.item_management_cardview, parent, false);
        Holder holder = new Holder(view);

        return holder;
    }

    /* Todo 만들어진 ViewHolder에 data 삽입 ListView의 getView와 동일 */
    @Override
    public void onBindViewHolder(final Holder holder, int position) {
        // 디자이너 seq , 디자이너 이름 , 디자이너 프로필사진 uri , 분야 , 자기소개 내용 , 올린 게시물 갯수 , 조회수 , 받은 좋아요 수 , URI::SEQ
        // 각 위치에 문자열 세팅

        int itemposition = position;
        holder.designerseq = list.get(itemposition).designerseq;
        holder.nickName.setText(list.get(itemposition).designerNickName);
        Picasso.with(context).load("http://58.142.149.131/"+list.get(itemposition).profileimgURI).fit().into(holder.imageView);
        holder.field.setText(list.get(itemposition).field);
        holder.uploadCount.setText(list.get(itemposition).uploadCount);
        holder.viewCount.setText(list.get(itemposition).viewCount);
        holder.likeCount.setText(list.get(itemposition).likeCount);
        holder.URIset = list.get(itemposition).URIset; // 업로드 디자인 URI 집합
        Log.i("URIset2", "value : " + holder.URIset + " " + list.get(itemposition).URIset);

        /* Folding in (content) */
        Picasso.with(context).load("http://58.142.149.131/"+list.get(itemposition).profileimgURI).fit().into(holder.profileimg_in);
        holder.content_in.setText(list.get(itemposition).content_in);
        holder.field_in.setText((list.get(itemposition).field));

        holder.PROJ_SEQ = list.get(itemposition).PROJ_SEQ;

        /* 탈퇴 버튼 보여주기
        if(holder.designerseq.equals(preferences.getString("MEMBERSEQ",""))) {
            holder.out.setVisibility(View.VISIBLE);
            holder.out.bringToFront();
        }*/

        /*
        holder.out.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
            AlertDialog.Builder alert = new AlertDialog.Builder(context);
            alert.setTitle("정말 탈퇴 하시겠습니까?");
            alert.setPositiveButton("예", new DialogInterface.OnClickListener() {
                @Override
                public void onClick(DialogInterface dialog, int which) {
                    new HttptaskOUT().execute(holder.PROJ_SEQ);
                }
            });
            alert.setNegativeButton("아니오", new DialogInterface.OnClickListener() {
                @Override
                public void onClick(DialogInterface dialog, int which) {
                    dialog.dismiss(); // 닫기
                }
            });
            alert.show();
            }
        });
        */

        /* 펼칠 때 업로드 내용을 받아와 펼친다. (리사이클 뷰로 구현) */
        holder.fc.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                String temp2[];
                String temp[] = split(holder.URIset,"::");
                for(int i =0; i<temp.length; i++){
                    Log.i("tempvalue" , "value :" + temp[i]);
                    if( i >= 4)
                        break;
                    else {
                        temp2 = split(temp[i], "&"); // seq&title&uri
                        switch (i) {
                            case 0:
                                Picasso.with(context).load("http://113.198.210.237:80/"+temp2[2]).fit().into(holder.upload1);
                                break;
                            case 1:
                                Picasso.with(context).load("http://113.198.210.237:80/"+temp2[2]).fit().into(holder.upload2);
                                break;
                            case 2:
                                Picasso.with(context).load("http://113.198.210.237:80/"+temp2[2]).fit().into(holder.upload3);
                                break;
                            case 3:
                                Picasso.with(context).load("http://113.198.210.237:80/"+temp2[2]).fit().into(holder.upload4);
                                break;
                        }
                    }
                }
                holder.fc.toggle(false);
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
        // 순서대로 디자이너 seq , 디자이너 이름 , 디자이너 프로필사진 uri , 분야 , 자기소개 내용 , 올린 게시물 갯수 , 조회수 , 받은 좋아요 수
        public String designerseq;
        public String profileimgURI;
        public TextView nickName;
        public TextView field;
        public TextView uploadCount;
        public TextView viewCount;
        public TextView likeCount;
        public String URIset;
        public FoldingCell fc;
        public TextView out;

        public String PROJ_SEQ;

        /* Folding in (content) */
        public TextView nickName_in;
        public TextView content_in;
        public ImageView profileimg_in;
        public TextView field_in;
        public ImageView upload1;
        public ImageView upload2;
        public ImageView upload3;
        public ImageView upload4;
        public ImageView arrow;

        ImageView imageView;

        public Holder(View view){
            super(view);
            fc = (FoldingCell) view.findViewById(R.id.folding_cell_management);
            nickName = (TextView) view.findViewById(R.id.nickName_management_cardview);
            imageView = (ImageView) view.findViewById(R.id.imageView_management_cardview);
            field = (TextView) view.findViewById(R.id.field_management_cardview);
            uploadCount = (TextView) view.findViewById(R.id.uploadCount_management_cardview);
            viewCount = (TextView) view.findViewById(R.id.viewCount_management_cardview);
            likeCount = (TextView) view.findViewById(R.id.likeCount_management_cardview);
            out = (TextView) view.findViewById(R.id.out_management_cardview);

            /* Folding in (content) */
            nickName_in = (TextView) view.findViewById(R.id.nickName_management_cardview_in);
            field_in = (TextView) view.findViewById(R.id.field_management_cardview_in);
            content_in = (TextView) view.findViewById(R.id.content_management_cardview_in);
            profileimg_in = (ImageView) view.findViewById(R.id.profileimg_management_cardview_in);
            upload1 = (ImageView) view.findViewById(R.id.upload1_management_cardview_in);
            upload2 = (ImageView) view.findViewById(R.id.upload2_management_cardview_in);
            upload3 = (ImageView) view.findViewById(R.id.upload3_management_cardview_in);
            upload4 = (ImageView) view.findViewById(R.id.upload4_management_cardview_in);
            arrow = (ImageView) view.findViewById(R.id.arrow_management_cardview_in);
        }
    }

    // listDB를 what단위로 끊어서 반환
    public String[] split(String temp123 , String what) {
        String[] temp2 = temp123.split(what);
        return temp2;
    }
}

