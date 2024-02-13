<?php

$databaseName = "HexxyDB";
$tableName = "HMM";
$columnName1 = "NOOM";

//really unsafe to store the password in the code
$conection = mysql_connect("localhost","root","");// REDACTED

$database = mysql_select_db($databaseName);

$v1 = $_POST["t1"];
$request1 = "INSERT INTO $tableName($columnName1) VALUES('$v1')";
$result1 = mysql_query($request1);

$request2 = "SELECT * FROM $tableName";
$result2 = mysql_query($request2);

echo "<table>";
while($line = mysql_fetch_array($result2)){
    echo "<tr><td>";
    echo $line[$columnName1];
    echo "</td></tr>";
}
echo "</table>";
?>