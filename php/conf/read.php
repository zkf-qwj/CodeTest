<?php
$fp = fopen("test","rb");
	// Read the file, in chunks of 16 byte
	$data = fread($fp,4);
	$arr = unpack("I*",$data);
	foreach ($arr as $key => $value) {
		echo " " . $value;
	}
	$data = fread($fp,$value);
	echo "recv: ".$data;
	echo "\n";
?>
