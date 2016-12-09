<?php
$f= fopen("./CameraInfo","r");
$str1 = 'rtsp://124.47.34.50:554/pag://124.47.34.50:7302:001030:0:SUB:TCP?auth=50&pnid=1&cnid=1&streamform=rtp';
$arr;
while (!feof($f))
{
	$line = fgets($f);
	$arr = explode('@', $line);
	if(isset($arr[1])){
		if ($str1 == $arr[1])
			break;
	}
}
echo "http://10.43.116.3:8081/live/".$arr[2]."\n";
fclose($f);
?>
