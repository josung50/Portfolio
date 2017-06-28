<?php
//MySQL 연결
$servername = "localhost";
$username = "root";
$password = "";
$dbTable = "opendesign";

$link = mysqli_connect($servername, $username, $password, $dbTable);
mysqli_query($connect, "set names utf8");
$seq = $_POST[SEQ];
$type = $_POST[TYPE];
date_default_timezone_set("Asia/Seoul");
$yearmonth = date("Ym",time());
$yearmonth = substr($yearmonth,2,5);
$dateTime = date("Ymd", time());

//query문 시작
$query = mysqli_query($connect,"INSERT INTO t_stat_activities (stat_month, target_seq, target_type, update_time) VALUES ('{$yearmonth}','{$seq}','{$type}','{$dateTime}')");
//echo $yearmonth;
echo "OK";
?>