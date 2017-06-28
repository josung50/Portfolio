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
$query_exec = mysqli_query($link, "SELECT * FROM t_point_history ORDER BY seq DESC");
$row = mysqli_fetch_row($query);
echo "<script>";
echo "$(document).ready(function(){\n";
$boardCnt = 1;
while($row = mysqli_fetch_array($query_exec))
{
//    $safeContent = $row['contents'];
    echo "var result = '<tr><td><span id=$boardCnt>".$row['seq']."</span></td><td>".$row['sign']."</td><td>".$row['amount']."</td><td>".$row['accum_amount']."</td><td>".$row['register_time']."</td><td>".$row['member_seq']."</td><td>".$row['order_seq']."</td><td>".$row['comments']."</td><td><button id=\"deleteDB\">DELETE</button></td></tr>';\n";
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
</script>
<body>
<div id="contentDiv">
    <table id="contentTable" border="1px">
        <tr>
            <th>SEQ</th>
            <th>Sign(가감구분)</th>
            <th>Amount(금액)</th>
            <th>Accum Amount(누적결과포인트)</th>
            <th>Register Time(등록일시)</th>
            <th>Member SEQ)(회원seq)</th>
            <th>Order SEQ(구매seq)</th>
            <th>Comments(비고)</th>
            <th>DELETE BTN</th>
        </tr>
    </table>
</div>
</body>
</html>
