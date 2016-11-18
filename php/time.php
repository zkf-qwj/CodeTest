<?php
$startdate=strtotime("2012-01-01 01:00:00");
$enddate=strtotime("2012-01-2 01:00:00");

//echo(strtotime("2015-05-22 15:00:00"));
//$days=round(($enddate-$startdate)/86400);
$days=round(($enddate-$startdate)/1);
echo $days;
?>
