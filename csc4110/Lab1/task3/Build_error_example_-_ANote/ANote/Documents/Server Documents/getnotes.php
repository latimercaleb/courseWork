<?php
// Get the notes that brings to the user


// Variable init
	#include ("init.php");
	$user	  = $_GET['user'];
	$password = $_GET['password'];

	if ($user == "" || password == "")	{
		echo $xmlstart ."<info info=\"no user or password\"/>";
		exit;
	}
	
// Connect to the database	
	include ("connect.php");
		
// Check if the user exists and that the password is right
	include ("validateuser.php");

// Everything is ok -> create the xml
	include ("createxml.php");
	
// Close mysql
	mysql_close();	
?>


