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

$DESIGN_WORK_SEQ = "null";
$DESIGN_WORK_SEQ = urldecode($_POST['DESIGN_WORK_SEQ']);

$query = mysqli_query($link,"select tableWithLikeCnt.seq, tableWithLikeCnt.title, tableWithLikeCnt.view_cnt, tableWithLikeCnt.contents, tableWithLikeCnt.thumb_uri,
		tableWithLikeCnt.register_time, tableWithLikeCnt.tags, tableWithLikeCnt.member_seq, tableWithLikeCnt.uname, tableWithLikeCnt.like_count,
		count(tableToCountComm.seq) as comm_count
from(
	select t1.seq, t1.title, t1.view_cnt, t1.contents, t1.thumb_uri, t1.register_time, t1.tags, t1.member_seq, t1.uname,
		count(t2.member_seq) as like_count
	from
		(select t_design_work.seq, t_design_work.title, t_design_work.view_cnt, t_design_work.contents,
		t_design_work.thumb_uri, t_design_work.register_time, t_design_work.tags, t_design_work.member_seq, t_member.uname
		from t_design_work, t_member
		where t_member.seq = t_design_work.member_seq) t1
    left outer join t_design_work_like t2 on t1.seq = t2.design_work_seq group by t1.seq) tableWithLikeCnt
left outer join t_design_work_comment tableToCountComm on tableWithLikeCnt.seq = tableToCountComm.design_work_seq
where tableWithLikeCnt.seq = $DESIGN_WORK_SEQ
group by tableWithLikeCnt.seq
");
$view_cnt_query = mysqli_query($link, "update t_design_work set view_cnt=(view_cnt+1) where seq = $DESIGN_WORK_SEQ");
//update view_count
$view_cnt_row = mysqli_fetch_array($view_cnt_query);
//echo "$_CODE tester";
$row = mysqli_fetch_array($query);
echo "$row[seq]a!PJP";
echo "$row[title]a!PJP";
echo "$row[thumb_uri]a!PJP";
echo "$row[view_cnt]a!PJP";
echo "$row[contents]a!PJP";
echo "$row[register_time]a!PJP";
echo "$row[tags]a!PJP";
echo "$row[member_seq]a!PJP";
echo "$row[uname]a!PJP";
echo "$row[like_count]a!PJP";
echo "$row[comm_count]a!PJP";
$inner_query = mysqli_query($link, "select a.design_work_seq, a.inner_image_seq, a.file_uri
from(
	select t_design_preview_image.design_work_seq, t_design_preview_image.seq as inner_image_seq, t_design_preview_image.file_uri
    from t_design_preview_image 
    order by inner_image_seq asc) a
    where a.design_work_seq = $row[seq]
");
while($inner_row = mysqli_fetch_array($inner_query)){
    echo "$inner_row[inner_image_seq]&";
    echo "$inner_row[file_uri]::";
}

?>
