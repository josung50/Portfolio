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
//query문 시작
//중복 검사
$query = mysqli_query($connect,"DELETE FROM t_stat_activities WHERE target_seq='{$seq}' AND target_type='{$type}'");
echo "OK";
?>