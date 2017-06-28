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

$_seq = "001";

$query_exec = mysqli_query($link, "select * from t_category where category_code = $_seq");
while($row = mysqli_fetch_array($query_exec))
{
    echo $_seq;
    echo "<br>";
    echo "$row[category_code]#";
    echo "$row[depth]#";
    echo "$row[category_name]";
}



/**
 * Created by PhpStorm.
 * User: choi
 * Date: 2017-03-20
 * Time: 오후 4:48
 */
?>