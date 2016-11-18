<?php
ini_set('default_socket_timeout', 3);  /*超时控制（3秒）*/
$url = 'www.baidu.com';
if($data = file_get_contents($url)) {
	echo 'Pass';
}else {
	echo 'Timeout';
} 
