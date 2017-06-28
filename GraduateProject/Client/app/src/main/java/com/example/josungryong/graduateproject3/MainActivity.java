package com.example.josungryong.graduateproject3;

import android.Manifest;
import android.app.SearchManager;
import android.content.Context;
import android.content.DialogInterface;
import android.content.Intent;
import android.content.SharedPreferences;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.os.Bundle;
import android.os.StrictMode;
import android.provider.MediaStore;
import android.support.v4.app.Fragment;
import android.support.v4.app.FragmentManager;
import android.support.v4.app.FragmentTransaction;
import android.support.v4.view.MenuItemCompat;
import android.support.v7.app.AlertDialog;
import android.support.v7.widget.SearchView;
import android.util.Log;
import android.view.DragEvent;
import android.view.View;
import android.support.design.widget.NavigationView;
import android.support.v4.view.GravityCompat;
import android.support.v4.widget.DrawerLayout;
import android.support.v7.app.ActionBarDrawerToggle;
import android.support.v7.app.AppCompatActivity;
import android.support.v7.widget.Toolbar;
import android.view.Menu;
import android.view.MenuItem;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.Spinner;
import android.widget.TextView;
import android.widget.Toast;

import com.example.josungryong.graduateproject3.Design_Fragment.DesignFragment;
import com.example.josungryong.graduateproject3.Design_Fragment.DesignWrite;
import com.example.josungryong.graduateproject3.Designer_Fragment.DesignerFragment;
import com.example.josungryong.graduateproject3.Main_Fragment.MainFragment;
import com.example.josungryong.graduateproject3.Message.Message_Main;
import com.example.josungryong.graduateproject3.Mypage.Mypage;
import com.example.josungryong.graduateproject3.Project_Fragment.ProjectFragment;
import com.example.josungryong.graduateproject3.Project_Fragment.ProjectWrite;
import com.example.josungryong.graduateproject3.Search.Search_main;
import com.gun0912.tedpermission.PermissionListener;
import com.gun0912.tedpermission.TedPermission;
import com.ramotion.foldingcell.FoldingCell;
import com.squareup.picasso.Picasso;

import java.io.BufferedInputStream;
import java.io.IOException;
import java.net.HttpURLConnection;
import java.net.URL;
import java.util.ArrayList;

import static com.example.josungryong.graduateproject3.Login.preferences;

