#ifndef OFFENSE_H
#define OFFENSE_H

#include "player.h"
#include <iostream>
#include <string>

using namespace std;

class Offense:public Player
{
private:
	int yards;

public:
	Offense(string name);
	virtual void setMinutesPlayed(int minutes);
	void setYards(int yards);
	virtual void printStats() const;
};

#endif