<?php  
$url='http://www.bauidu.com/';
$fp = fopen($url, 'r');  
//返回请求流信息（数组：请求状态，阻塞，返回值是否为空，返回值http头等）  

//[php] view plain copy print?
stream_get_meta_data($fp);  
//[php] view plain copy print?
while(!feof($fp)) {  
$result .= fgets($fp, 1024);  
}  
echo "url body: $result";  
fclose($fp);  
?>  
