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

// 아직 보류 중인 php

$DESIGN_WORK_SEQ = NULL;
$DESIGN_WORK_SEQ = urldecode($_POST["DESIGN_WORK_SEQ"]);
$query = mysqli_query($link,"select comm.seq, comm.design_work_seq, comm.member_seq, comm.contents, comm.register_time, mem.uname
from t_design_work_comment comm left outer join t_member mem on comm.member_seq = mem.seq
where comm.design_work_seq = $DESIGN_WORK_SEQ");
while($row = mysqli_fetch_array($query)) {
    echo "<br>";
    echo "$row[seq]#";
    echo "$row[design_work_seq]#";
    echo "$row[member_seq]#";
    echo "$row[uname]#";
    echo "$row[contents]#";
    echo "$row[register_time]";
}
$DESIGN_WORK_SEQ = NULL;
?>