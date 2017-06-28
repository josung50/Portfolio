<?php

ftp_upload($files,$source_dir,$target_dir);

function ftp_upload($files,$source_dir,$target_dir){
    //파일이름
    $files = "transfer_test_file.txt";
    //파일이 존재하는 directory
    $source_dir = "/var/www/html/grad/";
    //파일의 목적 directory
    $target_dir = "/home/kim/target";

    //타겟의 주소
    $ftp_host = "113.198.210.237";
    //타겟의 id
    $ftp_user = "kim";
    //타겟의 pwd
    $ftp_pass = "crc503";
    //타겟 port
    $ftp_port = "10022";
    $result = 0;

    if(!($conn_id = ftp_connect($ftp_host, $ftp_port))) die("$ftp_host : $ftp_port - 연결에 실패하였습니다.");
    if(!$login_result = ftp_login($conn_id, $ftp_user, $ftp_pass))
        echo"로그인성공";

    if(!$conn_id || !$login_result) echo"hello";

    $dir = ftp_chdir($conn_id, $target_dir);

    echo $files;
    echo "<br>";
    echo "$source_dir";
    echo "$files";
/*    foreach($files){
        echo"들어왔습니다";
        $file = trim($file);
        $d =  explode('/',$file);

        if(count($d)>1){
            echo"파일전송 성공1";
            $dir_sub = "";

            for($i=0;$i<count($d)-1;$i++){

                if($dir_sub){ $dir_sub .= "/".$d[$i]; }
                else{ $dir_sub = $d[$i]; }

                @ftp_mkdir($conn_id, $dir_sub);
            }
        }
*/
        if(!$up = ftp_put($conn_id, $files, $source_dir."/".$files, FTP_BINARY))
            echo "파일 전송에 실패했습니다.";
        //echo "$up = $source_dir/$file -> $target_dir/$file<br>\n";

        //if($up){ $result++; }

    ftp_close($conn_id);


}
?>