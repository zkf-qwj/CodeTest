<?php
$str = 'http://192.168.1.121:80/762315f2b6f1b8aec/test.m3u8';
$file = substr($str,-27,-10);
if(file_exists($file))
{
	    echo "当前目录中，文件".$file."存在";
		    echo "
				";
}
else
{
	echo "当前目录中，文件".$file."不存在创建";
	$structure = './'.$file;
	if (!mkdir($structure, 0777, true)) {
		   echo  'Failed to create folders...';
	}
}
