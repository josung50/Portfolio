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

$SUBJ_SEQ = "null";
$SUBJ_SEQ = urldecode($_POST['SUBJ_SEQ']);

/* 만일 주제에 내용이 없는 경우 어떻게 할 지 고려
    1) 리스트에 존재하는 '주제'에 게시된 것이 없으면 0을 보내주어 해결*/

$query = mysqli_query($link,"select X.uname, X.thumb_uri,X.title, X.seq, X.project_subject_seq, X.member_seq, X.com_count, count(Y.member_seq) as like_count
from
(select a.uname, a.title, a.thumb_uri, a.seq, a.project_subject_seq, a.member_seq, count(b.seq) as com_count
from (select a1.title, a1.seq, a1.project_subject_seq, a1.member_seq, a1.thumb_uri, a2.uname
from t_project_work a1, t_member a2
where a1.member_seq = a2.seq
and a1.del_flag = 'N'
) a
left outer join t_project_work_comment b
on a.seq = b.project_work_seq
group by a.seq) X
left outer join t_project_work_like Y
on X.seq = Y.project_work_seq
where X.project_subject_seq = $SUBJ_SEQ
group by X.seq
order by X.seq desc
");

//echo "$_CODE tester";
while($row = mysqli_fetch_array($query))
{
    echo "<br>";
    echo "$row[uname]#";
    echo "$row[thumb_uri]#";
    echo "$row[title]#";
    echo "$row[seq]#";
    echo "$row[member_seq]#";
    echo "$row[com_count]#";
    echo "$row[like_count]";
}

$SUBJ_SEQ = "null";

?>