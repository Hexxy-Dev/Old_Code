<?php
require '../commons.php';

$conection = mysql_connect($serverAddress,$user,$password);
$db = mysql_select_db($databaseName);


$response = mysql_query(
    "CREATE TABLE ".$aimTrainer['tableName']." (
        id INT UNSIGNED NOT NULL AUTO_INCREMENT PRIMARY KEY,
        ".$aimTrainer['name']." VARCHAR(5),
        ".$aimTrainer['score']." INT UNSIGNED
    );"
);

$response = mysql_query(
    "INSERT INTO ".$aimTrainer['tableName']." (".$aimTrainer['name'].", ".$aimTrainer['score'].") VALUES
        ('Cutie', ".rand(23404,638056459)."),
        ('Radar', ".rand(23404,638056459)."),
        ('Haneu', ".rand(23404,638056459).");
    "
);

?>