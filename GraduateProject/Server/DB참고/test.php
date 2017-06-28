<?php
$servername = "localhost";
$username = "root";
$password = "";
$dbTable = "testdb";
// Create connection
$link = mysqli_connect($servername, $username, $password, $dbTable);
mysqli_query($link, " SET NAMES UTF8");
if (!$link) {
	printf("Connect failed: %s\n", mysqli_connect_error());
	exit();
}

$_ID= urldecode($_POST['ID']);
$_PWD= urldecode($_POST['PWD']);

$query = mysqli_query($link, "insert into user_interface(ID, PWD) values(\"$_ID\", \"$_PWD\")");
if($query){
	echo "success";
}
else{
	echo "failure";
}
echo date("YmdHis");

?>