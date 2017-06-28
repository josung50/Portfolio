<?php
//ini_set('display_errors', '1');
//메일러 로딩
require_once("./mail/class.phpmailer.php");
require_once("./mail/class.smtp.php");
//require_once("./mail/PHPMailerAutoload.php");

$user_id = $_POST['user_id'];
$user_pw = $_POST['user_pw'];
$user_email = $_POST['user_email'];
$user_nick = $_POST['user_nick'];
$token = $_POST['token'];
$user_toekn = hash('sha256',$user_email);

if($token=="gossip") {
    $link = mysqli_connect("localhost", "root", "double989", "gossip");
    mysqli_query($link, " SET NAMES UTF8");
    // check connection
    if (!$link) {
        printf("Connect failed: %s\n", mysqli_connect_error());
        exit();
    }
    // set autocommit to off
    mysqli_autocommit($link, FALSE);
//mysqli_query($link, "CREATE TABLE Language LIKE CountryLanguage");
    // Insert some values
    mysqli_query($link, "INSERT INTO user_table(u_id,u_pw,u_email,u_nick,u_token) VALUES ('{$user_id}','{$user_pw}','{$user_email}','{$user_nick}','{$user_toekn}')");
    // commit transaction
    if (!mysqli_commit($link)) {
        print("Transaction commit failed\n");
        exit();
    }
    // close connection
    mysqli_close($link);
    //메일로 인증.
    $hash = hash('sha256',$user_email);
    $mail = new PHPMailer(); // create a new object
    $mail->IsSMTP(); // enable SMTP
    $mail -> CharSet = "UTF-8";
//$mail->SMTPDebug = 1; // debugging: 1 = errors and messages, 2 = messages only
    $mail->SMTPAuth = true; // authentication enabled
    $mail->SMTPSecure = 'ssl'; // secure transfer enabled REQUIRED for Gmail
    $mail->Host = "smtp.gmail.com";
    $mail->Port = 465; // or 587
    $mail->IsHTML(true);
    $mail->Username = "kookminapp@gmail.com";
    $mail->Password = "1q2w3e!@";
    $mail->SetFrom("kookminapp@gmail.com","kookminGossip");
    $mail->Subject = "국민가십 인증 메일입니다.";
    $mail->Body = "<html>
    <p>국민대 학생 인증을 위해 아래 링크를 클릭해주세요.</p>
    <a href='http://52.9.33.19/KHJ/userCheck.php?u=$hash&k=$user_id&l=OK'>Click</a>
    </html>";
    $mail->AddAddress("$user_email@kookmin.ac.kr");
    if(!$mail->Send()) {
        //echo "Mailer Error: " . $mail->ErrorInfo
        echo "FAIL";
    } else {
        //echo "Message has been sent";
        echo "SUCCESS";
    }

}else{
    echo "Sorry you got the wrong path";
}


?>
