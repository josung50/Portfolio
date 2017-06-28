<?php
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

$_EMAIL = urldecode($_POST["email"]);
$_check_user = 'N';
if($_EMAIL) {
    $get_nickname_query = mysqli_query($link, "select * from t_member where email LIKE \"%$_EMAIL%\"");
    $get_nick_row = mysqli_fetch_array($get_nickname_query);
    if($get_nick_row) {
        $_check_user = 'Y';
        echo "$get_nick_row[seq]#$get_nick_row[uname]#";
    }
    echo"$_check_user";

}
?>