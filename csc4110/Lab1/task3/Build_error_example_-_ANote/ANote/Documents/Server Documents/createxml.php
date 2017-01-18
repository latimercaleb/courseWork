<?php
// Find every note and create the xml
	$query="SELECT * FROM note WHERE userid='$userid'";
	$reply = mysql_query ($query);
	$num_result = mysql_num_rows ($reply);
	
// Did we find a user
	if ($num_result == 0)	{
		echo $xmlstart ."<info info=\"no notes\"/>";
		exit;
	}

// Create the xml header
	echo $xmlstart ."<notes>";

// Add the notes to the xml
	for ($i = 0; $i < $num_result; $i++)	{
		echo "<note";	
	// Data
		echo " noteversion=\"" .mysql_result ($reply, $i, "noteversion") ."\"";	
		echo " noteid=\"" .mysql_result ($reply, $i, "noteid") ."\"";
		echo " alarmtime=\"" .mysql_result ($reply, $i, "alarmtime") ."\"";
		echo " usealarm=\"" .mysql_result ($reply, $i, "usealarm") ."\"";
		echo " title=\"" .mysql_result ($reply, $i, "title") ."\"";
		echo " visible=\"" .mysql_result ($reply, $i, "visible") ."\"";
		echo " notecolor=\"" .mysql_result ($reply, $i, "notecolor") ."\"";						
		echo " positionleft=\"" .mysql_result ($reply, $i, "positionleft") ."\"";		
		echo " positiontop=\"" .mysql_result ($reply, $i, "positiontop") ."\"";		
		echo " width=\"" .mysql_result ($reply, $i, "width") ."\"";		
		echo " height=\"" .mysql_result ($reply, $i, "height") ."\"";		
		echo " dockedleft=\"" .mysql_result ($reply, $i, "dockedleft") ."\"";										
		echo " dockedtop=\"" .mysql_result ($reply, $i, "dockedtop") ."\"";										
		echo " dockedright=\"" .mysql_result ($reply, $i, "dockedright") ."\"";										
		echo " dockedbottom=\"" .mysql_result ($reply, $i, "dockedbottom") ."\"";										

		echo " slided-left=\"" .mysql_result ($reply, $i, "slided-left") ."\"";										
		echo " slided-right=\"" .mysql_result ($reply, $i, "slided-right") ."\"";										
		echo " slidepositionleft=\"" .mysql_result ($reply, $i, "slidepositionleft") ."\"";										
		echo " slidepositiontop=\"" .mysql_result ($reply, $i, "slidepositiontop") ."\"";										
		echo " slidepositionright=\"" .mysql_result ($reply, $i, "slidepositionright") ."\"";										
		echo " slidepositionbottom=\"" .mysql_result ($reply, $i, "slidepositionbottom") ."\">";										

		echo " <text>" .mysql_result ($reply, $i, "text") ."</text>";

		echo "</note>";
	}

// Add the end tag
echo "</notes>";
	
?>

