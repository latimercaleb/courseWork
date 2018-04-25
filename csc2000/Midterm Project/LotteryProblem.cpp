// Lottery Problem
#include<iostream>
#include <algorithm>
#include<array>
#include<stdlib.h>
#include<time.h>
using namespace std;

class Lottery {
public:
	Lottery() {
		srand(time(NULL));
		for (size_t i = 0; i < 5; i++) {
			lotto[i] = (rand() % 40) + 1;
		}
		printLotto();
	}
	void getChoices() {
		cout << "Enter 5 values between 1-40 inclusive: ";
		cout << "Enter the first number: ";
		for (size_t i = 0; i < 5; i++) {
			cin >> usrChoice[i];
			if (usrChoice[i] > 40 || usrChoice[i] < 1) {
				do {
					cout << "Number must be between 1 and 40. Select another. ";
					cin >> usrChoice[i];
				} while (usrChoice[i] > 40 || usrChoice[i] < 1);
			}
			cout << "Enter the next number: ";
		}
	}
	bool wonLotto() {
		sort(lotto, lotto + 5);
		sort(usrChoice, usrChoice + 5);
		for (size_t i = 0; i < 5; i++) {
			if (lotto[i] == usrChoice[i])
				continue;
			else
				return false;
		}
		return true;
	}
	void printLotto() {
		cout << "Lotto is: ";
		for (size_t i = 0; i < 5; i++) {
			cout << lotto[i] << " ";
		}
		cout << endl;
	}
private:
	int lotto[5];
	int usrChoice[5];
};

int main() {
	bool playing = true;
	bool winner;
	char c;
	while (playing) {
		Lottery megaMilli;
		megaMilli.getChoices();
		if (megaMilli.wonLotto() == true)
			cout << "You won!\n";
		else {
			cout << "You lost! The correct numbers are ";
			megaMilli.printLotto();
		}
		cout << "Play again? Y/N \n";
		cin >> c;
		c = tolower(c);
		c == 'y' ? playing = true : playing = false;
	}
	
	return 0;
}