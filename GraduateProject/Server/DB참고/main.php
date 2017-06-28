<?php
include_once "head.php";
?>
<body>

<p>THIS IS MAIN</p>

<?php session_start();
if($_SESSION["id"]) {?>
    <?php include_once "header.php";
    ?>
    <a href="#"><?= $_SESSION["id"] ?>님 환영합니다. <span class="glyphicon glyphicon-log-out" onclick="location.href='logout.php'" ></span></a>
<?php } else {?>
    <form method="post" onsubmit="return login();">
        <div class="form-group">
            <label for="id">id:</label>
            <input type="id" name="loginid" id="id" class="form-control">
        </div>
        <div class="form-group">
            <label for="pwd">Password:</label>
            <input type="password" name="loginpwd" id="pwd" class="form-control">
        </div>
        <div class="checkbox">
            <label><input type="checkbox"> Remember me</label>
        </div>
        <button type="submit" class="btn btn-default">Submit</button>
    </form>
<?php }?>





</body>
</html>
