/*
 * @Author C. Dorman
 */

#include <iostream>
#include <string>
#include "player.h"
#include "offense.h"            
#include "defense.h"
#include "Brian.h"
#include "Caleb.h"
#include "Tahmid.h"
#include "Safayeth.h"
#include "Zaid.h"
#include "Sarah.h"
#include <windows.h>
using namespace std;

int main(){

	// Create the players for the team.
	Offense player("Bob");
	Defense player1("Jane");
	Offense player2("Sai");
	Defense player3("Chin");
	Offense player4("Kali");
	Offense player5("Tom");
	Brian player6("Brian Atiyeh");
	Caleb player7("Caleb"); // Added for player Caleb 
	Tahmid player8("Tahmid");
	Safayeth player9("Safayeth");
	Zaid player10("Zaid");
	Sarah player11("Sarah");


	Player *team[12]; // Make a team of pointers to players, must be updated for each new addition

	team[0] = &player;
	team[1] = &player1;
	team[2] = &player2;
	team[3] = &player3;
	team[4] = &player4;
	team[5] = &player5;
	team[6] = &player6;
	team[7] = &player7;
	team[8] = &player8;
	team[9] = &player9;
	team[10] = &player10;
	team[11] = &player11;

	// Set the player numbers
	for(int i=0; i<12; i++) // must update to reflect current number of players
		team[i]->setNumber(i+10);

	// Set the player minutes.
	for(int i=0; i<12; i++) // must update to reflect current number of players
		team[i]->setMinutesPlayed(i*7+(i+1)*i+1);

	// Set the player's stats.
	player.setYards(34);
	player1.setTackles(5);
	player2.setYards(23);
	player3.setTackles(7);
	player4.setYards(132);
	player5.setYards(20);
	player6.setYards(450);
	player7.setYards(3000);
	player8.setYards(28);

	player8.setTouchdowns(4);
	player9.setTackles(999);
	player10.setYards(1409);

	player11.setYards(100);

	// Print out each player's stats.
	for(int i=0; i<12; i++) // again update to reflect current number of players
		team[i]->printStats();

	system("pause");

}