// Problem 1: Memory game
#include <iostream>
#include<string>
#include<stdlib.h>
#include<time.h>
using namespace std;
// class defined
class Card {
public: 
	// Constructors
	Card();
	Card(int);
	// Mutations
	void flipCard();
	void matchCard(Card &obj);
	void changeValue(int);
	// Accessors
	int getCard() const;
	bool isMatched() const;
	bool isFlipped() const;
private:
	int value;
	bool matched;
	bool state;
};

// Method definitions
Card::Card() {
	value = 0; // 0 assigned to start
	matched = false; // no match so false
	state = false; // false = down,  up = true
}

Card::Card(int i) {
	value = i;
	matched = false;
	state = false;
}

void Card::flipCard() {
	this->state = !(this->state);
}

void Card::matchCard(Card &obj) {
	if (obj.matched == false && this->matched == false) {
		obj.state = true;
		obj.matched = true;
		this->state = true;
	    this->matched = true;
	}
	else
		cout << "This card has already been matched!\n";
}

void Card::changeValue(int x) {
	this->value = x;
}

int Card::getCard() const {
	return this->value;
}

bool Card::isMatched()const {
	return this->state;
}
bool Card::isFlipped() const {
	return this->state;
}

// Game Functions
void turn(int &row, int&col) {
	cout << "Please select a row 1-4: ";
	cin >> row;
	if (row < 1 || row > 4) {
		while (row < 1 || row > 4) {
			cout << "Invalid Row \n";
			cout << "Please select a row 1-4: ";
			cin >> row;
		}
	}
	row -= 1; 
	cout << endl;
	cout << "Please select a column 1-4: ";
	cin >> col;
	if (col < 1 || col > 4) {
		while (col < 1 || col > 4) {
			cout << "Invalid Col \n";
			cout << "Please select a column 1-4: ";
			cin >> col;
		}
	}
	col -= 1;
	return;
}

int pickRand(int store[], int size) {
	int idx = rand() % 8;
	while (true) {
		int randNum = store[idx];
		if (randNum != -1) {
			store[idx] = -1;
			return randNum;
		}
		else
			idx = rand() % 8;
	}
	return 0;
}

void printGame(Card game[][4])
{
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (game[i][j].isMatched())
				cout << game[i][j].getCard() << " ";
			else
				cout << "*" << " ";
		}
		cout << endl;
	}
}
// Main Function
int main() {
	srand(time(NULL));
	int mainSet[8];
	for (int i = 0; i < 8; i++) 
		mainSet[i] = (rand() % 8) + 1;
	int cpySet[8];
	for (int i = 0; i < 8; i++)
		cpySet[i] = mainSet[i];

	Card GameGrid[4][4];

	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 4; j++) {
			GameGrid[i][j] = pickRand(mainSet, 8);
		}
	}

	for (int i = 2; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			GameGrid[i][j] = pickRand(cpySet, 8);
		}
	}
	cout << "Wanna play a game?\n";
	int matchCount = 0;
	int userRow, userCol;
	// Game starts
	while (matchCount < 8) {
		printGame(GameGrid);

		turn(userRow, userCol);
		Card first = GameGrid[userRow][userCol];
		if (GameGrid[userRow][userCol].isFlipped()) {
			while (GameGrid[userRow][userCol].isFlipped()) {
				cout << "Card has already been matched! \n";
				turn(userRow, userCol);
				first = GameGrid[userRow][userCol];
			}
		}
		int r1 = userRow;
		int c1 = userCol;
		GameGrid[userRow][userCol].flipCard();
		printGame(GameGrid);

		turn(userRow, userCol);
		Card second = GameGrid[userRow][userCol];
		if (GameGrid[userRow][userCol].isFlipped()) {
			while (GameGrid[userRow][userCol].isFlipped()) {
				cout << "Card has already been matched! \n";
				turn(userRow, userCol);
				second = GameGrid[userRow][userCol];
			}
		}
		int r2 = userRow;
		int c2 = userCol;
		if (r1 == r2 && c1 == c2) {
			while (r1 == r2 && c1 == c2) {
				cout << "Card has already been selected, please pick another \n";
				turn(userRow, userCol);
			    second = GameGrid[userRow][userCol];
				r2 = userRow;
				c2 = userCol;
			}
		}
		GameGrid[userRow][userCol].flipCard();
		printGame(GameGrid);

		if (first.getCard() == second.getCard()) {
			cout << "Pair found!\n";
			GameGrid[r1][c1].matchCard(GameGrid[r2][c2]);
			matchCount++;
		}
		else {
			cout << "Not a match! \n";
			GameGrid[r1][c1].flipCard();
			GameGrid[r2][c2].flipCard();
		}
		cout << "Try Again \n";
	}
	cout << "Thanks for playing! Enter any key to exit: ";
	char exit;
	cin >> exit;
	return 0;
}