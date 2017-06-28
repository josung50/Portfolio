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

$_PROJ_SEQ = "null";
$_PROJ_SEQ = urldecode($_POST['PROJ_SEQ']);



$query = mysqli_query($link,"select t_project_subject.seq, t_project_subject.subject_name
from t_project_subject
where project_seq = $_PROJ_SEQ
order by t_project_subject.seq asc");

//echo "$_CODE tester";
while($row = mysqli_fetch_array($query))
{
    echo "<br>";
    echo "$row[seq]#";
    echo "$row[subject_name]";
}

$_PROJ_SEQ = "null";

?>