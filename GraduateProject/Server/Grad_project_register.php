<?php
/**
 * Created by PhpStorm.
 * User: choi
 * Date: 2017-05-03
 * Time: 오후 2:29
 */

$servername = "localhost";
$username = "root";
$password = "";
$dbTable = "opendesign";
$link = mysqli_connect($servername, $username, $password, $dbTable);
mysqli_query($link, " SET NAMES UTF8");
if(!$link){
	printf("Connect failed: %s\n", mysqli_connect_error());
	exit();
}

/* 등록해야 하는 테이블
 * t_project
 * t_project_member
 */

$NOW_DATE = date("YmdHi");

$_PUBLIC_YN = "Y";
$_TITLE = urldecode($_POST["TITLE"]);
$_STATUS = "P";
$_PROGRESS_STATUS = "P";
$_REGISTER_TIME = $NOW_DATE;
$_UPDATE_TIME = $NOW_DATE;
$_OWNER_SEQ = urldecode($_POST["MEMBER_SEQ"]); // 프로젝트를 생성하려는 유저의 seq
$_DEL_FLAG = "N";
$_MEMBER_LIST = urldecode($_POST["MEMBER_LIST"]); // 프로젝트에 참여시키려는 유저의 seq
$_THUMBNAIL = urldecode($_POST["THUMB"]);

/*$check_new_user_query = mysqli_query($link, "select t_member.uname, t_member.seq, ifnull(mem.up_count, 0) as upload_count
from t_member left outer join
	(select member_seq, count(*) as up_count
	from t_design_work group by member_seq) mem on t_member.seq = mem.member_seq
where mem.member_seq = $_OWNER_SEQ");
$check_new_user_row = mysqli_fetch_array($check_new_user_query);*/
/*if($check_new_user_row[upload_count] == 0){
    echo "CANNOT";
}
else {*/// ^image1.jpeg^image2.jpeg^image3.jpeg^image4.jpeg^image5.jpeg
    $_MEMBER_COUNT = substr_count($_MEMBER_LIST, "^");
    $_MEMBER = explode("^", $_MEMBER_LIST);
    $insert_to_project_query = mysqli_query($link, "insert into t_project(public_yn, project_name, progress_status, file_url, register_time, update_time, owner_seq, file_name, del_flag)
 values(\"$_PUBLIC_YN\", \"$_TITLE\", \"$_PROGRESS_STATUS\", \"/resources/km_upload/project/$_THUMBNAIL\", \"$_REGISTER_TIME\", \"$_UPDATE_TIME\", $_OWNER_SEQ, \"$_THUMBNAIL\", \"$_DEL_FLAG\")");
    $insert_to_project_row = mysqli_fetch_row($insert_to_project_query);

    $get_project_seq_query = mysqli_query($link, "select * from t_project where owner_seq = $_OWNER_SEQ and register_time = \"$_REGISTER_TIME\"");
    $get_project_seq_row = mysqli_fetch_array($get_project_seq_query);
    sleep(1);
    //owner 먼저 입력
    $insert_owner_to_pm_query = mysqli_query($link, "insert into t_project_member(project_seq, member_seq, register_time) values($get_project_seq_row[seq], $_OWNER_SEQ, \"$_REGISTER_TIME\")");
    $insert_owner_row = mysqli_fetch_row($insert_owner_to_pm_query);
    sleep(1);
    //그 외 희망 멤버 입력
    for ($i = 1; $i <= $_MEMBER_COUNT; $i++) {
        $_hope_to_include_member = ((int)$_MEMBER[$i]);
        $insert_to_pm_query = mysqli_query($link, "insert into t_project_member(project_seq, member_seq, register_time) values($get_project_seq_row[seq], $_hope_to_include_member, \"$_REGISTER_TIME\")");
        $insert_to_pm_row = mysqli_fetch_row($insert_to_pm_query);
    }
    sleep(1);

#$reg_member_query = mysqli_query($link, "insert into t_project_member(member_seq, project_seq, register_time) values($get_nick_row[seq], $get_project_seq_query[seq]), $_REGISTER_TIME");
#$reg_member_row = mysqli_fetch_row($reg_member_query);
#}

?>
