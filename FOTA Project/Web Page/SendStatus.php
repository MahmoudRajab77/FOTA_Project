<?php

$Status='';
if(isset($_GET['Status'])){

    $Status=$_GET['Status'];
    
    $StatusFile = fopen('uploads/ProgStatus.txt', 'w+');
    fwrite($StatusFile, $Status);
    fclose($StatusFile);

    echo "OK";

}
else{
    echo "ERROR..No Status Received!!";
}


?>