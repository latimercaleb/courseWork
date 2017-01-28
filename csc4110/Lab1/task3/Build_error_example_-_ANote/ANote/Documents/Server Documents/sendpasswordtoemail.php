<?php
// Send an email with the password to the user

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
	$start = '<SendEmail>';
	$end = '</SendEmail>';
	$found = get_string($data, $start, $end);

// Get the data
	$username		= get_string ($data, "<username>", "</username>");
	$query="SELECT * FROM users WHERE user='$username'";
	$reply = mysql_query ($query);
	$num_result = mysql_num_rows ($reply);
	if ($num_result != 0)	{
		$password 	= base64_decode (mysql_result ($reply, 0, "password"));
		$email 		= base64_decode (mysql_result ($reply, 0, "email"));
	}
// Email the password
	$subject = "Password to A Note";
	$body = "This message has been automatically sent from A Note's server.
	You can not reply to this message.\n\nThe user's information is:\nUser name: ".base64_decode ($username) ."\nPassword: " .$password ."\n
	Start A Note and go to Options -> Database and fill in the information there.\n\nIf you have any questions, go to A Note's
	webpage http://sourceforge.net/projects/a-note/\n\n\nThe A Note staff...";
	mail($email, $subject, $body);

// Everytning is ok
	echo $xmlstart ."<info info=\"password has been emailed\"/>";
?>