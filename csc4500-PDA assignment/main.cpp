/*
	Extra Credit Programming assignment for CSC 4500 
	Pushdown Automata that accepts L= a^nb^n on language {a,b}
	Written by Caleb Latimer
	Access ID ej1297
*/

// Required libraries 
#include<iostream> // Used for testing and debugging
#include<fstream> // Used for I/O handling
#include<string> // I/O handling
#include<stack> // PDA computation
#include<vector> // Result storage and output
using namespace std;

enum states { // States for PDA listed here
	q0, q1, q2, qf
};

/*
	Function to print the output of each string computed by the PDA stored as true if it was accepted and false if rejected.
	Output is printed to a text file which is set to overwrite each time this program is run
	Output can be found in source folder called "CSC4500 Extra Credit Assignment Results.txt"
*/
void generateOutput(vector<bool> & args) {
	ofstream solution;
	solution.open("CSC4500 Extra Credit Assignment Results.txt", ios::out, ios::trunc);
	if (!solution.good()) {
		cout << "For some odd reason the above line isn't functioning as intended. \n";
		return;
	}

	solution << "The result of the PDA follows the same notation as the input file, the strings are marked by number in the same sequence as they were provided in the input file: \n \n";
	int count = 1;
	for (vector<bool>::iterator list = args.begin(); list != args.end(); list++) {
		if (*list == 1) {
			solution << count << " : " << "Accepted \n";
		}
		else {
			solution << count << " : " << "Rejected \n";
		}
		count++;
	}

	solution.close();

}

/*
	Function that does the PDA computations, returns an enumerated type which is a representation of the state. 
	Makes use of STL stack and internal logic to determine if the string it is passed is accepted by the language of the PDA
*/
states PDA(string inputText) {

	states currentState = q0;
	char read;
	stack<char>PDAstack; 
	PDAstack.push('Z');
	bool reject = false;
	int a = 0;
	int maxLength = inputText.length();

	while (a<inputText.length() && reject == false) { // read character by character
		read = inputText[a];
		switch (read) {
		case 'a': // Evaluates the transition rules for valid for progress towards qf for a
			if (currentState == q0 && PDAstack.top() == 'Z') {
				currentState = q1;
				PDAstack.push(read);
			}
			else if (currentState == q1 && PDAstack.top() == 'a') {
				currentState = q1;
				PDAstack.push(read);
			}
			else if (currentState == q2) {
				reject = true;
			}

			break;

		case 'b': // Evaluates the transition rules for valid for progress towards qf for b

			if (currentState == q0) {
				reject = true;
			}
			else if (currentState == q1 && PDAstack.top() == 'a') {
				currentState = q2;
				PDAstack.pop();
			}
			else if (currentState == q2 && PDAstack.top() == 'a') {
				currentState = q2;
				PDAstack.pop();
			}
			break;

		default: // if any other character is read other than a or b then reject the string
				reject = false;
		}

		a++;
	}

	if (reject == true) {
		return q0;
	}
	else {
		if (a == maxLength && PDAstack.top() == 'Z') // Last check to ensure that the stack is empty before acceptance
			currentState = qf;
		return currentState;
	}
}

int main() {

	vector<bool> resultsforOutput; // stores result of PDA computation for future print function
	states resultOfPDA = q0; // state variable
	ifstream input;
	input.open("input.txt");
	if (!input.good()) { // Error handling in case file fails to open
		cout << "Error file not found, ensure that input.txt is located in the same directory as main.cpp \n";
		return 1;
	}

	string line;
	// int count = 1; // Test for debugging
	while (getline(input, line)){ // read the file line by line and store the result in line
		if (line == "") {
			// cout << "Done\n"; // Test for debugging
			break;
		}

		string wordToTest = line.substr(2,(line.length()-2)); // Remove unneeded stylization bits and retain core string
		// cout << "Word " << count << " : " << wordToTest << endl; // Test for debugging
		

		resultOfPDA = PDA(wordToTest);
		if (resultOfPDA == qf) {
			//cout << "Result of " << count << " : " << "accepted" << endl; // Test for debugging
			resultsforOutput.push_back(true);
		}
		else {
			//cout << "Result of " << count << " : " << "rejected" << endl; // Test for debugging
			resultsforOutput.push_back(false);
		}

		// count++; // Test for debugging
	}
	input.close();
	generateOutput(resultsforOutput);

	return 0;
}