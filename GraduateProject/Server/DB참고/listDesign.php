<?php
include_once "head.php";
include_once "header.php";

//DB연결
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
//필요한 기능
//1. 게시물 정보 보기
//2. 게시물 삭제
//3. 추천 게시물
//4. 추천 디자이너

//전체 게시물 보기
$query_exec = mysqli_query($link, "SELECT * FROM t_design_work ORDER BY register_time DESC");
$row = mysqli_fetch_row($query);
echo "<script>";
echo "$(document).ready(function(){\n";
$boardCnt = 1;
while($row = mysqli_fetch_array($query_exec))
{
//    $safeContent = $row['contents'];
    $safeContent = "추후 수정";
    echo"<br>";
    echo "<tr><td><span id=$boardCnt>".$row['seq']."</span></td><td>".addslashes($row['title'])."</td><td>".$row['license']."</td><td>".addslashes($row['point'])."</td><td><a href=\"http://113.198.210.237:80".$row['thumb_uri']."\" target=\"_blank\"><img src=\"http://113.198.210.237:80".addslashes($row['thumb_uri'])."\" height=\"42\" width=\"42\"></a></td><td>".addslashes($safeContent)."</td><td>".addslashes($row['register_time'])."</td><td>".addslashes($row['tags'])."</td><td>".addslashes($row['member_seq'])."</td><td>".$row['update_time']."</td><td>".$row['del_flag']."</td><td><button id=\"deleteDB\">DELETE</button></td></td><td><button id=\"redoDB\">REDO</button></td><td><button id=\"uploadMain\">uploadMain</button></td></tr>';\n";
    
    echo "\n";
    $boardCnt++;

}
echo "\n});";
echo "</script>";
?>
<script>
    $(document).on("click","#deleteDB",function(){
        //가장 가까운 tr값을 찾아냄.
        var idx = $(this).closest('tr').prevAll().length;
        var seq = $('#'+idx).text();
        //seq에 해당하는 게시물을 지운다.
        $.post('deleteDesign.php',{
            SEQ : seq,
        },function (callback) {
            if(callback=='OK'){
                location.reload(true);
            }
        });
    });
    $(document).on("click","#redoDB",function(){
        //가장 가까운 tr값을 찾아냄.
        var idx = $(this).closest('tr').prevAll().length;
        var seq = $('#'+idx).text();
        //seq에 해당하는 게시물을 지운다.
        $.post('redoDesign.php',{
            SEQ : seq,
        },function (callback) {
            if(callback=='OK'){
                location.reload(true);
            }
        });
    });
    $(document).on("click","#uploadMain",function(){
        //가장 가까운 tr값을 찾아냄.
        var idx = $(this).closest('tr').prevAll().length;
        var seq = $('#'+idx).text();
        //seq에 해당하는 게시물을 등록한다.
        $.post('uploadMain.php',{
            TYPE : 2,
            SEQ : seq,
        },function (callback) {
            if(callback=='OK'){
                alert("등록완료");
                location.reload(true);
            }
        });
    });
</script>
<body>
<div id="contentDiv">
    <table id="contentTable" border="1px">
        <tr>
            <th>SEQ</th>
            <th>Title</th>
            <th>License</th>
            <th>Point</th>
            <th>Image</th>
            <th>Contents</th>
            <th>RegisterTime</th>
            <th>Tags</th>
            <th>Member</th>
            <th>UpdateTime</th>
            <th>del_flag</th>
            <th>DELETE BTN</th>
            <th>REDO</th>
            <th>메인에 올리기</th>
        </tr>
    </table>
</div>
</body>
</html>
