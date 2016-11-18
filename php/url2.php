<?php  

$handle = @fopen("user.txt", "r");
while (!feof($handle)) {
	$line = fgets($handle, 4096);
	$parameter = explode('$', $line); //字符串分割
	$url = "http://ott.jsocn.com:8035/play/?vsea_action=newhls&vsea_m=iOS&vsea_r=".$parameter[0]."&vsea_u=".$parameter[3]."&vsea_p=".$parameter[4];
	$parameter = explode('|', $url);
	$url = $parameter[0];
	echo $url."\n";
	$html = file_get_contents($url);  
	//print_r($http_response_header[6]);
	$str = substr($http_response_header[6],10);
	echo $str."\n";
}
echo "-----------------------------------------------";
fclose($handle);
?>  		  
