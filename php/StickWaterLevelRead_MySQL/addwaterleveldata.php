<?php
   	include("db_connection.php");
   	$link=Connection();
	$Sql="INSERT INTO stickwaterleveldata (temp1,photo1,DeviceType) VALUES ('".$_GET["waterlevel"]."', '".$_GET["water_present"]."', '".$_GET["DeviceType"]."')";     

	if (!mysqli_query($link, $Sql)) {
    	echo "Error: " . $Sql . "<br>" . mysqli_error($link);
	}

   	header("Location: displaywaterleveldata.php");
?>