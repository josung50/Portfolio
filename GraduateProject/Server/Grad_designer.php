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
$_CODE = null;
$_CODE = urldecode($_POST['CODE']);

//디자이너 고유번호,
$query = mysqli_query($link,"select tinfo.seq, tinfo.uname, tinfo.image_url, tinfo.category_code, tinfo.category_name, tinfo.comments, tuvl.up_count as U_count, tuvl.view_count as View_count, tuvl.like_count as Received_like from 
(select tm.seq, tm.uname, tm.image_url, ifnull(tcn.category_code, \"008\") as category_code, ifnull(tcn.category_name, \"없음\") as category_name, tm.comments from t_member tm left outer join 
(select tmc.member_seq, tmc.category_code,ifnull(tc.category_name,\"없음\") as category_name
from t_member_category tmc left outer join t_category tc on tc.category_code = tmc.category_code) tcn on tcn.member_seq = tm.seq) tinfo, 
(select tuv.seq, tuv.up_count, tuv.view_count, ifnull(tdlc.like_count, 0) as like_count from
	(select tdu.seq, tdu.up_count, tv.view_count from 
		(select t_member.seq, ifnull(up_count,0) as up_count from t_member
		left outer join (select member_seq, count(seq) as up_count from t_design_work group by member_seq) tdu on t_member.seq = tdu.member_seq) tdu
	left outer join (select td.seq, sum(ifnull(view_cnt, 0)) as view_count from t_design_work td group by td.seq) tv on tdu.seq = tv.seq) tuv
left outer join (select td.member_seq, ifnull(sum(tdll.like_count), 0) as like_count
				from t_design_work td left outer join
					(select design_work_seq, ifnull(count(tdl.member_seq), 0) as like_count
					from t_design_work_like tdl
					group by tdl.design_work_seq) tdll on tdll.design_work_seq = td.seq
				group by td.member_seq) tdlc on tdlc.member_seq = tuv.seq) tuvl
where tuvl.seq = tinfo.seq and category_code like \"$_CODE%\"");

//echo "$_CODE tester";
while($row = mysqli_fetch_array($query))
{
    echo "<br>";
    echo "$row[seq]a!PJP";
    echo "$row[uname]a!PJP";
    echo "$row[image_url]a!PJP";
    echo "$row[category_name]a!PJP";
    echo "$row[comments]a!PJP";
    echo "$row[U_count]a!PJP";
    echo "$row[View_count]a!PJP";
    echo "$row[Received_like]a!PJP";
    $inner_query = mysqli_query($link, "select t_design_work.seq, t_design_work.title, t_design_work.thumb_uri
    from t_design_work where t_design_work.member_seq = $row[seq]");
    while($inner_row = mysqli_fetch_array($inner_query)){
        echo"$inner_row[seq]&";
        echo"$inner_row[title]&";
        echo"$inner_row[thumb_uri]::";
    }
}

$_CODE = "null";

?>