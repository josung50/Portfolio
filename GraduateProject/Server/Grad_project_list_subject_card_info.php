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

$PROJECT_WORK_SEQ = "null";
$PROJECT_WORK_SEQ = urldecode($_POST['PROJECT_WORK_SEQ']);
$LOGIN_USER_SEQ = "null";
$LOGIN_USER_SEQ = urldecode($_POST['LOGIN_USER_SEQ']);
$LIKE_CHECK = "UNCHECKED";

$query = mysqli_query($link,"select t_pwork_frame_COMM.title, t_pwork_frame_COMM.contents, t_pwork_frame_COMM.seq, t_pwork_frame_COMM.member_seq,
		t_pwork_frame_COMM.uname, t_pwork_frame_COMM.register_time, t_pwork_frame_COMM.comm_count, count(t_like.member_seq) as like_count
from 
(select t_pwork_frame.title, t_pwork_frame.contents, t_pwork_frame.seq, t_pwork_frame.member_seq, t_pwork_frame.uname,
		t_pwork_frame.register_time, count(COMM.project_work_seq) as comm_count
from(select t_project_work.title, t_project_work.contents, t_project_work.seq, t_project_work.member_seq, t_member.uname,
		t_project_work.register_time
 from t_project_work, t_member
 where t_member.seq = t_project_work.member_seq
	and del_flag = 'N') t_pwork_frame
    left outer join t_project_work_comment COMM on t_pwork_frame.seq = COMM.project_work_seq
    group by t_pwork_frame.seq order by t_pwork_frame.seq asc) t_pwork_frame_COMM
    left outer join t_project_work_like t_like on t_pwork_frame_COMM.seq = t_like.project_work_seq
    where t_pwork_frame_COMM.seq = $PROJECT_WORK_SEQ
    group by t_pwork_frame_COMM.seq");

//echo "$_CODE tester";

$row = mysqli_fetch_array($query);

    echo "$row[uname]a!PJP";
    echo "$row[title]a!PJP";
    echo "$row[seq]a!PJP";
    echo "$row[member_seq]a!PJP";
    echo "$row[contents]a!PJP";
    echo "$row[register_time]a!PJP";
    echo "$row[comm_count]a!PJP";
    echo "$row[like_count]a!PJP";
    $like_query = mysqli_query($link,"select * from t_project_work_like where t_project_work_like.project_work_seq = $row[seq]");
    while($like_row = mysqli_fetch_array($like_query)){
        if($like_row[member_seq] == $LOGIN_USER_SEQ){
            $LIKE_CHECK = "CHECKED";
        }
    }
    echo "\($LIKE_CHECK\)a!PJP";
    $inner_query = mysqli_query($link, "select distinct t_pwork_ver.project_work_seq, t_pwork_ver.seq as file_seq, t_pwork_ver.file_uri
    from t_project_work_ver t_pwork_ver, t_project_work
    where t_pwork_ver.project_work_seq = $row[seq]
    order by t_pwork_ver.project_work_seq desc, t_pwork_ver.seq desc");
    $cnt = 0;
    while($inner_row = mysqli_fetch_array($inner_query)){
        echo "$inner_row[file_seq]&";
        echo "$inner_row[file_uri]::";
        $cnt++;
        if($cnt == 1)
            exit();
    }

$PROJECT_WORK_SEQ = "null";
$LOGIN_USER_SEQ = "null";
$LIKE_CHECK = "null";

?>