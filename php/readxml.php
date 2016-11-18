<?php 
//$file_r = $_GET['vsea_file'];
$doc = new DOMDocument(); 
$doc->load("20161023-1001-220123.xml"); //读取xml文件 
$root=$doc->documentElement;
$ChannelInfo = array(
	'ProviderId' => 0,
	'ProviderName' => 0,
	'ChannelId' => 0,
	'duration' => array(),
	'beginTime' => array(),
	'EventId' => array(),
	'Name' => array(),
	'ShortDescription' => array(),
	'Description' => array(),
);
$ProviderInfos = $doc->getElementsByTagName( "ProviderInfo" );
foreach( $ProviderInfos as $ProviderInfoElem ) 
{
	$ProviderIds = $ProviderInfoElem->getElementsByTagName( "ProviderId" );
	$ProviderNames = $ProviderInfoElem->getElementsByTagName( "ProviderName" );
	$providerid = $ProviderIds->item(0)->nodeValue;
	$providername = $ProviderNames->item(0)->nodeValue;
	$ChannelInfo['ProviderId'] = $providerid;
	$ChannelInfo['ProviderName'] = $providername;
}

$i = 0;
foreach($doc->getElementsByTagName( "ChannelId" ) as $list)
{ 
	$channelid = $list->firstChild->nodeValue;
	$ChannelInfo['ChannelId'] = $channelid;
	$i++;
}
$i = 0;
foreach($doc->getElementsByTagName("Event") as $list)
{
	$duration = $list->getAttribute("duration")."\n";
	$beginTime = $list->getAttribute("beginTime")."\n";
	$ChannelInfo['duration'][$i] = $duration;
	$ChannelInfo['beginTime'][$i] = $beginTime;
	$i++;
}

$i = 0;
foreach($doc->getElementsByTagName('EventId') as $list)
{	
	$eventid = $list->firstChild->nodeValue; 
	$ChannelInfo['EventId'][$i] = $eventid;
	$i++;
}
$i = 0;
foreach($doc->getElementsByTagName( "Name" ) as $list)
{	
	$name =  $list->firstChild->nodeValue; 
	$ChannelInfo['Name'][$i] = $eventid;
	$i++;
}
$i = 0;
foreach($doc->getElementsByTagName( "ShortDescription" ) as $list)
{
	$shortdescription = $list->firstChild->nodeValue; 
	$ChannelInfo['ShortDescription'][$i] = $eventid;
	$i++;
}
$i = 0;
foreach($doc->getElementsByTagName( "Description" ) as $list)
{
	$description = $list->firstChild->nodeValue; 
	$ChannelInfo['Description'][$i] = $eventid;
	$i++;
}

$arr = array ('ProviderId'=>3,'ProviderName'=>2,'ChannelId'=>3,'duration'=>4,'beginTime'=>5,'EventId'=>3, 'Name' =>3, 'ShortDescription' =>3, 'Description'=>3);
echo json_encode($arr);
?>
