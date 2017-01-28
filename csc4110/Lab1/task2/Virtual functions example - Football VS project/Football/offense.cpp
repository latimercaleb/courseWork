// offense.cpp written by Caleb Latimer for CSC 4111 task 2
#include"Offense.h"

Offense::Offense(string name): Player(name) {
	// populates local name after populating base class
	myName = name;
}

void Offense::setMinutesPlayed(int minutes) {
	// sets minutes for player
	this->minutes = minutes;
}

void Offense::setYards(int yards) {
	// sets yards for player
	this->yards = yards;
}

void Offense::printStats() const {
	// modified form of print from base class
	cout << "Name: " << myName << "\tNumber: " << number << "\tMinutes: " << minutes << "\tYards: " << yards << endl;
}