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
# title, license, point, thumb_uri, contents, tags( |~~|~~| ) , member_seq, del_flag
# 입력해야할 것 >> origin_seq, register_time, update_time
$NOW_DATE = date("YmdHi");

$_ORIGIN_SEQ = 0; #지정
$_TITLE = urldecode($_POST['TITLE']);#디자인 제목 받아옴
$_LICENSE = "111"; #지정
$_POINT = 0; #지정
$_CONTENTS = urldecode($_POST['CONTENTS']); #디자인 상세내용 받아옴
$_REGISTER_TIME = $NOW_DATE;
$_MEMBER_SEQ = urldecode($_POST['MEMBER_SEQ']); #디자인 제작자 seq 받아옴
$_UPDATE_TIME = $NOW_DATE;
$_DEL_FLAG = 'N';

$_IMAGE_LIST = urldecode($_POST['IMAGE_LIST']); // ^image1.jpeg^image2.jpeg^image3.jpeg^image4.jpeg^image5.jpeg
$_FILE_COUNT = substr_count($_IMAGE_LIST, "^");
$_IMAGE = explode("^", $_IMAGE_LIST);

$_TAGS_LIST = urldecode($_POST['TAGS']); // #tag1#tag2#tag3#tag4#tag5#tag6#tag7
$_TAGS_COUNT = substr_count($_TAGS, "#");
$_TAGS_TEMP = explode("#", $_TAGS_LIST);
$_TAGS= "|";

for($i = 1; $i <= $_TAGS_COUNT; $i++){
    $_TAGS = $_TAGS.$_TAGS_TEMP[$i];
    $_TAGS = $_TAGS."|";
}

// 사용 시 인덱스는 1 <= x <= COUNT
$insert_design_work_query = mysqli_query($link, "insert into t_design_work(origin_seq, title, license, point, thumb_uri, contents, register_time, tags, member_seq, update_time, del_flag)
    values($_ORIGIN_SEQ, \"$_TITLE\", \"$_LICENSE\", $_POINT, \"/resources/km_upload/product/$_IMAGE[1]\", \"$_CONTENTS\", \"$_REGISTER_TIME\", \"$_TAGS\", $_MEMBER_SEQ, \"$_UPDATE_TIME\", \"$_DEL_FLAG\")");
$insert_design_work_row = mysqli_fetch_row($insert_design_work_query);
$get_design_seq = mysqli_query($link, "select seq from t_design_work t where t.member_seq = $_MEMBER_SEQ and t.register_time LIKE \"$_REGISTER_TIME\"");
$get_design_row = mysqli_fetch_array($get_design_seq);
$insert_design_cate_query = mysqli_query($link, "insert into t_design_work_category(design_work_seq, category_code, register_time) values($get_design_row[seq], \"008\", $_REGISTER_TIME)");
$insert_design_cate_row = mysqli_fetch_row($insert_design_cate_query);
for($pre = 1; $pre <= $_FILE_COUNT; $pre++){
    $insert_preview_query = mysqli_query($link, "insert into t_design_preview_image(design_work_seq, file_uri, filename) values($get_design_row[seq], \"/resources/km_upload/product/$_IMAGE[$pre]\", \"$_IMAGE[$pre]\")");
    $insert_preview_row = mysqli_fetch_row($insert_preview_query);
}
#echo "<br>$_STRING_TOKEN[$total_size]";
/*while($_TEMP > -1){
    $_STRING_TOKEN[$total_size] = strtok($_STRING, '^');
    $total_size++;
    $_TEMP--;
}*/
/*while($total_size > -1){
    echo"$_STRING_TOKEN[$total_size]<br>";
}*/

?>
