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
$query_exec = mysqli_query($link, "SELECT * FROM t_stat_activities");
$row = mysqli_fetch_row($query);
echo "<script>";
echo "$(document).ready(function(){\n";
$boardCnt = 1;
while($row = mysqli_fetch_array($query_exec))
{
//    $safeContent = $row['contents'];
    echo "var result = '<tr><td><span id=$boardCnt>".$row['stat_month']."</span></td><td>".$row['target_seq']."</td><td>".addslashes($row['target_type'])."</td><td>".$row['update_time']."</td><td><button id=\"deleteDB\">DELETE</button></td></tr>';\n";
    echo "$('#contentTable').append(result);\n";
    $boardCnt++;
}
echo "\n});";
echo "</script>";
?>
<script>
    $(document).on("click","#deleteDB",function(){
        //가장 가까운 tr값을 찾아냄.
        var idx = $(this).closest('td').prev().prev().prev().text();
        var type = $(this).closest('td').prev().prev().text();

        //seq에 해당하는 게시물을 지운다.
        $.post('deleteStat.php',{
            SEQ : idx,
            TYPE : type
        },function (callback) {
            if(callback=='OK'){
                alert("삭제완료");
                location.reload(true);
            }
        });
    });
</script>
<body>
<div id="contentDiv">
    <table id="contentTable" border="1px">
        <tr>
            <th>Stat Month(집계 월)</th>
            <th>Target SEQ(대상)</th>
            <th>Target Type(대상형태)</th>
            <th>Update Time(수정일자)</th>
            <th>DELETE BTN</th>
        </tr>
    </table>
</div>
<button id="addDesign">디자인 추가</button></body>
<button id="addDesigner">디자이너 추가</button></body>

</html>
