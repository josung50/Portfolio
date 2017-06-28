<?php
/**
 * Created by PhpStorm.
 * User: choi
 * Date: 2017-05-21
 * Time: 오후 11:12
 */
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

$_NOW_DATE = date("YmdHi");

$_TITLE = urldecode($_POST["TITLE"]);
$_CONTENTS = urldecode($_POST["CONTENTS"]);
$_SUBJ_SEQ = urldecode($_POST['SUBJ_SEQ']);
$_MEMBER_SEQ = urldecode($_POST["MEMBER_SEQ"]);
$_REGISTER_TIME = $_NOW_DATE;
$_LAST_VER = "1.0"; // char
$_DEL_FLAG = "N";
$_THUMB_URI = urldecode($_POST["THUMB_URI"]);

$insert_pwork_query = mysqli_query($link, "insert into t_project_work(title, contents, project_subject_seq, member_seq,
  register_time, last_ver, del_flag, thumb_uri) values(\"$_TITLE\", \"$_CONTENTS\", $_SUBJ_SEQ, $_MEMBER_SEQ, 
  \"$_REGISTER_TIME\", \"$_LAST_VER\", \"$_DEL_FLAG\", \"/resources/km_upload/project_work_file/$_THUMB_URI\")");
$insert_pwork_row = mysqli_fetch_row($insert_pwork_query);

$get_pwork_seq_query = mysqli_query($link, "select t_project_work.seq from t_project_work where member_seq = $_MEMBER_SEQ and register_time = \"$_REGISTER_TIME\"");
$get_pwork_seq_row = mysqli_fetch_array($get_pwork_seq_query);

$insert_pwork_ver_query = mysqli_query($link, "insert into t_project_work_ver(project_work_seq, ver, file_uri, register_time, filename)
          values($get_pwork_seq_row[seq], \"$_LAST_VER\", \"/resources/km_upload/project_work_file/$_THUMB_URI\", \"$_REGISTER_TIME\", \"$_THUMB_URI\")");
$insert_pwork_ver_row = mysqli_fetch_row($insert_pwork_ver_query);
?>