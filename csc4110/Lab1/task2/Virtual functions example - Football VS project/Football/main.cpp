/*
 * This is the main class for CSC 4111 Lab 1 Task 2
 * You are not allowed to change this file.
 * 10 points will be subtracted if this file is modified.
 *
 * @Author C. Dorman
 */

#include <iostream>
#include <string>
#include "player.h"
#include "offense.h"            
#include "defense.h"
#include <windows.h>
using namespace std;

int main(){

	// Create the players for the team.
	Offense player("Bob");
	Defense player1("Jane");
	Offense player2("Sai");
	Defense player3("Chin");
	Offense player4("Kali");

	Player *team[5]; // Make a team of pointers to players.

	// Question 1 - Why is there an '&' before the players on lines 29 to 33?
	team[0] = &player;
	team[1] = &player1;
	team[2] = &player2;
	team[3] = &player3;
	team[4] = &player4;

	// Set the player numbers
	for(int i=0; i<5; i++)
		team[i]->setNumber(i+10);

	// Set the player minutes.
	for(int i=0; i<5; i++)
		team[i]->setMinutesPlayed(i*7+(i+1)*i+1);

	// Question 2 - Why not use a loop for lines 45 to 49?
	// Set the player's stats.
	player.setYards(34);
	player1.setTackles(5);
	player2.setYards(23);
	player3.setTackles(7);
	player4.setYards(132);

	// Print out each player's stats.
	for(int i=0; i<5; i++)
		team[i]->printStats();

	system("pause");

}