public class MainActivity extends AppCompatActivity
        implements NavigationView.OnNavigationItemSelectedListener {

    public static int CHECK;
    public static Context MainActivity;

    public static Bitmap Main_profileimg;
    private Button ProjectButton; private Button DesignButton; private Button DesignerButton;

    public static Spinner DesignSpinner; public static Spinner DesignerSpinner;
    public ArrayAdapter<CharSequence> Design_Spinner_Adapter;
    public ArrayAdapter<CharSequence> Designer_Spinner_Adapter;

    ImageView imgurl;
    TextView nickname;
    TextView selfinfo;

    // 로그인 여부(success,failed) # 멤버SEQ # 멤버닉네임 # 프로필URL # 자기소개 # ID # PASSWORD
    //      0                            1           2           3           4      5        6
    // LOGIN # MEMBERSEQ # MEMBERNICK # IMGURL # SELFINFO # ID # PASSWORD

    // fragment //
    private Fragment fr = null;

    // 0:메인 1:디자인 2:프로젝트 3:디자이너
    int positionFR_current = 0;
    int positionFR_after = -999;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        MainActivity = this;
        CHECK = 0;

        Toolbar toolbar = (Toolbar) findViewById(R.id.toolbar);

        /* 권한 설정 */
        PermissionListener permissionlistener = new PermissionListener() {
            @Override
            public void onPermissionGranted() {
                //Toast.makeText(MainActivity.this, "권한 허가", Toast.LENGTH_SHORT).show();
            }

            @Override
            public void onPermissionDenied(ArrayList<String> deniedPermissions) {
                Toast.makeText(MainActivity.this, "권한 거부\n" + deniedPermissions.toString(), Toast.LENGTH_SHORT).show();
            }
        };
        new TedPermission(this)
                .setPermissionListener(permissionlistener)
                .setRationaleMessage("저장장치에 접근하기 위한 권한이 필요합니다.")
                .setDeniedMessage("[설정] > [권한] 에서 권한을 허용할 수 있습니다.")
                .setPermissions(Manifest.permission.WRITE_EXTERNAL_STORAGE)
                .check();


        // 탭 버튼 //
        ProjectButton = (Button) findViewById(R.id.ProjectButton);
        DesignButton = (Button) findViewById(R.id.DesignButton);
        DesignerButton = (Button) findViewById(R.id.DesignerButton);

        DesignSpinner = (Spinner) findViewById(R.id.DesignSpinner);
        DesignSpinner.setPrompt("분야 선택");
        Design_Spinner_Adapter = ArrayAdapter.createFromResource(this,R.array.design_spinner,R.layout.spinner_tab_item);
        Design_Spinner_Adapter.setDropDownViewResource(R.layout.support_simple_spinner_dropdown_item);
        DesignSpinner.setAdapter(Design_Spinner_Adapter);
        DesignSpinner.setVisibility(View.INVISIBLE);

        DesignerSpinner = (Spinner) findViewById(R.id.DesignerSpinner);
        DesignerSpinner.setPrompt("분야 선택");
        Designer_Spinner_Adapter = ArrayAdapter.createFromResource(this,R.array.design_spinner,R.layout.spinner_tab_item);
        Designer_Spinner_Adapter.setDropDownViewResource(R.layout.support_simple_spinner_dropdown_item);
        DesignerSpinner.setAdapter(Designer_Spinner_Adapter);
        DesignerSpinner.setVisibility(View.INVISIBLE);


        DesignButton.setTextSize(15);
        ProjectButton.setTextSize(15);
        DesignerButton.setTextSize(15);

        fr = new MainFragment();
        selectFragment(fr);

        toolbar.setLogo(R.drawable.logo2);
        toolbar.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                ProjectButton.setTextSize(15);
                DesignButton.setVisibility(View.VISIBLE);
                DesignSpinner.setVisibility(View.INVISIBLE);
                DesignerButton.setVisibility(View.VISIBLE);
                DesignerSpinner.setVisibility(View.INVISIBLE);
                fr = new MainFragment();
                selectFragment(fr);
            }
        });
        setSupportActionBar(toolbar); // 액션바 대신 툴바 적용

        DrawerLayout drawer = (DrawerLayout) findViewById(R.id.drawer_layout);
        ActionBarDrawerToggle toggle = new ActionBarDrawerToggle(
                this, drawer, toolbar, R.string.navigation_drawer_open, R.string.navigation_drawer_close);
        drawer.setDrawerListener(toggle);
        toggle.syncState();

        NavigationView navigationView = (NavigationView) findViewById(R.id.nav_view);
        navigationView.setNavigationItemSelectedListener(this);

        Log.i("MainCOOKIE" , "Value : " + preferences.getString("MEMBERSEQ","") + " " + preferences.getString("ID","") + " " + preferences.getString("LOGIN","") + " " + preferences.getString("IMGURL",""));
    }

    @Override
    protected void onStart() {
        super.onStart();
    }

    @Override
    public void onBackPressed() {
        DrawerLayout drawer = (DrawerLayout) findViewById(R.id.drawer_layout);
        if (drawer.isDrawerOpen(GravityCompat.START)) {
            drawer.closeDrawer(GravityCompat.START);
        } else {
            super.onBackPressed();
        }
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.main, menu);

        /* 검색 */
        SearchManager searchManager = (SearchManager) getSystemService(SEARCH_SERVICE);
        // 검색 버튼을 가져온다.
        MenuItem searchButton = menu.findItem(R.id.action_search);
        // 검색버튼을 클릭했을 때 SearchView를 가져온다.
        SearchView searchView = (SearchView) MenuItemCompat.getActionView(searchButton);
        // 검색 힌트를 설정한다.
        searchView.setQueryHint("검색어를 입력하세요");
        // SearchView를 검색 가능한 위젝으로 설정한다.
        searchView.setSearchableInfo(searchManager.getSearchableInfo(getComponentName()));
        searchView.setOnQueryTextListener(new SearchView.OnQueryTextListener() {
            @Override // 완료 버튼 눌렀을 때 쿼리를 넘긴다.
            public boolean onQueryTextSubmit(String query) {
                Intent intent = new Intent(MainActivity.this, Search_main.class);
                intent.setFlags(Intent.FLAG_ACTIVITY_NO_HISTORY);
                intent.putExtra("QUERY", IsTag(query));
                startActivity(intent);
                return false;
            }

            @Override // 텍스트 추천 리스트를 띄워준다.
            public boolean onQueryTextChange(String newText) {
                return false;
            }
        });


        nickname = (TextView) findViewById(R.id.nickname);
        selfinfo = (TextView) findViewById(R.id.selfinfo);
        imgurl = (ImageView) findViewById(R.id.profileimage);

        nickname.setText(preferences.getString("MEMBERNICK",""));
        selfinfo.setText(preferences.getString("SELFINFO",""));
        Picasso.with(this).load("http://58.142.149.131/"+preferences.getString("IMGURL","")).fit().into(imgurl);
        //Main_profileimg = getPic();
        //imgurl.setImageBitmap(Main_profileimg);
        //Log.i("URLINFO" , "Value : " + "http://113.198.210.237:80/" + preferences.getString("IMGURL",""));

        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        // Handle action bar item clicks here. The action bar will
        // automatically handle clicks on the Home/Up button, so long
        // as you specify a parent activity in AndroidManifest.xml.
        int id = item.getItemId();
        //noinspection SimplifiableIfStatement
        switch(id) {
            case R.id.design_write_nav:
                AlertDialog.Builder alert = new AlertDialog.Builder(this);
                alert.setTitle("어디서 디자인을 가져올까?");
                alert.setPositiveButton("카메라", new DialogInterface.OnClickListener() {
                    @Override
                    public void onClick(DialogInterface dialog, int which) {
                        Intent intent = new Intent(getApplicationContext(), DesignWrite.class);
                        intent.putExtra("CAMERAORIMG","1");
                        startActivity(intent);
                    }
                });
                alert.setNeutralButton("취소", new DialogInterface.OnClickListener() {
                    @Override
                    public void onClick(DialogInterface dialog, int which) {
                        dialog.dismiss();
                    }
                });
                alert.setNegativeButton("갤러리", new DialogInterface.OnClickListener() {
                    @Override
                    public void onClick(DialogInterface dialog, int which) {
                        Intent intent = new Intent(getApplicationContext(), DesignWrite.class);
                        intent.putExtra("CAMERAORIMG","2");
                        startActivity(intent);
                    }
                });
                alert.show();
                return true;

            case R.id.project_write_nav:
                new HttpTaskCheckProjectWrite().execute();
                break;
        }
        return super.onOptionsItemSelected(item);
    }

    @SuppressWarnings("StatementWithEmptyBody")
    @Override
    public boolean onNavigationItemSelected(MenuItem item) {

        int id = item.getItemId();
        if (id == R.id.nav_logout) {
            preferences = getSharedPreferences("login_prefs", MODE_PRIVATE);
            SharedPreferences.Editor editor = preferences.edit();
            editor.clear();
            editor.commit();
            Intent intent = new Intent(MainActivity.this, Login.class);
            startActivity(intent);
            finish();
            // Handle the camera action
        } else if (id == R.id.nav_alram) { // 메세지
            Intent intent = new Intent(MainActivity.this, Message_Main.class);
            startActivity(intent);

        } else if (id == R.id.nav_mypage) {
            Intent intent = new Intent(MainActivity.this, Mypage.class);
            startActivity(intent);
        }

        DrawerLayout drawer = (DrawerLayout) findViewById(R.id.drawer_layout);
        drawer.closeDrawer(GravityCompat.START);
        return true;
    }

    /* 디자인 , 프로젝트 , 디자이너 탭에 따른 Fragment 이동 */
    public void TabClick(View v) {
        switch (v.getId()) {
            case R.id.DesignButton:
                ProjectButton.setTextSize(15);
                DesignButton.setVisibility(View.INVISIBLE);
                DesignSpinner.setVisibility(View.VISIBLE);
                DesignerButton.setVisibility(View.VISIBLE);
                DesignerSpinner.setVisibility(View.INVISIBLE);
                positionFR_after = 1;
                fr = new DesignFragment();
                selectFragment(fr);
                positionFR_current = 1;
                break;
            case R.id.ProjectButton:
                ProjectButton.setTextSize(22);
                DesignButton.setVisibility(View.VISIBLE);
                DesignSpinner.setVisibility(View.INVISIBLE);
                DesignerButton.setVisibility(View.VISIBLE);
                DesignerSpinner.setVisibility(View.INVISIBLE);
                positionFR_after = 2;
                fr = new ProjectFragment();
                selectFragment(fr);
                positionFR_current = 2;
                break;
            case R.id.DesignerButton:
                ProjectButton.setTextSize(15);
                DesignButton.setVisibility(View.VISIBLE);
                DesignSpinner.setVisibility(View.INVISIBLE);
                DesignerButton.setVisibility(View.INVISIBLE);
                DesignerSpinner.setVisibility(View.VISIBLE);
                positionFR_after = 3;
                fr = new DesignerFragment();
                selectFragment(fr);
                positionFR_current = 3;
                break;
        }
    }

    // fragment 교체 //
    public void selectFragment(Fragment fr) {
        int currentPosition = 0;

        FragmentManager fm = getSupportFragmentManager();
        FragmentTransaction fragmentTransaction = fm.beginTransaction();

        switch (leftORrightFR(positionFR_current , positionFR_after)){
            case 0: // 메인으로 이동
                break;
            case 1: // 왼쪽으로 이동
                Log.i("positionvalue" , "value : " + positionFR_current + " " + positionFR_after);
                fragmentTransaction.setCustomAnimations(R.anim.anim_slide_in_left, R.anim.anim_slide_out_right , R.anim.anim_slide_out_right , R.anim.anim_slide_in_left);

                break;
            case 2: // 오른쪽으로 이동
                Log.i("positionvalue" , "value : " + positionFR_current + " " + positionFR_after);
                fragmentTransaction.setCustomAnimations(R.anim.anim_slide_in_right, R.anim.anim_slide_out_left , R.anim.anim_slide_out_left , R.anim.anim_slide_in_right);
                break;
            case -1: // 메인에서 이동
                break;
        }
        fragmentTransaction.replace(R.id.fragment_container, fr);
        fragmentTransaction.commit();
    }
    // fragment 교체 애니메이션을 위한 현재 프레그먼트 찾기 //
    public static int leftORrightFR(int current_position , int after_position ) {
        if(current_position > after_position) { // 왼쪽 이동
            return 1;
        }
        else if(current_position < after_position) // 오른쪽 이동
            return 2;
        else if(after_position == 0) {
            return 0; // 메인 이동
        }
        else return -1; // 메인에서 이동
    }

    // URL을 통해 이미지를 서버로 부터 불러온다. //
    public Bitmap getPic(String imagePath) {
        StrictMode.ThreadPolicy policy = new StrictMode.ThreadPolicy.Builder().permitAll().build();
        StrictMode.setThreadPolicy(policy);

        HttpURLConnection connection = null;
        String imageURL;
        imageURL = "http://58.142.149.131/"+imagePath;
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

    public String IsTag(String query) {
        String[] DeleteSpace = query.split(" "); // 단어 하나만을 인식 (띄어쓰기 기준)
        String realQuery = DeleteSpace[0]; // 검색어로 사용할 진짜 쿼리
        /* #이 포함 되면 태그로 인식 */
        if(realQuery.charAt(0) == '#') { //tag 검색인 경우 (# 포함)
            return realQuery;
        }

        else { // tag 검색이 아닌 경우 (# 미포함)
            return realQuery;
        }
    }
}
