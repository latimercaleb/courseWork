#include "offense.h"
#include <iostream>
#include <string>
using namespace std;

Offense::Offense(string name):Player(name)
{
}

void Offense::setMinutesPlayed(int minutes)
{
	this->minutes = minutes;
}

void Offense::setYards(int yards)
{
	this->yards = yards;
}

void Offense::printStats() const
{
	Player::printStats();
	cout<<"\tMinutes: "<< minutes <<"\tYards: "<< yards <<endl;
}