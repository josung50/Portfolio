<?php
/**
 * Created by PhpStorm.
 * User: choi
 * Date: 2017-05-22
 * Time: 오후 8:19
 */
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

$_SEARCH_TEXT = urldecode($_POST["SEARCH_TEXT"]);
$_LOGIN_MEMBER_SEQ = urldecode($_POST["MEMBER_SEQ"]);

$_TAG_COUNT = substr_count($_SEARCH_TEXT, "#");
$_TAGS = explode("#", $_SEARCH_TEXT);
if($_SEARCH_TEXT) {
    if ($_TAG_COUNT == 0) {
        $search_word_query = mysqli_query($link, "select * from t_design_work tableWithLikeCnt
	    where tableWithLikeCnt.title LIKE \"%$_SEARCH_TEXT%\" or tableWithLikeCnt.contents LIKE \"%$_SEARCH_TEXT%\"");
        while ($search_word_row = mysqli_fetch_array($search_word_query)) {
            echo "<br>";
            $_LIKE_CHECK = "UNCHECKED";
            echo "$search_word_row[seq]#";
            echo "$search_word_row[member_seq]#";
            echo "$search_word_row[thumb_uri]#";
            $like_query = mysqli_query($link, "select * from t_design_work_like where t_design_work_like.design_work_seq = $search_word_row[seq]");
            while($like_judge_row = mysqli_fetch_array($like_query)){
                if($like_judge_row[member_seq] == $_LOGIN_MEMBER_SEQ){
                    $_LIKE_CHECK = "CHECKED";
                }
            }
            echo "\($_LIKE_CHECK\)";
        }
    } else {
        for ($i = 1; $i <= $_TAG_COUNT; $i++) {
            $tag_search_query = mysqli_query($link, "select * from t_design_work tableWithLikeCnt
	        where tableWithLikeCnt.tags LIKE \"%$_TAGS[$i]%\"");
            while ($tag_search_row = mysqli_fetch_array($tag_search_query)) {
                $_LIKE_CHECK = "UNCHECKED";
                echo "<br>";
                echo "$tag_search_row[seq]#";
                echo "$tag_search_row[member_seq]#";
                echo "$tag_search_row[thumb_uri]#";
                $like_query = mysqli_query($link, "select * from t_design_work_like where t_design_work_like.design_work_seq = $tag_search_row[seq]");
                while ($like_judge_row = mysqli_fetch_array($like_query)) {
                    if ($like_judge_row[member_seq] == $_LOGIN_MEMBER_SEQ) {
                        $_LIKE_CHECK = "CHECKED";
                    }
                }
                echo "\($_LIKE_CHECK\)";
            }
        }
    }
}
?>
