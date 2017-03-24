#include "defense.h"
#include <iostream>
#include <string>
using namespace std;

Defense::Defense(string name):Player(name)
{
}

void Defense::setMinutesPlayed(int minutes)
{
	this->minutes = minutes;
}

void Defense::setTackles(int tackles)
{
	this->tackles = tackles;
}

void Defense::printStats() const
{
	Player::printStats();
	cout<<"\tMinutes: "<< minutes <<"\tTackles: "<< tackles <<endl;
}