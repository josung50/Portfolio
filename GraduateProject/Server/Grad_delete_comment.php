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
$_PROJ_SEQ = null;
$_DESIGN_SEQ = null;

$_PROJ_SEQ = urldecode($_POST["PROJECT_SEQ"]);
$_DESIGN_SEQ = urldecode($_POST["DESIGN_WORK_SEQ"]);

$_COMMENT_SEQ = urldecode($_POST["COMMENT_SEQ"]);

if($_PROJ_SEQ){
    $delete_proj_comm_query = mysqli_query($link, "delete from t_project_work_comment where seq = $_COMMENT_SEQ");
    $delete_proj_comm_row = mysqli_fetch_row($delete_proj_comm_query);
}
else if($_DESIGN_SEQ){
    $delete_design_comm_query = mysqli_query($link, "delete from t_design_work_comment where seq = $_COMMENT_SEQ");
    $delete_design_comm_row = mysqli_fetch_row($delete_design_comm_query);
}
?>