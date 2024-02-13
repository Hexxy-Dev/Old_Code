<?php
header("Access-Control-Allow-Origin: *");
#header is needed for CORS policy
require '../commons.php';

$conection = mysql_connect($serverAddress,$user,$password);
$db = mysql_select_db($databaseName);

$result = mysql_query(
    "SELECT * FROM ".$aimTrainer['tableName'].";"
);

echo "[";
while ($entry = mysql_fetch_array($result)) {
    echo "{
        \"Name\":\"".$entry[$aimTrainer['name']]."\",
        \"Score\":".$entry[$aimTrainer['score']]."
    },";
}
echo "{}]";

?>