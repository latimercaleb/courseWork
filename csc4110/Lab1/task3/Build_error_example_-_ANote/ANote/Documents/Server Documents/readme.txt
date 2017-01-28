FILE				DESCRIPTION
-------------------------------------------
connect.php			Connects to the database (used in several files)
createuser.php			Create one user and checks if it's already such a user
createxml.php			Find the notes that belongs to the user and create an xml that will be sent to the program
getnotes.php			The user wants to get his/hers notes and they will be sent (if the user exists)
getversion.php			Get the latest version of A Note and the changelog text
init.php			Initialize some variables (used in several files)
savenotes.php			Save the uploaded notes in the database
sendnotes.php			The user upload some notes and they will be saved if the user exists
sendpasswordtoemail.php		Send the password to the user that has forgotten it
validateuser.php		Check if the user exists (used in several files)


NOTE: You'll have to make a database and some tables with that (see create database.txt for information)