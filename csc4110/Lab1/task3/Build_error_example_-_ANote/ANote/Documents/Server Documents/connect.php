<?php
// Connect to the database
	mysql_connect("mysql.sourceforge.net",$dbusername,$dbpassword);
	@mysql_select_db($database) or die( "Unable to select database");
?>