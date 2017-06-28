<?php
include_once "head.php";
include_once "header.php";
//DB연결
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
//필요한 기능
//1. 게시물 정보 보기
//2. 게시물 삭제
//3. 추천 게시물
//4. 추천 디자이너


//전체 게시물 보기
$query_exec = mysqli_query($link, "SELECT * FROM t_member ORDER BY seq DESC");
$row = mysqli_fetch_row($query);
echo "<script>";
echo "$(document).ready(function(){\n";
$boardCnt = 1;
while($row = mysqli_fetch_array($query_exec))
{
    $safeContent = "추후 수정";
    echo "var result = '<tr><td><span id=$boardCnt>".$row['seq']."</span></td><td>".$row['email']."</td><td>".$row['uname']."</td><td><image src=\"http://113.198.210.237:80".addslashes($row['image_url'])."\"height=\"42\" width=\"42\"/></td><td>".addslashes($safeContent)."</td><td>".$row['member_type']."</td><td>".$row['point']."</td><td>".$row['register_time']."</td><td>".$row['update_time']."</td><td>".$row['sido_seq']."</td><td><button id=\"uploadMain\">uploadMain</button><td><button id=\"deleteDB\">DELETE</button></td></tr>';\n";
    echo "$('#contentTable').append(result);\n";
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
        $.post('deleteGroup.php',{
            SEQ : seq,
        },function (callback) {
        });
    });
    $(document).on("click","#uploadMain",function(){
        //가장 가까운 tr값을 찾아냄.
        var idx = $(this).closest('tr').prevAll().length;
        var seq = $('#'+idx).text();
        //seq에 해당하는 게시물을 등록한다.
        $.post('uploadMain.php',{
            TYPE : 1,
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
            <th>Email</th>
            <th>uname</th>
            <th>Image URI</th>
            <th>Comments</th>
            <th>Member Type</th>
            <th>Point</th>
            <th>Register Time</th>
            <th>Update Time</th>
            <th>Sido SEQ</th>
            <th>메인에 올리기</th>
            <th>DELETE BTN</th>
        </tr>
    </table>
</div>
</body>
</html>
