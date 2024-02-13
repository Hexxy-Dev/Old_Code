<?php
require './commons.php';

$conection = mysql_connect($serverAddress,$user,$password);

$response = mysql_query("CREATE DATABASE $databaseName;");
$db = mysql_select_db($databaseName);

$files = scandir('./');
foreach($files as $file) {
    if(is_dir($file) && !in_array($file,array('.','..'))) {
        exec("curl http://localhost/Hexxy/$file/Init.php");
    }
}

?>