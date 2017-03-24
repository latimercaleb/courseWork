/*
 * @Author C. Dorman
 */

#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <string>

using namespace std;

class Player{
private:
	string name;

protected:
	int number; // The player's number.
	int minutes; // The number of minutes the player is in the game.

public:	

	/*
	 * This is the constructor for the player class.
	 * @param The player's name.
	 */
	Player(string name);

	/*
	 * This is a mutator method, it sets the player's number.
	 * @param The player's number.
	 */
	void setNumber(int number);

	/*
	 * Add comments for this method in your inherited class.
	 */
	virtual void setMinutesPlayed(int minutes) = 0;
	
	/*
	 * This is a method to print out a players stats, its virtual,
	 * so it is possible to override it.
	 */
	virtual void printStats() const; 
};

#endif