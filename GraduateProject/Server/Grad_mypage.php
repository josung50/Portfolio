<?php
/**
 * Created by PhpStorm.
 * User: choi
 * Date: 2017-05-03
 * Time: 오후 2:28
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
//MENU 확인
$_MENU = "NULL";
$_MENU = urldecode($_POST["MENU"]);
//MEMBER_SEQ 확인
$_MEMBER_SEQ = "NULL";
$_MEMBER_SEQ = urldecode($_POST["MEMBER_SEQ"]);
//변수 새로 할당
$_LOGIN_MEMBER_SEQ = $_MEMBER_SEQ;

//좋아하는 디자인인지 확인
$_LIKE_CHECK = "UNCHECKED";
if($_MENU == "uploadDesign") {
    #내가 등록한 디자인 ( 최근 순 )
    # a!PJP로 구분 ( contents 때문 )
    # 순서대로  ->  제목, 조회수, 썸네일이미지, 상세내용, 제작자
    #제작자seq # 디자인카드 seq # 제목 # 조회수 # 썸네일 경로 # 제작자,등록자이름
    $upload_design_query = mysqli_query($link, "select d.member_seq, d.seq, d.view_cnt, d.title, d.thumb_uri, d.register_time, m.uname from t_design_work d, t_member m
where m.seq = d.member_seq and d.member_seq = $_MEMBER_SEQ ORDER BY register_time DESC;");
    while ($upload_design_row = mysqli_fetch_array($upload_design_query)) {
        $_LIKE_CHECK = "UNCHECKED";
        echo "<br>";
        echo "$upload_design_row[member_seq]#";
        echo "$upload_design_row[seq]#";
        echo "$upload_design_row[title]#";
        echo "$upload_design_row[view_cnt]#";
        echo "$upload_design_row[thumb_uri]#";
        echo "$upload_design_row[uname]#";
        $like_query = mysqli_query($link, "select * from t_design_work_like where t_design_work_like.design_seq = $upload_design_row[seq]");
        while($like_judge_row = mysqli_fetch_array($like_query)){
            if($like_judge_row[member_seq] == $_LOGIN_MEMBER_SEQ){
                $_LIKE_CHECK = "CHECKED";
            }
        }
        echo "\($_LIKE_CHECK\)";
    }
}
else if($_MENU == "likeDesign") {
    #내가 관심있는 디자인
    # a!PJP로 구분 ( contents 때문 )
    #순서대로 -> 디자인 seq, 디자인 제목, 디자인 썸네일이미지, 디자인 상세내용, 디자인 제작자, 디자인 조회수, 디자인 좋아요 수, 디자인 댓글 수
    #제작자seq # 디자인카드 seq # 제목 # 조회수 # 썸네일 경로 # 제작자,등록자이름 # 좋아요 여부
    $user_favorite_design_query = mysqli_query($link, "select distinct *
from(
	select tableWithLikeCnt.seq, tableWithLikeCnt.title, tableWithLikeCnt.view_cnt, tableWithLikeCnt.contents, tableWithLikeCnt.thumb_uri,
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
	group by tableWithLikeCnt.seq) upload_design_info,
    (select t_design_work.seq as finding_seq
    from t_design_work, t_design_work_like
    where t_design_work.seq = t_design_work_like.design_work_seq and t_design_work_like.member_seq = $_MEMBER_SEQ) userLikeThisWork
where upload_design_info.seq = userLikeThisWork.finding_seq");
    while($like_design_row = mysqli_fetch_array($user_favorite_design_query)){
        $_LIKE_CHECK = "UNCHECKED";
        echo"<br>";
        echo"$like_design_row[member_seq]#";
        echo"$like_design_row[seq]#";
        echo"$like_design_row[title]#";
        echo"$like_design_row[view_cnt]#";
        echo"$like_design_row[thumb_uri]#";
        echo"$like_design_row[uname]#";
        $like_query = mysqli_query($link, "select * from t_design_work_like where t_design_work_like.design_work_seq = $like_design_row[seq]");
        while($like_judge_row = mysqli_fetch_array($like_query)){
            if($like_judge_row[member_seq] == $_LOGIN_MEMBER_SEQ){
                $_LIKE_CHECK = "CHECKED";
            }
        }
        echo "\($_LIKE_CHECK\)";
        #echo"$like_design_row[like_count]a!PJP";
        #echo"$like_design_row[comm_count]";
    }
}
else if($_MENU == "myProject") {
    #내가 참여중인 프로젝트
    #순서대로 -> 프로젝트 seq, 프로젝트 이름,프로젝트 생성자 닉네임, 프로젝트 썸네일이미지, 프로젝트 등록 시간, 프로젝트 파일 갯수, 프로젝트 참여 중인 멤버 수
    #프로젝트 이름 # 프로젝트 생성자 # 썸네일 경로 # 멤버수 # 파일수 # 프로젝트 고유 seq # 프로젝트 멤버 전원 seq
    $project_with_user_query = mysqli_query($link, "select * from(
select tt1.pproject_seq, tt1.project_name, tt1.thumb_uri, tt1.uname,
tt1.owner_seq, tt1.register_time, ifnull(tt1.file_count,0) as file_count, ifnull(t3.mem_count, 0) as mem_count from
	(select * from
		(select distinct t_project.seq as pproject_seq, t_project.project_name,t_project.file_url as thumb_uri,t_member.uname, t_project.owner_seq, t_project.register_time
		from t_project,t_project_member,t_member
		where t_member.seq=t_project.owner_seq
		and t_project.del_flag = 'N'
		and t_project.progress_status='P') t1 left outer join
		(select t_project_subject.project_seq, ifnull(count(*),0) as 'file_count' from t_project_work, t_project_subject
		where t_project_work.project_subject_seq = t_project_subject.seq
		and t_project_work.del_flag = 'N'
		group by t_project_subject.project_seq)t2
	on t1.pproject_seq = t2.project_seq)tt1 left outer join
	(select t_project.seq as project_seq, ifnull(count(t_project_member.member_seq),0) as 'mem_count'
	from t_project, t_project_member
	where t_project.seq = t_project_member.project_seq
	group by t_project.seq)t3
    on tt1.pproject_seq = t3.project_seq
order by tt1.pproject_seq desc) projectCardInfo,
(select t_project.seq from t_project_member, t_project
where t_project_member.project_seq = t_project.seq
and t_project_member.member_seq = $_MEMBER_SEQ) projectWithUser
where projectCardInfo.pproject_seq = projectWithUser.seq");
    while($project_row = mysqli_fetch_array($project_with_user_query)){
        echo"<br>";
        echo"$project_row[project_name]#";
        echo"$project_row[uname]#";
        echo"$project_row[owner_seq]#";
        echo"$project_row[thumb_uri]#";
        echo"$project_row[mem_count]#";
        echo"$project_row[file_count]#";
        echo"$project_row[pproject_seq]#";
        $member_seq_finding_query = mysqli_query($link, "select member_seq from t_project_member where t_project_member.project_seq = $project_row[pproject_seq]");
        while($member_finding_row = mysqli_fetch_array($member_seq_finding_query)){
            echo "M$member_finding_row[member_seq]";
        }
    }
}
/*else if($_MENU == "myGroup") {
    #내가 속한 그룹
    #그룹 이름때문에 a!PJP로 구분
    #순서대로 -> 그룹 seq, 그룹 이름, 그룹에 속한 멤버 수
    #그룹 seq # 그룹 타이틀 # 그룹 멤버 수 # 그룹원 정보(멤버seq!#!멤버이름!#!멤버프로필uri;;)
    $group_with_user_query = mysqli_query($link, "select groupInfo.group_name, groupInfo.seq, groupMemberCount.member_count
from(select g.group_name, g.seq
	from t_pgroup g
    where g.member_seq = $_MEMBER_SEQ) groupInfo left outer join
	(select g_member.seq,count(g_member.member_seq) as member_count
    from t_pgroup g_member
    where g_member.member_seq = $_MEMBER_SEQ
    group by g_member.seq) groupMemberCount on groupInfo.seq = groupMemberCount.seq
");
    while($group_row = mysqli_fetch_array($group_with_user_query)){
        echo"<br>";
        echo"$group_row[seq]";
        echo"$group_row[group_name]";
        echo"$group_row[member_count]";
    }
}*/
?>