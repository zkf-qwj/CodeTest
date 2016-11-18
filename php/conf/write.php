<?php
$fp = fopen("test", "wb");
// Assign a binary byte to a variable
$i = 2016;
$data = "abcdefg";
$len = strlen($data);
$header = pack("I*",$len);
echo strlen($header);
echo "---------------".$header.$data;
	// Write the byte to the file
	fwrite($fp, $header.$data);

fclose($fp);
?>
