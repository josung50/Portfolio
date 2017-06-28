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

$_CODE = "null";
$_CODE = urldecode($_POST['CODE']);
$_LOGIN_MEMBER_SEQ = "NULL";
$_LOGIN_MEMBER_SEQ = urldecode($_POST['MEMBER_SEQ']);
$_LIKE_CHECK = "UNCHECKED";

$query = mysqli_query($link,"select distinct t_design_work.title, t_design_work.view_cnt, t_design_work.thumb_uri, t_member.uname, t_design_work.register_time, t_design_work.seq,
      t_design_work.member_seq
      from t_design_work,t_design_work_category,t_member
      where t_design_work.member_seq=t_member.seq and t_design_work.del_flag = 'N' and t_design_work.seq=t_design_work_category.design_work_seq and category_code like \"$_CODE%\" ORDER BY t_design_work.register_time DESC;");
//echo "$_CODE tester";
$item_count = 0;
while($row = mysqli_fetch_array($query))
{
    $_LIKE_CHECK = "UNCHECKED";
    echo "<br>";
    echo "$row[member_seq]#";
    echo "$row[seq]#";
    echo "$row[title]#";
    echo "$row[view_cnt]#";
    echo "$row[thumb_uri]#";
    echo "$row[uname]#";
    /*$like_query = mysqli_query($link, "select * from t_design_work_like where t_design_work_like.design_work_seq = $like_design_row[seq]");
    while($like_judge_row = mysqli_fetch_array($like_query)){
        if($like_judge_row[member_seq] == $_LOGIN_MEMBER_SEQ){
            $_LIKE_CHECK = "CHECKED";
        }
    }
    echo "\($_LIKE_CHECK\)";
    */
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
$_CODE = "NULL";
?>