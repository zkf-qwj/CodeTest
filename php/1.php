<?php

$arr = array ('a'=>"你好",'b'=>2,'c'=>3,'d'=>4,'e'=>5);
$json_string = json_encode($arr);
$obj=json_decode($json_string); 
echo $obj->a;
