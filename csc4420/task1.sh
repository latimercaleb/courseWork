#!/bin/bash

#shebang above for bourne shell execution
#Initial prompt to test validity of script  
echo "Hello this is task 1 of the homework"

#shopt allows configuration of the shell -s dotglob allows the script to run on dot-files
shopt -s dotglob

#loop to iterate through each file in Task1 directory and rename them

#loop runs if there is a file type of ".PDF" in the folder Task1, if there isn't displays that there isn't a file of that type and terminates

#loop uses 3 variables ran to dictate the final echo prompt i to count the number of times the loop executed and j to determine if the loop ran to completion or not 

#if is used here to determine the value of ran 
 
ran=false
i=0
j=2
for file in Task1/*.PDF;
	do
		let "i += 1" 
		mv "$file" "${file%.PDF}.pdf"
		echo "$file has been updated"


		if [ "$i" -ge "$j" ] 
		then
			ran=true
		fi
	done
if [ "$ran" = false ] 
	then
		echo "Files do not exist"
	fi
#bash script by Caleb Latimer ej1297 
