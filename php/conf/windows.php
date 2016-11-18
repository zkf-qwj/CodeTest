<?php
$port = 3000;
$ip = "192.168.1.159";
$socket = socket_create(AF_INET, SOCK_STREAM, SOL_TCP);
if ($socket < 0) {
	echo "socket_create() failed: reason: " . socket_strerror($socket) . "\n";
}else {
	echo "OK.\n";
}   
echo "试图连接 '$ip' 端口 '$port'...\n";
$result = socket_connect($socket, $ip, $port);
if ($result < 0) {
	echo "socket_connect() failed.\nReason: ($result) " . socket_strerror($result) . "\n";
}else {
	echo "连接OK\n";
}   
$arr = Array('flag'=>'windows', 'channelid'=>'zhanglianjie');

$send_string = str_replace("\\/", "/",  json_encode($arr));
$len = strlen($send_string);
$header = pack("I*",$len);    
if(!socket_write($socket, $header.$send_string, strlen($header.$send_string))) {
	//if (!fwrite($socket, $header.$send_string)){
	echo "socket_write() failed: reason: 
		".socket_strerror($socket)."\n";                                                                                                                                
	exit;
}
$byte = socket_recv($socket,$recv_url,8192,0);
echo $send_string;
echo "-----recv:".$recv_url;
