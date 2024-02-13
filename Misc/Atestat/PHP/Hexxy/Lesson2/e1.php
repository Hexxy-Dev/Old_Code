<?php
$v1 = $_POST["t1"];
echo $v1;

//really unsafe to store the password in the code
$conection = mysql_connect("localhost","root","");// REDACTED

$database = mysql_select_db("HexxyDB");

$tableName = "tableName";
$columnName1 = "columnName1";

$request1 = "INSERT INTO $tableName($columnName1) VALUES($v1);";
$result1 = mysql_query($request1);
echo $result1;

$request2 = "SELECT * FROM $tableName;";
$result2 = mysql_query($request2);
echo $result2;
?>