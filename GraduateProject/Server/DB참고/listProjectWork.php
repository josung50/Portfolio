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
    $query_exec = mysqli_query($link, "SELECT * FROM t_project_work ORDER BY seq DESC");
    $row = mysqli_fetch_row($query);
    echo "<script>";
    echo "$(document).ready(function(){\n";
    $boardCnt = 1;
    while($row = mysqli_fetch_array($query_exec))
    {
//    $safeContent = $row['contents'];
        $safeContent = "추후 수정";
        echo "var result = '<tr><td><span id=$boardCnt>".$row['seq']."</span></td><td>".addslashes($row['project_subject_seq'])."</td><td>".addslashes($row['title'])."</td><td>".$safeContent."</td><td>".addslashes($row['member_seq'])."</td><td>".$row['register_time']."</td><td>".$row['refer_project_work_seq']."</td><td>".$row['last_ver']."</td><td>".$row['del_flag']."</td><td><button id=\"deleteDB\">DELETE</button></td><td><button id=\"redoDB\">REDO</button></td></tr>';\n";
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
            $.post('deleteProjectWork.php',{
                SEQ : seq,
            },function (callback) {
                if(callback=="OK"){
                    location.reload(true);
                }
            });
        });
        $(document).on("click","#redoDB",function(){
            //가장 가까운 tr값을 찾아냄.
            var idx = $(this).closest('tr').prevAll().length;
            var seq = $('#'+idx).text();
            //seq에 해당하는 게시물을 지운다.
            $.post('redoProjectWork.php',{
                SEQ : seq,
            },function (callback) {
                if(callback=="OK"){
                    location.reload(true);
                }
            });
        });
    </script>
</head>
<body>
<div id="contentDiv">
    <table id="contentTable" border="1px">
        <tr>
            <th>SEQ</th>
            <th>Project Subject SEQ</th>
            <th>Title</th>
            <th>Contents</th>
            <th>Member</th>
            <th>RegisterTime</th>
            <th>Refer Project Work SEQ(참조 작품 SEQ)</th>
            <th>Last Ver</th>
            <th>del_flag</th>
            <th>DELETE BTN</th>
            <th>REDO</th>
        </tr>
    </table>
</div>
</body>
</html>
