#pragma once
// defense.h written by Caleb Latimer for CSC 4111 task 2
#include "player.h"
class Defense : public Player {
public:
	int tackles; 
	string myName;
	Defense(string name); 
	void setMinutesPlayed(int minutes); 
	void setTackles(int tackles); 
	void printStats() const;

};