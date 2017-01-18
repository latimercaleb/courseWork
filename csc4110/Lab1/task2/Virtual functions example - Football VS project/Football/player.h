/*
 * This is the header file for the player class for CSC 4111 Lab 1 Task 2
 * You are not allowed to change this file. 
 * 10 points will be subtracted if this file is modified.
 *
 * @Author C. Dorman
 */

// Question 3 - What do the #ifndef, #define and #endif preprocessor commands do in this file? 
#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <string>

using namespace std;

class Player{
private:
	string name; // The player's name, notice it's private, Question 4 - What does this mean you have to do?

protected:  // Question 5 - Why does number have to be private.
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
	virtual void setMinutesPlayed(int minutes) = 0; // Question 6 - why does this method equal zero?
	
	/*
	 * This is a method to print out a players stats, its virtual,
	 * so it is possible to override it.
	 */
	virtual void printStats() const; // Question 7 - What does 'const' do here? 
};

#endif