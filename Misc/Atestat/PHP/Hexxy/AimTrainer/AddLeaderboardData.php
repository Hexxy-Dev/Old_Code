<?php
require '../commons.php';

$conection = mysql_connect($serverAddress,$user,$password);
$db = mysql_select_db($databaseName);

$result = mysql_query(
    "INSERT INTO ".$aimTrainer['tableName']." (".$aimTrainer['name'].", ".$aimTrainer['score'].") VALUES
        ('".$_POST['Name']."',".$_POST['Score'].");
    "
);

?>