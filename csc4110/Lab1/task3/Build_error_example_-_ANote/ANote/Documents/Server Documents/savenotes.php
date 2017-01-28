<?php
// Save the notes in the database

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

// Erase every note
$query = "DELETE FROM note WHERE userid=$userid";
$reply = mysql_query ($query);
if ($reply === 0)	{
	echo $xmlstart ."<info info=\"The notes couldn't be deleted\"/>";
	exit;
}
// Get the xml
$data = $HTTP_RAW_POST_DATA;


// Find the note and save it
while ($data != "")	{
	$start = '<note>';
	$end = '</note>';
	$found = get_string($data, $start, $end);

	if ($found === "")
		break;
		
// Get the data
	$noteversion	= get_string ($found, "<noteversion>", "</noteversion>");
	$noteid			= get_string ($found, "<noteid>", "</noteid>");
	$alarmtime		= get_string ($found, "<alarmtime>", "</alarmtime>");	
	$usealarm		= get_string ($found, "<usealarm>", "</usealarm>");	
	$title			= get_string ($found, "<title>", "</title>");	
	$visible		= get_string ($found, "<visible>", "</visible>");	
	$notecolor		= get_string ($found, "<notecolor>", "</notecolor>");	
	$positionleft	= get_string ($found, "<positionleft>", "</positionleft>");	
	$positiontop	= get_string ($found, "<positiontop>", "</positiontop>");
	$width			= get_string ($found, "<width>", "</width>");
	$height			= get_string ($found, "<height>", "</height>");
	$text			= get_string ($found, "<text>", "</text>");
	$dockedleft		= get_string ($found, "<dockedleft>", "</dockedleft>");	
	$dockedtop		= get_string ($found, "<dockedtop>", "</dockedtop>");	
	$dockedright	= get_string ($found, "<dockedright>", "</dockedright>");	
	$dockedbottom	= get_string ($found, "<dockedbottom>", "</dockedbottom>");				

	$slidedleft		= get_string ($found, "<slided-left>", "</slided-left>");				
	$slidedright	= get_string ($found, "<slided-right>", "</slided-right>");				
	$slidepositionleft = get_string ($found, "<slidepositionleft>", "</slidepositionleft>");				
	$slidepositiontop	 = get_string ($found, "<slidepositiontop>", "</slidepositiontop>");				
	$slidepositionright = get_string ($found, "<slidepositionright>", "</slidepositionright>");				
	$slidepositionbottom = get_string ($found, "<slidepositionbottom>", "</slidepositionbottom>");				
 					   
// Save the note
	$query = "INSERT INTO note values (		\"$userid\", 
											\"$noteid\", 
											\"$noteversion\", 
											\"$text\",
											\"$alarmtime\",
											\"$usealarm\",
											\"$title\",
											\"$visible\",
											\"$notecolor\",
											\"$positionleft\",
											\"$positiontop\",
											\"$width\",
											\"$height\",
											\"$dockedleft\",
											\"$dockedtop\",
											\"$dockedright\",
											\"$dockedbottom\",
											\"$slidedleft\",
											\"$slidedright\",
											\"$slidepositionleft\",
											\"$slidepositiontop\",
											\"$slidepositionright\",
											\"$slidepositionbottom \"	
											)";
	$reply = mysql_query ($query);

// Something went wrong
	if ($reply === 0)	{
		echo $xmlstart ."<info info=\"The note couldn't be inserted\"/>";
		exit;
	}

// Jump over one <note>...</note>
	$a = strpos ($data, $end) + strlen ($end);
	$data = substr ($data, $a);
}

// Everytning is ok
echo $xmlstart ."<info info=\"The notes was uploaded\"/>";

?>
