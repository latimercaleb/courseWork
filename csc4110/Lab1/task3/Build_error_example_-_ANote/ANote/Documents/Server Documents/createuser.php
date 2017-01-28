<?php
// Save the notes in the database

// Variable init
	include ("init.php");

// Connect to the database	
	include ("connect.php");

function get_string($h, $s, $e)
{
// Check that the start tag is NOT the same as the end tag
if ($s == $e)
   return "";

// Check that the start tag exists
if (strpos ($h, $s, 0) === false)
   return "";

// Check that the end tag exists
if (strpos ($h, $e, 0) === false)
   return "";

$sp = strpos($h, $s, 0) + strlen($s);  
$ep = strpos($h, $e, 0); 

// Check that the start tag comes before the end tag
if ($sp >= $ep)
   return "";

return substr($h, $sp, $ep-$sp);
}

// Get the xml
$data = $HTTP_RAW_POST_DATA;

// Find the user information
	$start = '<UserInformation>';
	$end = '</UserInformation>';
	$found = get_string($data, $start, $end);

// Get the data
	$username		= get_string ($data, "<username>", "</username>");
	$password		= get_string ($data, "<password>", "</password>");
	$email			= get_string ($data, "<email>", "</email>");	
	
// See if the user already exists
	$query="SELECT * FROM users WHERE user='$username'";
	$reply = mysql_query ($query);
	$num_result = mysql_num_rows ($reply);
	if ($num_result != 0)	{
		if (mysql_result ($reply, 0, "password") != $password)	{
			echo $xmlstart ."<info info=\"username exists but wrong password\"/>";
			exit;
		}
		else	{
		// Update the user
			$query ="UPDATE `users` SET `email` = '$email' WHERE user = '$username'";
			mysql_query ($query);

			echo $xmlstart ."<info info=\"Creation of new user was successfull\"/>";
			exit;
		}
	}

// Create the user

	$query = 'INSERT INTO `users` ( `id` , `user` , `password` , `email` , `numlogs` ) ';
	$query .= 'VALUES ( \'\', \''.$username .'\', \'' .$password .'\', \''.$email .'\', \'0\' );';
	$query .= ''; 
	$reply = mysql_query ($query);
	
// Something went wrong
	if ($reply === 0)	{
		echo $xmlstart ."<info info=\"The user could not be created\"/>";
		exit;
	}

// Everytning is ok
echo $xmlstart ."<info info=\"Creation of new user was successfull\"/>";
?>
