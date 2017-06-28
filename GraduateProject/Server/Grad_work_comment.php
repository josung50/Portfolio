<?php
$servername = "localhost";
$username = "root";
$password = "";
$dbTable = "opendesign";
// Create connection
$link = mysqli_connect($servername, $username, $password, $dbTable);
mysqli_query($link, " SET NAMES UTF8");
if (!$link) {
    printf("Connect failed: %s\n", mysqli_connect_error());
    exit();
}
//프로젝트 탭 댓글 목록 요청 시 필요한 변수
$PROJECT_WORK_SEQ = NULL;
$PROJECT_WORK_SEQ = urldecode($_POST["PROJECT_WORK_SEQ"]);
//프로젝트 탭 댓글 등록 시 필요한 변수
$REGI_MEMBER_SEQ = NULL;
$REGI_MEMBER_SEQ = urldecode($_POST["REGI_MEMBER_SEQ"]);
$REGI_PROJECT_WORK_SEQ = NULL;
$REGI_PROJECT_WORK_SEQ = urldecode($_POST["REGI_PROJECT_WORK_SEQ"]);
$REGI_PCOMMENT = NULL;
$REGI_PCOMMENT = urldecode($_POST["REGI_PCOMMENT"]);
//디자인 탭 댓글 목록 요청 시 필요한 변수
$DESIGN_WORK_SEQ = NULL;
$DESIGN_WORK_SEQ = urldecode($_POST["DESIGN_WORK_SEQ"]);
//디자인 탭 댓글 등록 시 필요한 변수
$REGI_D_MEMBER_SEQ = NULL;
$REGI_D_MEMBER_SEQ = urldecode($_POST["REGI_D_MEMBER_SEQ"]);
$REGI_DESIGN_WORK_SEQ = NULL;
$REGI_DESIGN_WORK_SEQ = urldecode($_POST["REGI_DESIGN_WORK_SEQ"]);
$REGI_DCOMMENT = NULL;
$REGI_DCOMMENT = urldecode($_POST["REGI_DCOMMENT"]);

//프로젝트 탭 댓글 목록 요청
if($PROJECT_WORK_SEQ) {
    $query = mysqli_query($link, "select a.member_seq, a.contents, a.seq, a.register_time, b.uname, b.image_url
  from t_project_work_comment a, t_member b
  where b.seq = a.member_seq
  and a.project_work_seq = $PROJECT_WORK_SEQ
  ");
    while($row = mysqli_fetch_array($query)) {
        echo "<br>";
        echo "$row[seq]#";
        echo "$row[member_seq]#";
        echo "$row[uname]#";
        echo "$row[image_url]#";
        echo "$row[contents]#";
        echo "$row[register_time]";
    }
    $PROJECT_WORK_SEQ = NULL;
}
//프로젝트 탭 댓글 등록
else if($REGI_PCOMMENT){
    $NOW_DATE = date("YmdHis");
    //$REGI_PCOMMENT = str_replace("ReAdLiNe","ReAdLiNe",$REGI_PCOMMENT);
    $query = mysqli_query($link, "insert into t_project_work_comment(member_seq, contents, project_work_seq, register_time)
                        values($REGI_MEMBER_SEQ, \"$REGI_PCOMMENT\", $REGI_PROJECT_WORK_SEQ, \"$NOW_DATE\")");
}
//디자인 탭 댓글 목록 요청
else if($DESIGN_WORK_SEQ) {
    $query = mysqli_query($link, "select comm.seq, comm.design_work_seq, comm.member_seq, comm.contents, comm.register_time, mem.uname, mem.image_url
from t_design_work_comment comm left outer join t_member mem on comm.member_seq = mem.seq
where comm.design_work_seq = $DESIGN_WORK_SEQ");
    while ($row = mysqli_fetch_array($query)) {
        echo "<br>";
        echo "$row[seq]#";
        echo "$row[member_seq]#";
        echo "$row[uname]#";
        echo "$row[image_url]#";
        echo "$row[contents]#";
        echo "$row[register_time]";
    }
}
//디자인 탭 댓글 등록
else if($REGI_DCOMMENT){
    $NOW_DATE = date("YmdHis");
    $query = mysqli_query($link, "insert into t_design_work_comment(member_seq, contents, design_work_seq, register_time)
                        values($REGI_D_MEMBER_SEQ, \"$REGI_DCOMMENT\", $REGI_DESIGN_WORK_SEQ, \"$NOW_DATE\")");
}
?>
