<?php
/**
 * Created by PhpStorm.
 * User: choi
 * Date: 2017-05-15
 * Time: 오후 3:00
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
$_MENU = null;
$_MENU = urldecode($_POST["MENU"]);

$_PROJECT_SEQ = "NULL";
$_PROJECT_SEQ = urldecode($_POST["PROJECT_SEQ"]);

$_LOGIN_MEMBER_SEQ = "NULL";
$_LOGIN_MEMBER_SEQ = urldecode($_POST["MEMBER_SEQ"]);

$_HOPE_MEMBER_ID = "NULL";
$_HOPE_MEMBER_ID = urldecode($_POST["ID"]);

$NOW_DATE = date("YmdHi");

$_PROJECT_JOIN_STATUS = "NULL";

#$_HOPE_MEMBER_ID = "jjcec@naver.com";
#$_PROJECT_SEQ = 4;
#$_MENU = "RETIRE";
#$_LOGIN_MEMBER_SEQ = 47;

if($_MENU == "JOIN_US") {
    $find_member_query = mysqli_query($link, "select * from t_member where t_member.email LIKE \"$_HOPE_MEMBER_ID\"");
    $find_member_row = mysqli_fetch_array($find_member_query);
    if ($find_member_row != null) {
        $add_member_to_project_query = mysqli_query($link, "insert into t_project_member(member_seq, project_seq, register_time)
                       values($find_member_row[seq], $_PROJECT_SEQ, \"$NOW_DATE\") ");
        $add_member_row = mysqli_fetch_row($add_member_to_project_query);

        $_PROJECT_JOIN_STATUS = "Y";
    } else {
        $_PROJECT_JOIN_STATUS = "N";
    }
    if (($_PROJECT_JOIN_STATUS == "Y" || $_PROJECT_JOIN_STATUS == "N") && $_HOPE_MEMBER_ID != "NULL") {
        echo "$_PROJECT_JOIN_STATUS";
    }
}
else if($_MENU == "RETIRE"){
    $delete_info_query = mysqli_query($link, "delete from t_project_member where t_project_member.project_seq = $_PROJECT_SEQ and t_project_member.member_seq = $_LOGIN_MEMBER_SEQ");
    $delete_row = mysqli_fetch_row($delete_info_query);
    echo"SUCCESS";
}

?>