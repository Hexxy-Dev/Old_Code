<?php
require './commons.php';

$conection = mysql_connect($serverAddress,$user,$password);
$response = mysql_query("DROP DATABASE $databaseName;");

?>