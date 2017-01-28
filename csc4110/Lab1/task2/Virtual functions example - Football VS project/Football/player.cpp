/*
 * This is the implementation file for the player class for CSC 4111 Lab 1 Task 2
 * You are not allowed to change this file.
 * 10 points will be subtracted if this file is modified.
 *
 * @Author C. Dorman
 */

#include "player.h"

/*
 * This is the constructor for the player class.
 * @param The player's name.
 */
Player::Player(string name){
	this->name = name;
}

/*
 * This is a mutator method, it sets the player's number.
 * @param The player's number.
 */
void Player::setNumber(int number){
	this->number = number;
}

/*
 * This is a method to print out a players stats, its virtual,
 * so it is possible to override it.
 */
void Player::printStats() const{
	cout << "Name: " << name << "\tNumber: " << number;
}


