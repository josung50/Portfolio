<?php
//DB연결
session_start();


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

//DB 접속
$id = $_POST[loginid];
$pwd = $_POST[loginpwd];

$pwd = hash('sha256', $pwd);

$id = mysqli_real_escape_string($link, $id);
$pwd = mysqli_real_escape_string($link, $pwd);




$query = mysqli_query($link, "select * from t_admin where admin_id='".$id."' and admin_pw='".$pwd."';");

//테이블에서 가져온 값울 배열로 변환
if($arr = mysqli_fetch_array($query,MYSQLI_BOTH))
{
    session_start();
    $_SESSION["id"] = $arr[admin_id];
    //마지막 접속일 갱신
    die("1");
}
else{

die("입력하신 아이디 또는 비밀번호가 올바르지 않습니다.");
die("1");
}
?>

