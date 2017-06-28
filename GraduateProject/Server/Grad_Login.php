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

$_ID = "null";
$_PWD = "null";
$_ID = urldecode($_POST['ID']);
$_PWD = urldecode($_POST['PWD']);
$query = mysqli_query($link,"select t_member.seq, t_member.uname, t_member.image_url, t_member.comments, IFNULL(max(t_member.seq),-1) as loginstatus
from t_member where email = '$_ID' 
and passwd = '$_PWD'");
$row = mysqli_fetch_array($query);
    if ($row[loginstatus] == -1) {
        echo "failed";
    } else {
        echo "success#";
        echo "$row[seq]#";
        echo "$row[uname]#";
        echo "$row[image_url]#";
        echo "$row[comments]#";
        echo "$_ID#";
        echo "$_PWD";
    }

?>