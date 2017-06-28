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

$_MARK = "null";
$_MARK = urldecode($_POST['MARK']);

$_JOIN_ID="null";
$_JOIN_ID = urldecode($_POST['JOIN_ID']);//ID 중복체크 스트링

$_JOIN_PW="null";
$_JOIN_PW= urldecode($_POST['PW']);//PW insert

$_U_NAME="null";
$_U_NAME= urldecode($_POST['U_NAME']);//닉네임 중복체크 스트링


$_CATE1="null";
$_CATE1=urldecode($_POST['SEC1']);//depth 1

$_CATE2="null";
$_CATE2=urldecode($_POST['SEC2']);//depth 2

$_PRESENTATION="null";
$_PRESENTATION=urldecode($_POST['PRESENTATION']);

$_RESIDENCE="null";
$_RESIDENCE=urldecode($_POST['RESIDENCE']);

$_URI="null";
$_URI=urldecode($_POST['URI']);

$_TRUE=1;
$_FALSE=0;

switch($_MARK) {
    case "1" :
        $query1 = mysqli_query($link, "select t_member.email from t_member where email=\"$_JOIN_ID\"");
        $row1 = mysqli_fetch_array($query1); // ID 중복체크
        if ($row1 != null)
            echo "$_TRUE";  // 중복
        else
            echo "$_FALSE"; // 중복이 아님
        break;

    case "2":
        $query2 = mysqli_query($link, "select t_member.uname from t_member where uname=\"$_U_NAME\"");
        $row2 = mysqli_fetch_array($query2);
        if ($row2 != null)
            echo "$_TRUE"; //중복
        else
            echo "$_FALSE"; // 중복이 아님
        // 닉네임 중복 체크
        break;

    case "3":
        $query3 = mysqli_query($link, "select t_category.category_code from where category_name=\"$_CATE2\"");
        $row3 = mysqli_fetch_array($query3);
        $query4 = mysqli_query($link, "select seq from t_zip_code where sido=\"$_RESIDENCE\"");
        $row4 = mysqli_fetch_array($query4);
        $NOW_DATE = date("YmdHi");
        if($_URI == NULL){$_URI = "basic.png";}
        if( $_URI == ''){$_URI = "basic.png";}
        if($_PRESENTATION == ''){$_URI = "no comments";}
        if($_PRESENTATION == NULL){$_URI = "no comments";}
        $query5 = mysqli_query($link, " INSERT INTO t_member(email,passwd,uname,image_url,comments,point,sido_seq,register_time,update_time) 
            VALUES(\"$_JOIN_ID\",\"$_JOIN_PW\",\"$_U_NAME\",\"/resources/km_upload/user_profile/$_URI\",\"$_PRESENTATION\",10000,$row4[seq],\"$NOW_DATE\",\"$NOW_DATE\")");
        break;

}

?>