
<?php
$arr = Array('a'=>'http://abc', 'b'=>'two', 'c'=>'three');
//$b = json_encode($arr);
echo str_replace("\\/", "/",  json_encode($arr));
echo "-------------------";
echo json_encode($arr);
