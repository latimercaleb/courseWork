#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

// Globals here
int countCorrect = 0;
int countWrong = 0;

// Functions
// Sets the difficulty level which determines total number of digits in problem
int setLevel(char lv) { // Part D
	lv = toupper(lv);
	switch (lv) {
	case 'D':
		return 9;
	case 'C':
		return 999;
	case 'B':
		return 9999;
	case 'A':
		return 99999;
	default: 
		cout << "Invalid level choice, setting to 1 \n";
		return 9;
	}
}

// Simple repeatable arithmetic operations
int addition(int num1, int num2){
	return num1 + num2;
}

int subtraction(int num1, int num2){
	return num1 - num2;
}

int multiplication(int num1, int num2){
	return num1 * num2;
}

int division(int num1, int num2){
	return num1 / num2;
}
// We check for the bad denominator here and fix it if it turns out to be one
int fixNum2(int num2) {
	while (num2 == 0) {
	num2 = (rand() % 9) + 1;
	}
	return num2;
}

// End of game message and tallying of score, Part C
void sanityCheck() {
	double pct = static_cast<double>(countCorrect) / static_cast<double>(countCorrect + countWrong);
	if (pct >= 0.75) {
		cout << "Congratulations, let's level up \n";
	}
	else {
		cout << "Check with teacher for support \n";
	}

	countCorrect = 0;
	countWrong = 0;
}

// Correct answer prompts Part B
void rightAnswer(){
	int choice = (rand() % 4) + 1;
	if (choice == 1)
		cout << "Very Good!" << endl;
	else if (choice == 2)
		cout << "Excellent!" << endl;
	else if (choice == 3)
		cout << "Nice Work!" << endl;
	else
		cout << "Keep Up The Good Work!" << endl;
	countCorrect++;
	int totalCount = countCorrect + countWrong;
	if (totalCount == 10) { sanityCheck(); }
}
// Incorrect answer prompts Part B
void wrongAnswer(){
	int choice = (rand() % 4) + 1;
	if (choice == 1)
		cout << "No. Please try again." << endl;
	else if (choice == 2)
		cout << "Wrong. Try once more." << endl;
	else if (choice == 3)
		cout << "Don't give up!" << endl;
	else
		cout << "No. Keep trying!" << endl;
	countWrong++;
	int totalCount = countCorrect + countWrong;
	if (totalCount == 10) { sanityCheck(); }
}

// Convert selected option to it's arithmetic operator
char getSymbol(char x) {
	switch (x) {
	case 'A':
		return '+';
	case 'S':
		return '-';
	case 'M':
		return '*';
	case 'D':
		return '/';
	default:
		return x;
	}
}

// Get a random operator
char getRand() {
	int op = (rand() % 4) - 1;
	switch (op) {
	case 1:
		return '+';
	case 2:
		return '-';
	case 3:
		return '*';
	case 4:
		return '/';
	default:
		return '+';
	}
}

// Decide which arithmetic to do, then check the result of that against the user answer
bool checkAnswer(int userAnswer, int num1, int num2, char op) {
	int realAns;
	switch (op) {
	case '+':
		realAns = addition(num1, num2);
		break;
	case '-':
		realAns = subtraction(num1, num2);
		break;
	case '*':
		realAns = multiplication(num1, num2);
		break;
	case '/':
		realAns = division(num1, num2);
		break;
	default:
		cout << "Input must be A, S, M, D or E, input a valid character \n";
		break;
	}

	if (realAns == userAnswer) { 
		rightAnswer();
		return true;
	}
	else { 
		wrongAnswer();
		return false;
	}
}

// Main menu and part A & E
void menu() {
	char op;
	int difficulty;
	int num1, num2, ans, endOfTest;
	bool solved = true;
	
	do {
		endOfTest = 10;
		cout << "\t \t CAI Instruction Terminal \n"
			<< "\t \t \t Enter an option from the selection below to proceed \n"
			<< "\t \t Options: \n\n"
			<< "A: Addtion \t"
			<< "S: Subtraction \t"
			<< "M: Multiplication \t"
			<< "R: Random \t"
			<< "D: Division \n\n"
			<< "E: Exit \n\n"
			<< "Enter the character here: ";
		cin >> op;
		if (!isalpha(op)) {
			// Entered a non-alpha exception
			cout << "Input must be A,S,M,D or E, input a valid character: \n";
			menu();
		}
		else {
			op = toupper(op);
			// Set difficulty
			char usrLevel;
			cout << "Set difficulty level D being lowest, A being highest from (A,B,C,D): ";
			cin >> usrLevel;
			int level = setLevel(usrLevel);

			while (endOfTest > 0) {
				// Single digit random numbers, if previous problem was solved or starts with random numbers
				if(solved){
					num2 = (rand() % level) + 1;
					num1 = (rand() % level) + 1;
					if (op == 'D' && num2 == 0) { num2 = fixNum2(num2); } // Just in case we a divide by 0
					if (op == 'R') { op = getRand(); } // For the case of random being selected, to grab a random operation
					op = getSymbol(op); // Change op to it's matching operation
				}
			
				cout << "How much is " << num1 << " " << op << " " << num2 << " ?\n";
				cin >> ans;
				solved = checkAnswer(ans, num1, num2, op);
				endOfTest--;
			}

		}
	} while (op != 'E');
		

}

int main()
{
	srand(time(NULL)); // required to force random numbers each time
	menu(); // Part A
}

