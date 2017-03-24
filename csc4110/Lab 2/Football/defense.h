#ifndef DEFENSE_H
#define DEFENSE_H

#include "player.h"
#include <iostream>
#include <string>

using namespace std;

class Defense:public Player
{
private:
	int tackles;

public:
	Defense(string name);
	virtual void setMinutesPlayed(int minutes);
	void setTackles(int tackles);
	virtual void printStats() const;
};

#endif