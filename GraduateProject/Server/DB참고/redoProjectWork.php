<?php
//MySQL 연결
$servername = "localhost";
$username = "root";
$password = "";
$dbTable = "opendesign";

$link = mysqli_connect($servername, $username, $password, $dbTable);
mysqli_query($connect, "set names utf8");
$seq = $_POST[SEQ];
//query문 시작
//중복 검사
$query = mysqli_query($connect,"UPDATE t_project_work SET del_flag='N' WHERE seq='{$seq}'");
echo "OK";
?>