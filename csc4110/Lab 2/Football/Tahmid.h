#ifndef TAHMID_H
#define TAHMID_H

#include <iostream>
#include "offense.h"

class Tahmid : public Offense{
public:
	Tahmid(string name);
	void setTouchdowns(int touchdowns);
	void printStats() const;
private:
	int touchdowns;
};

#endif