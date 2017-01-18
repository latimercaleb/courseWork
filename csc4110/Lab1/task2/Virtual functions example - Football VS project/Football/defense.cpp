// defense.cpp written by Caleb Latimer for CSC 4111 task 2
#include"Defense.h"
#include <string>

Defense::Defense(string name):Player(name) {
	// Constructor of defense player populates base class first then derived class 
	myName = name;
}

void Defense::setMinutesPlayed(int minutes) {
	// applies minutes parameter to object's minutes
	this->minutes = minutes;
}

void Defense::setTackles(int tackles) {
	// applies tackles parameter to object's tackles
	this -> tackles = tackles;
}

void Defense::printStats() const {
	// modified form of print method in base class 
	cout << "Name: " << myName << "\tNumber: " << number<< "\tMinutes: " << minutes << "\tTackles: " << tackles << endl;
}