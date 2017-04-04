// Thread written by Caleb Latimer ej1297
#include<iostream> // Basic I/O
#include<string> // Use of string
using namespace std; // ease of implementation
int main (){
	string prompt; // Variable prompt to retain user input
	string display; // Variable for the display
	string history[5]; // array of size 5 to hold the most recent 5 prompts from user
	int historyCount = 0; // counter to track prompt
	int globalPrompt = 0; // counter to track global history
	cout <<  "CSC4420.cpp--prompt%:" << " < " << globalPrompt << " > "; // inital prompt waits for user input
	display = "CSC4420.cpp--prompt%:";
	cin >> prompt; // user enters input
	// Loop begins shell comparing input with each case
	while (true) {
		if (prompt == "url") {
			globalPrompt++;
			cout << "www.cs.wayne.edu/~lihao/Courses/CSC4420/" << endl;
			if(historyCount <= 4){ // if history is in bounds then append so that most recent is at the end
			history[historyCount] = prompt;
			historyCount++;
			}
			else{ // if not, implement by FIFO pop the oldest, shift and append newest to the end
				for (size_t i = 1; i< 5;i++) {
					history[(i-1)] = history[i];
				}
				history[4] = prompt;
			}
			cout <<  display << " < " << globalPrompt << " > ";
			cin >> prompt;
		}
		else if(prompt == "prompt"){
			globalPrompt++;
			cout << "Input a new prompt no spaces are allowed: ";
			cin >> display;
			if(historyCount <= 4){ // if history is in bounds then append so that most recent is at the end
			history[historyCount] = prompt;
			historyCount++;
			}
			else{ // if not, implement by FIFO pop the oldest, shift and append newest to the end
				for (size_t i = 1; i< 5;i++) {
					history[(i-1)] = history[i];
				}
				history[4] = prompt;
			}
			cout <<  display << " < " << globalPrompt << " > ";
			cin >> prompt;
		}
		 else if (prompt == "hour") {
			 globalPrompt++;
			cout << "Monday & Wednesday 10a-11:15a" << endl;
			if(historyCount <= 4){
			history[historyCount] = prompt;
			historyCount++;
			}
			else{
				for (size_t i = 1; i< 5;i++) {
					history[(i-1)] = history[i];
				}
				history[4] = prompt;
			}
			cout <<  display << " < " << globalPrompt << " > ";
			cin >> prompt;
		}
		else if(prompt == "room"){
			globalPrompt++;
			cout << "State hall 0025" << endl;
			if(historyCount <= 4){
			history[historyCount] = prompt;
			historyCount++;
			}
			else{
				for (size_t i = 1; i< 5;i++) {
					history[(i-1)] = history[i];
				}
				history[4] = prompt;
			}
			cout <<  display << " < " << globalPrompt << " > ";
			cin >> prompt;
		}
		else if (prompt == "desp"){
			globalPrompt++;
				cout << "Operating system is an essential software layer to use various computing devices. This course covers the basic components and design principles of modern operating systems, including process and thread, CPU scheduling, memory management, file system and others. This course also provides hand-on programming experiences of using Linux system calls, and design and implementation of a cloud-based file system." << endl;
				if(historyCount <= 4){
				history[historyCount] = prompt;
				historyCount++;
				}
				else{
					for (size_t i = 1; i < 5;i++) {
						history[(i-1)] = history[i];
					}
					history[4] = prompt;
				}
				cout <<  display << " < " << globalPrompt << " > ";
				cin >> prompt;
		}
		else if(prompt == "text"){
			globalPrompt++;
			cout << "Modern Operating Systems, 4/E , 4th Edition, Pearson, 2015." << endl;
			if(historyCount <= 4){
			history[historyCount] = prompt;
			historyCount++;
			}
			else{
				for (size_t i = 1; i< 5;i++) {
					history[(i-1)] = history[i];
				}
				history[4] = prompt;
			}
			cout <<  display << " < " << globalPrompt << " > ";
			cin >> prompt;
		}
		else if(prompt == "ref"){
			globalPrompt++;
			cout << "Operating System Concepts, 8th Edition, Wiley, 2008" << endl;
			cout <<"Understanding the Linux Kernel, , 3rd Edition, O'Reilly Media, 2005"<< endl;
			cout <<"Advanced UNIX Programming , 2nd Edition, Addison-Wesley, 2004"<< endl;
			cout <<"Advanced Programming in the UNIX Environment 1st Edition , Addison-Wesley, 1992 or 3rd edition, 2013"<< endl;
			if(historyCount <= 4){
			history[historyCount] = prompt;
			historyCount++;
			}
			else{
				for (size_t i = 1; i < 5;i++) {
					history[(i-1)] = history[i];
				}
				history[4] = prompt;
			}
			cout <<  display << " < " << globalPrompt << " > ";
			cin >> prompt;
		}
		else if(prompt == "prof"){
			globalPrompt++;
			cout << "Lihao Xu" << endl;
			if(historyCount <= 4){
			history[historyCount] = prompt;
			historyCount++;
			}
			else{
				for (size_t i = 1; i< 5;i++) {
					history[(i-1)] = history[i];
				}
				history[4] = prompt;
			}
			cout <<  display << " < " << globalPrompt << " > ";
			cin >> prompt;
		}
		else if(prompt == "pol"){
			globalPrompt++;
			cout << "Woodward 5057, Room 1401.1" << endl;
			if(historyCount <= 4){
			history[historyCount] = prompt;
			historyCount++;
			}
			else{
				for (size_t i = 1; i< 5;i++) {
					history[(i-1)] = history[i];
				}
				history[4] = prompt;
			}
			cout <<  display << " < " << globalPrompt << " > ";
			cin >> prompt;
		}
		else if(prompt == "poh"){
			globalPrompt++;
			cout << "Office Hours: 1:15pm to 2:15pm, Mon. and Wed" << endl;
			if(historyCount <= 4){
			history[historyCount] = prompt;
			historyCount++;
			}
			else{
				for (size_t i = 1; i< 5;i++) {
					history[(i-1)] = history[i];
				}
				history[4] = prompt;
			}
			cout <<  display << " < " << globalPrompt << " > ";
			cin >> prompt;
		}
		else if(prompt == "pma"){
			globalPrompt++;
			cout << "lihao@wayne.edu" << endl;
			if(historyCount <= 4){
			history[historyCount] = prompt;
			historyCount++;
			}
			else{
				for (size_t i = 1; i< 5;i++) {
					history[(i-1)] = history[i];
				}
				history[4] = prompt;
			}
			cout <<  display << " < " << globalPrompt << " > ";
			cin >> prompt;
		}
		else if(prompt == "ta"){
			globalPrompt++;
			cout << "David Warnke" << endl;
			if(historyCount <= 4){
			history[historyCount] = prompt;
			historyCount++;
			}
			else{
				for (size_t i = 1; i<5;i++) {
					history[(i-1)] = history[i];
				}
				history[4] = prompt;
			}
			cout <<  display << " < " << globalPrompt << " > ";
			cin >> prompt;
		}
		else if(prompt == "tol"){
			globalPrompt++;
			cout << "Office: Science and Engineering Library Room 0073" << endl;
			if(historyCount <= 4){
			history[historyCount] = prompt;
			historyCount++;
			}
			else{
				for (size_t i = 1; i< 5;i++) {
					history[(i-1)] = history[i];
				}
				history[4] = prompt;
			}
			cout <<  display << " < " << globalPrompt << " > ";
			cin >> prompt;
		}
		else if(prompt == "toh"){
			globalPrompt++;
			cout << "Office Hours: 11:30am to 12:30pm, Mon. and Wed" << endl;
			if(historyCount <= 4){
			history[historyCount] = prompt;
			historyCount++;
			}
			else{
				for (size_t i = 1; i<5;i++) {
					history[(i-1)] = history[i];
				}
				history[4] = prompt;
			}
			cout <<  display << " < " << globalPrompt << " > ";
			cin >> prompt;
		}
		else if(prompt == "tma"){
			globalPrompt++;
			cout << "david.warnke@wayne.edu" << endl;
			if(historyCount <= 4){
			history[historyCount] = prompt;
			historyCount++;
			}
			else{
				for (size_t i = 1; i<5;i++) {
					history[(i-1)] = history[i];
				}
				history[4] = prompt;
			}
			cout <<  display << " < " << globalPrompt << " > ";
			cin >> prompt;
		}
		else if(prompt == "history"){
			globalPrompt++;
			for (size_t p = 0; p < 5; p++) {
				cout << p << " - " << history[p] << endl;
			}
			if(historyCount <= 4){
			history[historyCount] = prompt;
			historyCount++;
			}
			else{
				for (size_t i = 1; i<5;i++) {
					history[(i-1)] = history[i];
				}
				history[4] = prompt;
			}
			cout <<  display << " < " << globalPrompt << " > ";
			cin >> prompt;
		}
		else if(prompt == "help"){
			globalPrompt++;
			cout << "prompt : sets to any string you input, in addition to the current global history event number, i.e, %h as in csh"<< endl;
			cout << "url : list the course web site" << endl;
			cout << "hour : list class times" << endl;
			cout << "room : list classroom location" << endl;
			cout << "desp : list the description of this course" << endl;
			cout << "text : list the textbook" << endl;
			cout << "ref : list the reference books" << endl;
			cout << "prof : list the professor's name" << endl;
			cout << "pol : professor's office location" << endl;
			cout << "poh : professor's office hours" << endl;
			cout << "pma : professor's email address" << endl;
			cout << "ta : list the TA's name" << endl;
			cout << "tol : TA's office location" << endl;
			cout << "toh : TA's office hours" << endl;
			cout << "tma : TA's email address" << endl;
			cout << "history : list history of events up to the most recent 5" << endl;
			cout << "help : list all the available commands" << endl;
			cout << "exit or quit : exit CSC4420 shell" << endl;
			if(historyCount <= 4){
			history[historyCount] = prompt;
			historyCount++;
			}
			else{
				for (size_t i = 1; i<5;i++) {
					history[(i-1)] = history[i];
				}
				history[4] = prompt;
			}
			cout <<  display << " < " << globalPrompt << " > ";
			cin >> prompt;
		}
		else if(prompt == "quit"){ // exit prompt 1
			break;
		}
		else if(prompt == "exit"){ // exit prompt 2
			break;
		}
		else{ // Handler for any improper string
			globalPrompt++;
			cout << "Invalid prompt" << endl;
			if(historyCount <= 4){
			history[historyCount] = prompt;
			historyCount++;
			}
			else{
				for (size_t i = 1; i<5;i++) {
					history[(i-1)] = history[i];
				}
				history[4] = prompt;
			}
			cout <<  display << " < " << globalPrompt << " > ";
			cin >> prompt;
		}
			}
			return 0;
	}
