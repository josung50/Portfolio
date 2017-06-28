<?php
/**
 * Created by PhpStorm.
 * User: choi
 * Date: 2017-05-22
 * Time: 오후 8:40
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

$NOW_DATE = date("YmdHi");

$_RECEIVER = urldecode($_POST["RECEIVER"]);
$_LOGIN_MEMBER_SEQ = urldecode($_POST["MEMBER_SEQ"]);
$_SENDER_SEQ = urldecode($_POST["SENDER_SEQ"]);
$_MESSAGE = urldecode($_POST["MESSAGE"]);

$_REGISTER_TIME= $NOW_DATE;

$_COMMAND = urldecode($_POST["COMMAND"]);
$_SENT = "N";
if($_COMMAND == "SEND_MESSAGE") {
    $send_msg_query = mysqli_query($link, "insert into t_talk(contents, recieve_seq, send_seq, register_time)
                values(\"$_MESSAGE\", $_RECEIVER, $_LOGIN_MEMBER_SEQ, \"$_REGISTER_TIME\")");
    $send_msg_row = mysqli_fetch_row($send_msg_query);
    $_SENT = "Y";
    echo "$_SENT";
}
else if($_COMMAND == "GET_LIST"){
    $get_list_query = mysqli_query($link, "select tm.uname, tm.image_url, ttlt.seq, ttlt.contents, ttlt.sender_seq, ttlt.register_time from t_member tm,
(select tt.seq, tt.contents, tt.send_seq as sender_seq, tt.register_time from t_talk tt,
(select send_seq, MAX(seq) as lastest_message_seq
from t_talk
where recieve_seq = $_LOGIN_MEMBER_SEQ
group by send_seq) t_lm
where tt.seq = t_lm.lastest_message_seq
order by tt.seq desc) ttlt
where tm.seq = ttlt.sender_seq");
    while($get_list_row = mysqli_fetch_array($get_list_query)){
        echo"<br>";
        echo"$get_list_row[uname]a!PJP";
        echo"$get_list_row[image_url]a!PJP";
        echo"$get_list_row[contents]a!PJP";
        echo"$get_list_row[sender_seq]a!PJP";
        echo"$get_list_row[register_time]";
    }
}
else if($_COMMAND == "LIST_MESSAGE"){
    $list_message_query = mysqli_query($link, "select * from t_talk
        where (send_seq = $_SENDER_SEQ and recieve_seq = $_LOGIN_MEMBER_SEQ) or (send_seq = $_LOGIN_MEMBER_SEQ and recieve_seq = $_SENDER_SEQ) order by seq asc");
    while($list_message_row = mysqli_fetch_array($list_message_query)){
        $_STATUS = "R";
        echo"<br>";
        echo"$list_message_row[contents]a!PJP";
        echo"$list_message_row[register_time]a!PJP";
        if($list_message_row[send_seq] == $_LOGIN_MEMBER_SEQ){
            $_STATUS = "S";
        }
        echo"$_STATUS";
    }
}
?>