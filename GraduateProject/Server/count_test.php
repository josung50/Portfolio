<?php
$servername = "localhost";
$username = "root";
$password = "";
$dbTable = "opendesign";

$link = mysqli_connect($servername, $username, $password, $dbTable);
mysqli_query($link, " SET NAMES UTF8");
if (!$link) {
    printf("Connect failed: %s\n", mysqli_connect_error());
    exit();
}
echo date("YmdHis");
$project_with_user_query = mysqli_query($link, "select * from(
select * from (select distinct t_project.project_name,t_project.file_url as thumb_uri,t_member.uname, t_project.seq as projectSeq, t_project.register_time
from t_project,t_project_member,t_member
where t_member.seq=t_project.owner_seq
and t_project.del_flag = 'N'
and t_project.progress_status='P') t1,
(select t_project_subject.project_seq, count(*) as 'file_count' from t_project_work, t_project_subject
where t_project_work.project_subject_seq = t_project_subject.seq
and t_project_work.del_flag = 'N'
group by t_project_subject.project_seq)t2,
(select t_project.seq, count(t_project_member.member_seq) as 'mem_count'
from t_project, t_project_member
where t_project.seq = t_project_member.project_seq
group by t_project.seq)t3
where t2.project_seq = t1.projectSeq
and t1.projectSeq = t3.seq
order by t1.projectSeq asc) projectCardInfo,
(select t_project.seq from t_project_member, t_project
where t_project_member.project_seq = t_project.seq
and t_project_member.member_seq = 17) projectWithUser
where projectCardInfo.projectSeq = projectWithUser.seq");
while($project_row = mysqli_fetch_array($project_with_user_query)){
    echo"<br>";
    echo"$project_row[project_name]#";
    echo"$project_row[uname]#";
    echo"$project_row[thumb_uri]#";
    echo"$project_row[mem_count]#";
    echo"$project_row[file_count]#";
    echo"$project_row[projectSeq]#";
    $member_seq_finding_query = mysqli_query($link, "select member_seq from t_project_member where t_project_member.project_seq = $project_row[projectSeq]");
    while($member_finding_row = mysqli_fetch_array($member_seq_finding_query)){
        echo "M$member_finding_row[member_seq]";
    }
}
?>