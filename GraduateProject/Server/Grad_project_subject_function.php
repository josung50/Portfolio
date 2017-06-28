<?php

$servername = "localhost";
$username = "root";
$password = "";
$dbTable = "opendesign";

$link = mysqli_connect($servername, $username, $password, $dbTable);
mysqli_query($link, " SET NAMES UTF8");
if (!$link) {
    printf("Connect failed: %s\n", mysqli_connect_error());
    exit();
}
$_EXE_COMMAND = "NULL";
$_EXE_COMMAND = urldecode($_POST['EXE_COMMAND']);

$_PROJECT_SEQ = "NULL";
$_PROJECT_SEQ = urldecode($_POST['PROJECT_SEQ']);
$_PROJECT_SUBJ_SEQ = "NULL";
$_PROJECT_SUBJ_SEQ = urldecode($_POST['PROJECT_SUBJ_SEQ']);

$_TITLE = "NULL";
$_TITLE = urldecode($_POST['TITLE']);
$_REGI_MEMBER_SEQ = "NULL";
$_REGI_MEMBER_SEQ = urldecode($_POST['REGI_MEMBER_SEQ']);
$_NOW_DATE = date("YmdHis");

#insert subject -> 맨 마지막 주제의 뒤에 추가하며, 추가 시 게시물이 없습니다. 라고 보여줄 수 있도록 할 것.
#string size -> 한글자 3바이트
if($_EXE_COMMAND == "INSERT"){
    #$query = mysqli_query($link, "insert into t_project_work_comment(member_seq, contents, project_work_seq, register_time)
     #                   values($REGI_MEMBER_SEQ, \"$REGI_PCOMMENT\", $REGI_PROJECT_WORK_SEQ, \"$NOW_DATE\")");
    $insert_query = mysqli_query($link, "insert into t_project_subject(project_seq, subject_name, member_seq, register_time)
                     values($_PROJECT_SEQ, \"$_TITLE\", $_REGI_MEMBER_SEQ, \"$_NOW_DATE\")");
    $row = mysqli_fetch_row($insert_query);
}
#delete subject -> 삭제하려는 주제 내부에 게시물이 존재할 경우 삭제불가
else if($_EXE_COMMAND == "DELETE") {
    $count_work_query = mysqli_query($link, "select count(*) as subj_work_count
    from t_project_work
    where project_subject_seq = $_PROJECT_SUBJ_SEQ
    and project_subject_seq IS NOT NULL");
    $delete_judge_row = mysqli_fetch_array($count_work_query);
    if ($delete_judge_row[subj_work_count] >= 1) {
        echo "FALSE";
    }
    else{
        $delete_query = mysqli_query($link, "delete from t_project_subject where seq = $_PROJECT_SUBJ_SEQ");
        $delete_row = mysqli_fetch_row($delete_query);
        echo "TRUE";
    }
}
#correct subject -> 수정할 주제를 선택하여 할 수 있도록
else if($_EXE_COMMAND == "CORRECT"){
    $correct_query = mysqli_query($link, "update t_project_subject set subject_name = \"$_TITLE\" where seq = $_PROJECT_SUBJ_SEQ");
    $correct_row = mysqli_fetch_row($correct_query);
}
?>