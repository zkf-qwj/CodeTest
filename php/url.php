<?php  
$url='http://ott.jsocn.com:8035/play/?vsea_action=newhls&vsea_r=rtsp://172.100.226.214&vsea_u=admin&vsea_p=admin&vsea_stb=0&vsea_m=nobox';  
$html = file_get_contents($url);  
echo $html;  
?>  
