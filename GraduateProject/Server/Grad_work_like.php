<?php
/**
 * Created by PhpStorm.
 * User: choi
 * Date: 2017-05-14
 * Time: 오후 5:34
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

$_DESIGN_WORK_SEQ = "NULL";
$_PROJECT_WORK_SEQ = "NULL";
$_MEMBER_SEQ = "NULL";
$_LIKE_STATUS = "NULL";

$_DESIGN_WORK_SEQ = urldecode($_POST["DESIGN_WORK_SEQ"]);
$_PROJECT_WORK_SEQ = urldecode($_POST["PROJECT_WORK_SEQ"]);
$_MEMBER_SEQ = urldecode($_POST["MEMBER_SEQ"]);
$_LIKE_STATUS = urldecode($_POST["LIKE_STATUS"]);
//현재시간
$NOW_DATE = date("YmdHi");
echo"$_DESIGN_WORK_SEQ#";
echo"$_MEMBER_SEQ#";
echo"$_LIKE_STATUS#";

if($_DESIGN_WORK_SEQ != "NULL"){
    if($_LIKE_STATUS == "\(CHECKED\)"){
        echo"싫어졌어요 ㅡㅡ";
        $cancel_like_query = mysqli_query($link, "delete from t_design_work_like
            where t_design_work_like.design_work_seq = $_DESIGN_WORK_SEQ and t_design_work_like.member_seq = $_MEMBER_SEQ ");
        $cancel_like_row = mysqli_fetch_row($cancel_like_query);
    }
    else if($_LIKE_STATUS == "\(UNCHECKED\)"){
        echo"좋아요!";
        $like_this_query = mysqli_query($link, "insert into t_design_work_like(design_work_seq, member_seq, register_time) values($_DESIGN_WORK_SEQ, $_MEMBER_SEQ, \"$NOW_DATE\")");
        $like_this_row = mysqli_fetch_row($like_this_query);
    }
}
?>