// Derived class header file will name class, functions and variables
#include"clockType.h"
#include<iostream>
#include<string>
using namespace std;

class extClockType : public clockType{ // inheritance of public type from clockType
public:
	extClockType(); // Default Constructor
	extClockType(string); // Parameter based constructor

	void printzone()const; // Function to print timezone
	string changezone(string); // Function to change timezone to something else

private: 
	string timezone; // private var of timezone 
};