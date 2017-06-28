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
$_LOGIN_MEMBER_SEQ = "NULL";
$_LOGIN_MEMBER_SEQ = urldecode($_POST['MEMBER_SEQ']);
$_LIKE_CHECK = "UNCHECKED";

$item_count = 0;
    $query = mysqli_query($link,"select distinct t_design_work.seq, t_design_work.contents,t_design_work.view_cnt,t_design_work.title,t_design_work.thumb_uri,t_design_work.register_time,t_member.uname
 from t_design_work,t_member
 where t_design_work.member_seq=t_member.seq and t_design_work.del_flag='N' ORDER BY register_time DESC;");
    while($row = mysqli_fetch_array($query)) {
        $_LIKE_CHECK = "UNCHECKED";
        echo "<br>";
        echo "$row[title]#";
        echo "$row[view_cnt]#";
        echo "$row[thumb_uri]#";
        echo "$row[contents]#";
        echo "$row[uname]#";
        $like_query = mysqli_query($link, "select * from t_design_work_like where t_design_work_like.design_work_seq = $row[seq]");
        while($like_judge_row = mysqli_fetch_array($like_query)){
            if($like_judge_row[member_seq] == $_LOGIN_MEMBER_SEQ){
                $_LIKE_CHECK = "CHECKED";
            }
        }
        echo "\($_LIKE_CHECK\)";
        $item_count++;
        if ($item_count == 20)
        {
            exit();
        }
    }

?>