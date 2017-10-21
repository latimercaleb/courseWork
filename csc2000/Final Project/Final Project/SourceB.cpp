// SourceB.cpp : Time converter
//
#include<iostream>
using namespace std;

// Supporting functions

// Function to print the current time
void printTime(int hr, int min, int sec, char t) {
	t = toupper(t);
	cout << "The converted time is: " << hr << " : " << min << " : " << sec << " " << t << 'M' << endl << endl;
}

void setTime(int &hours, int &minutes, int &seconds, char &T) {
	cout << "Please enter the time data \n"
		 << "Enter the hours: ";
	cin >> hours;
	cout << "Enter the minutes: ";
	cin >> minutes;
	cout << "Enter the seconds: ";
	cin >> seconds;
	cout << "Enter an A for AM or a P for PM: ";
	cin >> T;
}

//menu function
int mainOptionWindow() {
	cout << "Welcome to the time converter!\n"
		<< "This application will present a menu and allow you to select from 2 options to manipulate your time format \n"
		<< "You, the user will be able to take the following actions : \n"
		<< "12-hour notation \t 24-hour notation \n"
		<< "Please choose from one of the options below: \n"
		<< "1: Change to 12-hour time \n"
		<< "2: Change to 24-hour time \n \n"
		<< "0: To terminate the program and exit \n\n"
		<< "What is your selection?\t";

	int userChoice;
	cin >> userChoice;
	return userChoice;
}

// multiplication of fractions that are passed in as parameters
void to12(int hours, int minutes, int seconds, char T) {
	int newHr;
	if (hours > 12)
		newHr = hours - 12;
	else
		newHr = hours;
	printTime(newHr, minutes, seconds, T);
	cout << "Returning to main menu ... \n";
}

// division of fractions that are passed in as parameters
void to24(int hours, int minutes, int seconds, char T) {
	int newHr;
	if (T == 'p' || T == 'P')
		newHr = hours + 12;
	else
		newHr = hours;
	
	printTime(newHr, minutes, seconds, T);
	cout << "Returning to main menu ... \n";
}




// Main function
int main()
{
	// implement supporting functions
	int menuSelection = 12;
	int hours, minutes, seconds;
	char T;
	while (menuSelection != 0) {
		menuSelection = mainOptionWindow();
		switch (menuSelection) {
		case 1:
			cout << "Conversion to 12-hour format function executing ...\n";
			setTime(hours, minutes, seconds,T);
			to12(hours,minutes,seconds,T);
			break;

		case 2:
			cout << "Conversion to 24-hour format function executing ...\n";
			setTime(hours, minutes, seconds, T);
			to24(hours, minutes, seconds,T);
			break;

		case 0:
			cout << "Program terminated ... \n";
			break;

		default:
			cout << "INVALID INPUT, please enter a number 1-4, menu restarting ... \n";
		}
	}
	return 0;
}