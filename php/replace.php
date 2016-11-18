<?php
$str1 = "http://10.27.159.204:8888/f5f6e3557d16693e6/test.m3u8";
$str2 = 'ott.jsocn.com:8888';
$parameter = explode('/', $str1);
$parameter[2];
echo str_replace($parameter[2],$str2,$str1)."\n";

