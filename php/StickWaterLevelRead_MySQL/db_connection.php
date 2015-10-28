<?php
function Connection(){
	if (!($link=mysqli_connect("localhost","iotdetro_dbusr","password")))  
	{
		echo "Could not connect to mysqli..." . mysqli_connect_error();
		exit();
	}
	if (!mysqli_select_db($link, "iotdetro_arduino_stick_water_level")){
		echo "Could not connect to mysql db..." . mysqli_error();
		exit();
	}
	return $link;
}
?>
