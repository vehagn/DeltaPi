<!DOCTYPE html>
<html>
<head>
	<meta http-equiv="Content-Type"
	content="text/html;charset=UTF-8">
	<title>EpsilonPi</title>
	<style>
	body {background-color:#0C371D}
	h1 {font-family:"Lucida Console";
		text-decoration:underline;}
	div {text-align:center;
		border:10px;
		margin-right:40%;
		margin-left:40%;
		margin-top:5%;
		width:300px;
		background-color:white;
		font-family:"Courier";}
	a {color:#00703C;}
	open {color:#00CC00;}
	closed {color:#CC0000;}
	</style>
</head>
<body>
	<div>
	<br>
	<h1>EpsilonPi</h1>
	<?php
	$fh = fopen('office.txt','r');
	$line = fgets($fh);

	if ($line == 'on'){
		echo '<p>Office:<br><open>Open</open></p>';
	}
	else{
		echo '<p>Office:<br><closed>Closed</closed></p>';
	}
	fclose($fh);
	?>

	<?php
	$fh = fopen('coffee.txt','r');
	$line = fgets($fh);
	$line = fgets($fh);
	echo '<p>Last coffee: <br>' . $line . '</p>';
	?>
	<h2>
	<a href="http://deltahouse.no">
	<img src="Coffee.svg" alt="Coffee time!"></a>
	<?php
	echo 'Week: ' . date("W") . '';
	?></h2>
	<p><a href="card.php">Find RFID tag</a></p>
	<p>
	<a href="office.txt">office.txt</a>
	<a href="coffee.txt">coffee.txt</a>
	<a href="coffee_log.txt">coffee_log.txt</a>
	</p>
	<p><a href="http://deltahouse.no/docs/">misc documents</a></p>
	<p>&pi; = 4&sdot;atan(1)</p>
	<p><a href="/PiTemp">Temperature log</a></p>
	<br>
	</div>
</body>
</html>
