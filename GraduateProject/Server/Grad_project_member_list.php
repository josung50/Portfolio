<?php
/**
 * Created by PhpStorm.
 * User: choi
 * Date: 2017-05-15
 * Time: 오후 3:00
 */
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
$_PROJECT_SEQ = "NULL";
$_PROJECT_SEQ = urldecode($_POST["PROJECT_SEQ"]);
$_LOGIN_MEMBER_SEQ = "NULL";
$_LOGIN_MEMBER_SEQ = urldecode($_POST["MEMBER_SEQ"]);

#$_PROJECT_SEQ = 38;
#$_LOGIN_MEMBER_SEQ = 17;

$_INCLUDE_IN_PROJECT = "NO";

$include_check_query = mysqli_query($link, "select * from t_project_member where t_project_member.project_seq = $_PROJECT_SEQ");
while($member_check_row = mysqli_fetch_array($include_check_query)){
    if($member_check_row[member_seq] == $_LOGIN_MEMBER_SEQ){
        $_INCLUDE_IN_PROJECT = "YES";
    }
}
# 로그인한 유저가 프로젝트에 속해있을 경우, 최상단에 해당 사용자의 정보를 보여줌.
if($_INCLUDE_IN_PROJECT == "YES") {
    $login_user_info_query = mysqli_query($link,"select DESIGNER_INFO.seq, DESIGNER_INFO.uname, DESIGNER_INFO.image_url, DESIGNER_INFO.category_name, DESIGNER_INFO.comments, DESIGNER_INFO.U_count, DESIGNER_INFO.Received_like, DESIGNER_INFO.View_count from 
	(select mem_iC_Uc_Lc.seq, mem_iC_Uc_Lc.uname, mem_iC_Uc_Lc.image_url, mem_iC_Uc_Lc.category_name, ifnull(mem_iC_Uc_Lc.comments,\"없음\") as comments, mem_iC_Uc_Lc.U_count, mem_iC_Uc_Lc.Received_like, ifnull(R_viewed.View_count, 0) as View_count
	from 
		(select mem_iC_Uc.seq, mem_iC_Uc.uname, mem_iC_Uc.image_url, mem_iC_Uc.comments, ifnull(mem_iC_Uc.category_name, \"없음\") as category_name, mem_iC_Uc.U_count, ifnull(R_like.like_count,0) as Received_like from 	
			(select mem_iC.seq, mem_iC.uname, mem_iC.image_url, mem_iC.comments, mem_iC.category_name, ifnull(mem_with_Udesign.U_count,0) as U_count
			from
				(select m.seq, m.uname, m.image_url, m.comments, user_cate.category_name
				from t_member m left outer join
					(select t_mc.member_seq, t_c.category_name
					from t_member_category t_mc, t_category t_c
					where t_mc.category_code = t_c.category_code) user_cate
				on m.seq = user_cate.member_seq) mem_iC left outer join    
				(select mem.seq as mem_seq, count(mem.seq) as U_count
				from t_member mem left outer join t_design_work up_design
				on mem.seq = up_design.member_seq
				where up_design.del_flag = 'N'
				group by mem.seq) mem_with_Udesign
				on mem_iC.seq = mem_with_Udesign.mem_seq) mem_iC_Uc left outer join
			(select d.member_seq, sum(ifnull(dl_count.like_count, 0)) as like_count
			from t_design_work d left outer join
				(select design_work_seq, count(*) as like_count
				from t_design_work_like
				group by design_work_seq) dl_count on d.seq = dl_count.design_work_seq
			where d.del_flag = 'N'
			group by member_seq) R_like
		on mem_iC_Uc.seq = R_like.member_seq) mem_iC_Uc_Lc left outer join
		(select td.member_seq, sum(td.view_cnt) as View_count
		from t_design_work td
		group by td.member_seq) R_viewed on mem_iC_Uc_Lc.seq = R_viewed.member_seq) DESIGNER_INFO 
	where DESIGNER_INFO.seq = $_LOGIN_MEMBER_SEQ");
    $login_user_info_row = mysqli_fetch_array($login_user_info_query);
    echo "<br>";
    echo "$login_user_info_row[seq]a!PJP";
    echo "$login_user_info_row[uname]a!PJP";
    echo "$login_user_info_row[image_url]a!PJP";
    echo "$login_user_info_row[category_name]a!PJP";
    echo "$login_user_info_row[comments]a!PJP";
    echo "$login_user_info_row[U_count]a!PJP";
    echo "$login_user_info_row[Received_like]a!PJP";
    echo "$login_user_info_row[View_count]a!PJP";
    $inner_query = mysqli_query($link, "select t_design_work.seq, t_design_work.title, t_design_work.thumb_uri
    from t_design_work where t_design_work.member_seq = $login_user_info_row[seq]");
    while($inner_row = mysqli_fetch_array($inner_query)){
        echo"$inner_row[seq]&";
        echo"$inner_row[title]&";
        echo"$inner_row[thumb_uri]::";
    }
}
# 프로젝트에 속해있는 멤버의 리스트를 보여줌.
$project_member_list_query = mysqli_query($link, "select DESIGNER_INFO.seq, DESIGNER_INFO.uname, DESIGNER_INFO.image_url, DESIGNER_INFO.category_name, DESIGNER_INFO.comments, DESIGNER_INFO.U_count, DESIGNER_INFO.Received_like, DESIGNER_INFO.View_count from 
	(select mem_iC_Uc_Lc.seq, mem_iC_Uc_Lc.uname, mem_iC_Uc_Lc.image_url, mem_iC_Uc_Lc.comments,
	mem_iC_Uc_Lc.category_name, mem_iC_Uc_Lc.U_count, mem_iC_Uc_Lc.Received_like, ifnull(R_viewed.View_count, 0) as View_count from 
		(select mem_iC_Uc.seq, mem_iC_Uc.uname, mem_iC_Uc.image_url, ifnull(mem_iC_Uc.comments,\"없음\") as comments, ifnull(mem_iC_Uc.category_name, \"없음\") as category_name, mem_iC_Uc.U_count, ifnull(R_like.like_count,0) as Received_like from 	
			(select mem_iC.seq, mem_iC.uname, mem_iC.image_url, mem_iC.comments, mem_iC.category_name, ifnull(mem_with_Udesign.U_count,0) as U_count
			from
				(select m.seq, m.uname, m.image_url, m.comments, user_cate.category_name
				from t_member m left outer join
					(select t_mc.member_seq, t_c.category_name
					from t_member_category t_mc, t_category t_c
					where t_mc.category_code = t_c.category_code) user_cate
				on m.seq = user_cate.member_seq) mem_iC left outer join    
				(select mem.seq as mem_seq, count(mem.seq) as U_count
				from t_member mem left outer join t_design_work up_design
				on mem.seq = up_design.member_seq
				where up_design.del_flag = 'N'
				group by mem.seq) mem_with_Udesign
				on mem_iC.seq = mem_with_Udesign.mem_seq) mem_iC_Uc left outer join
			(select d.member_seq, sum(ifnull(dl_count.like_count, 0)) as like_count
			from t_design_work d left outer join
				(select design_work_seq, count(*) as like_count
				from t_design_work_like
				group by design_work_seq) dl_count on d.seq = dl_count.design_work_seq
			where d.del_flag = 'N'
			group by member_seq) R_like
		on mem_iC_Uc.seq = R_like.member_seq) mem_iC_Uc_Lc left outer join
		(select td.member_seq, sum(td.view_cnt) as View_count
		from t_design_work td
		group by td.member_seq) R_viewed on mem_iC_Uc_Lc.seq = R_viewed.member_seq) DESIGNER_INFO, 
	(select pm.member_seq, pm.project_seq from t_project_member pm where pm.member_seq != $_LOGIN_MEMBER_SEQ and pm.project_seq = $_PROJECT_SEQ) PROJECT_MEMBER
where DESIGNER_INFO.seq = PROJECT_MEMBER.member_seq");
while($project_member_list_row = mysqli_fetch_array($project_member_list_query)){
    echo "<br>";
    echo "$project_member_list_row[seq]a!PJP";
    echo "$project_member_list_row[uname]a!PJP";
    echo "$project_member_list_row[image_url]a!PJP";
    echo "$project_member_list_row[category_name]a!PJP";
    echo "$project_member_list_row[comments]a!PJP";
    echo "$project_member_list_row[U_count]a!PJP";
    echo "$project_member_list_row[Received_like]a!PJP";
    echo "$project_member_list_row[View_count]a!PJP";
    $inner_query = mysqli_query($link, "select t_design_work.seq, t_design_work.title, t_design_work.thumb_uri
    from t_design_work where t_design_work.member_seq = $project_member_list_row[seq]");
    while($inner_row = mysqli_fetch_array($inner_query)){
        echo"$inner_row[seq]&";
        echo"$inner_row[title]&";
        echo"$inner_row[thumb_uri]::";
    }
}

?>