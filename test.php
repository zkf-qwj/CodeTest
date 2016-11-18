<?php

function inquire($dbhost = '192.168.2.126:3306',$dbuser = 'root',$dbpass = '@vsea.tv'){
	$dbhost = '192.168.2.126:3306';  //mysql服务器主机地址
	$dbuser = 'root';      //mysql用户名
	$dbpass = '@vsea.tv';//mysql用户名密码
	$conn = mysql_connect($dbhost, $dbuser, $dbpass);
	if(! $conn )
	{
		die('Could not connect: ' . mysql_error());
	}
	echo 'Connected successfully\n';
	$sql = 'SELECT reg_user FROM registrations';


	mysql_select_db('freeswitch',$conn); //进入数据库

	$retval = mysql_query( $sql, $conn ); //在表里面查询数据

	$cars=array("Volvo","BMW","SAAB");
	$i = 0;
	while($row = mysql_fetch_array($retval, MYSQL_ASSOC))
	{
		$cars[$i++] = $row['reg_user'];	//将数据保存到数组里面
	}
	echo "---------------------------------------------";
	print_r($cars);

	mysql_close($conn);

	return $cars;
}
//inquire('192.168.2.126:3306','root','@vsea.tv');

?>
