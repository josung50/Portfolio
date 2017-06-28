<?php
session_start();

unset($_SESSION["id"]);
die("<script>location.href='main.php';</script>");
?>