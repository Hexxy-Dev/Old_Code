<?php
require '../commons.php';

$conection = mysql_connect($serverAddress,$user,$password);
$db = mysql_select_db($databaseName);

$response = mysql_query(
    'CREATE TABLE tableName (columnName1 TEXT);'
);
$response = mysql_query(
    'CREATE TABLE HMM (NOOM TEXT);'
);

?>