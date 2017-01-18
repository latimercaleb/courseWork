<?php
// See if the user exists and that the password is right
	$query="SELECT * FROM users WHERE user='$user'";
	$reply = mysql_query ($query);
	$num_result = mysql_num_rows ($reply);

// Did we find a user
	if ($num_result == 0)	{
		echo $xmlstart ."<info info=\"no user\"/>";
		exit;
	}

// Check if the user and password is valid
	$pass = mysql_result ($reply, 0, "password");
	$userid = mysql_result ($reply, 0, "id");

	if ($pass != $password)	{
		echo $xmlstart ."<info info=\"username exists but wrong password\"/>";
	   	exit;
	}
?>