//personTypeImp.cpp
  
#include <iostream> 
#include <string>
#include "personType.h"

using namespace std;

void personType::print() const
{
    cout << firstName << " " << middleName<< " " << lastName;
	cout << endl;
}

void personType::setName(string first, string last)
{
    firstName = first;
    lastName = last;
}

string personType::getFirstName() const
{
    return firstName;
}

string personType::getLastName() const
{
    return lastName;
}

    //constructor
personType::personType(string first, string last, string middle) 

{ 
    firstName = first;
    lastName = last;
	middleName = middle;
}
string personType::setFirstname(string name)
{
	firstName = name;
	return firstName;
}
string personType::setLastname(string name2)
{
	lastName = name2;
	return lastName;
}
string personType::setMiddlename(string name3)
{
	middleName = name3;
	return middleName;
}
void personType::checkFirst(string test)
{
	if (test == firstName)
		cout << "Same name! Clone detected!" << endl;
	else
		cout << "Not the same name" << endl;
}
void personType::checkLast(string test2)
{
	if (test2 == lastName)
		cout << "Same name! Clone detected!" << endl;
	else
		cout << "Not the same name" << endl;
}

