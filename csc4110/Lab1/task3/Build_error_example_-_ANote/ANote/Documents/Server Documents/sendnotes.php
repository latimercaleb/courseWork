<?php
// A Note is sending the notes -> store them in the database

// Variable init
	include ("init.php");
	$user	  = $_GET['user'];
	$password = $_GET['password'];

	if ($user == "" || password == "")	{
		echo $xmlstart ."<info>no user or password</info>";
		exit;
	}

// Connect to the database	
	include ("connect.php");
		
// Check if the user exists and that the password is right
	include ("validateuser.php");

// Everything is ok -> save the notes in the database
	include ("savenotes.php");

// Increase the counter that shows how many uploades the user has done
	$query="SELECT * FROM users WHERE user='$user'";
	$reply = mysql_query ($query);
	$num_result = mysql_num_rows ($reply);

	$count = mysql_result ($reply, 0, "numlogs");
	$count++;
	$query ="UPDATE `users` SET `numlogs` = '$count' WHERE user = '$user'";
	mysql_query ($query);
	
// Close mysql
	mysql_close();	
?>


