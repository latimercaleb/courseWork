// Implementation of derived class
#include "extClockType.h"
//#include<iostream> // All precompilers and namespaces are removed here since they are declared in header file
//#include<string> 
//using namespace std; 

extClockType::extClockType()
{
	timezone = " ";
}
extClockType::extClockType(string d)
{
	timezone = d;
	//return timezone; returns don't go in constructors
}
void extClockType::printzone()const
{
	cout << " The timezone is : " << timezone << endl; // string lib must be called in order to use strings in a function
}
string extClockType::changezone(string g)
{
	cout << "The timezone has changed from " << timezone << " to " << g << endl;
	timezone = g;
	return timezone; 
}