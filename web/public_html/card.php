<!DOCTYPE html>
<html>
<head>
	<meta http-equiv="Content-Type"
	content="text/html;charset=UTF-8">
	<title>Find RFID tag</title>
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
	<h1>Find RFID tag</h1>
	<form action="card.php" method="get"><p>
	Card ID<br>(lower left corner)<br>
	<input type="number" name="n" min="0" max="4294967295" step="1" value="<?=$_GET["n"]?>">
	<input type="submit"><br>
	<input type="checkbox" name="magic" <?php if (isset($_GET["magic"])){echo checked;} ?>>Show me the magic
	</p></form>
	<p><?php 
		if (isset($_GET["n"])){
			$b = sprintf('%032b',(int)$_GET["n"]);
			$bflip = strrev(substr($b,0,8)).strrev(substr($b,8,8)).strrev(substr($b,16,8)).strrev(substr($b,24,8));
			if (isset($_GET["magic"])){
				echo 'Get number as int32<br>';
				echo (int)$_GET["n"];
				echo '<br>Convert to binary<br>';
				echo substr($b,0,8).' '.substr($b,8,8).' '.substr($b,16,8).' '.substr($b,24,8);
				echo '<br>Reverse every 8-bit word<br>';
				echo substr($bflip,0,8).' '.substr($bflip,8,8).' '.substr($bflip,16,8).' '.substr($bflip,24,8);
				echo '<br>Convert back to int32<br>';
				echo bindec($bflip);
			}else{
				echo 'Your RFID tag is<br>';
				echo bindec($bflip);
			}
		}
	?></p>
	<p>Protip:<br> Also works in reverse!</p>
	<p>
	<a href="http://deltahouse.no">Deltahouse.no</a>
	<a href="index.php">EpsilonPi</a>
	</p>
	<br>
	</div>
</body>
</html>
