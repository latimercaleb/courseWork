#pragma once
// offense.h written by Caleb Latimer for CSC 4111 task 2
#include "player.h"
class Offense : public Player {
public:
	int yards;
	string myName; // Additional variable to locally hold name 
	Offense(string name);
	void setMinutesPlayed(int minutes);
	void setYards(int yards);
	void printStats() const;

};