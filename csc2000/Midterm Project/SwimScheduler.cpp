// Swim Schedule Problem
// Main File
#include<iostream>
#include<string>
#include<iomanip>
#include <fstream>
#include<array>
using namespace std;


// Classes for instructors
class Jeff {
public:
	Jeff() { // Constructor
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
				this->schedule[i][j] = '-';
		this->shift[0] = "11-12";
		this->shift[1] = "12-1";
		this->shift[2] = "1-2";
		this->shift[3] = "2-3";
	}
	char getSchedule(int time, int day) { // Returns schedule for outfile
		return schedule[time][day];
	}
	void printSchedule() { // Print method
		cout << "Jeff:\n" << "\t\t Mon\t Tue\t Wed\t Thu\t \n";
		for (int i = 0; i < 4; i++) {
			cout << this->shift[i] << "\t";
			for (int j = 0; j < 4; j++) {
				cout << "\t" << this->schedule[i][j];
			}
			cout << endl;
		}
		cout << endl << endl;
	}
	bool isAvailableForSingleOrGroup(int time, int day) { // Returns non-scaled availability
		return schedule[time][day] == '-';
	}
	bool isAvailable(int time, int day) { // Returns scaled availability
		time--;
		day--;
		return schedule[time][day] == '-'; 
	}
	void bookSlot(int time, int day) { // Booking method
		time--;
		day--;
		this->schedule[time][day] = 'X';
	}
	void clearSlot(int time, int day) { // Freeing method
		time--;
		day--;
		this->schedule[time][day] = '-';
	}
	string getShift(int requestedShift) { // Method to return shifts
		return this->shift[requestedShift];
	}
	void printSingleSessions() {}
	void printGroupSessions() {}
private:
	char schedule[4][4];
	string shift[4];
};


class Anna { // Anna shares the same methods as Jeff
public:
	Anna() {
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
				this->schedule[i][j] = '-';
		this->shift[0] = "11-12";
		this->shift[1] = "12-1";
		this->shift[2] = "1-2";
		this->shift[3] = "2-3";
	}
	char getSchedule(int time, int day) { // Returns schedule for outfile
		return schedule[time][day];
	}
	void printSchedule() {
		cout << "Anna:\n" << "\t\t Mon\t Tue\t Wed\t Thu\t \n";
		for (int i = 0; i < 4; i++) {
			cout << this->shift[i] << "\t";
			for (int j = 0; j < 4; j++) {
				cout << "\t" << this->schedule[i][j];
			}
			cout << endl;
		}
		cout << endl << endl;
	}
	bool isAvailableForSingleOrGroup(int time, int day) {
		return schedule[time][day] == '-';
	}

	bool isAvailable(int time, int day) {
		time--;
		day--;
		return schedule[time][day] == '-';
	}
	void bookSlot(int time, int day) {
		time--;
		day--;
		this->schedule[time][day] = 'X';
	}
	void clearSlot(int time, int day) {
		time--;
		day--;
		this->schedule[time][day] = '-';
	}
	string getShift(int requestedShift) {
		return this->shift[requestedShift];
	}
	void printSingleSessions() {}
	void printGroupSessions() {}
private:
	char schedule[4][4];
	string shift[4];
};

// Global teacher objects
Jeff CoachJ;
Anna CoachA;

// Helper functions
void scheduleSlot() { // Prompt choices then schedule a day
	int teacher, day, slot;
	cout << "Select instructor (1 - Jeff, 2 - Anna): ";
	cin >> teacher;
	cout << "Select Day (1 - Mon, 2- Tue, 3 - Wed, 4 - Thu): ";
	cin >> day;
	cout << "Select Slot (1 - 11-12, 2 - 12-1, 3 - 1-2, 4 - 2-3): ";
	cin >> slot;

	struct DecideAndBook { // Nested function with struct inside helper
		void getSlot(int teacher, int day, int slot) {
			if (teacher == 1) { // Jeff route
				if (CoachJ.isAvailable(slot, day)) {
					CoachJ.bookSlot(slot,day);
				}
				else {
					cout << "\n Coach Jeff is not available that day, please pick another shift. Or a different teacher. \n\n";
				}
			}
			else { // Anna route
				if (CoachA.isAvailable(slot, day)) {
					CoachA.bookSlot(slot,day);
				}
				else {
					cout << "\n Coach Anna is not available that day, please pick another shift. Or a different teacher. \n\n";
				}
			}
		}
	}; DecideAndBook DecisionObject;

	DecisionObject.getSlot(teacher, day, slot); // Invoke function
	
}
void freeSlot() { // Prompt choices and then free a day
	int teacher, day, slot;
	cout << "Select instructor (1 - Jeff, 2 - Anna): ";
	cin >> teacher;
	cout << "Select Day (1 - Mon, 2- Tue, 3 - Wed, 4 - Thu): ";
	cin >> day;
	cout << "Select Slot (1 - 11-12, 2 - 12-1, 3 - 1-2, 4 - 2-3): ";
	cin >> slot;

	struct DecideAndFree { // Nested function with struct inside helper
		void getSlot(int teacher, int day, int slot) {
			if (teacher == 1) { // Jeff route
				if (!CoachJ.isAvailable(slot, day)) {
					CoachJ.clearSlot(slot, day);
				}
				else {
					cout << "\n Coach Jeff is already available! \n\n";
				}
			}
			else { // Anna route
				if (!CoachA.isAvailable(slot, day)) {
					CoachA.clearSlot(slot, day);
				}
				else {
					cout << "\n Coach Anna is already available! \n\n";
				}
			}
		}
	}; DecideAndFree DecisionObject;

	DecisionObject.getSlot(teacher, day, slot); // Invoke function

}
void showIndividual() { // Show available slots when at least one is free
	cout << "\t\t Mon\t Tue\t Wed\t Thu\t \n";
	for (int i = 0; i < 4; i++) {
		cout << CoachJ.getShift(i) << "\t";
		for (int j = 0; j < 4; j++) {
			if(CoachJ.isAvailableForSingleOrGroup (i,j) || CoachA.isAvailableForSingleOrGroup(i,j))
				cout << "\t" << 'I';
			else
				cout << "\t" << '-';
		}
		cout << endl;
	}
	cout << endl << endl;
}
void showGroup() { // Show available slots when both are free
	cout << "\t\t Mon\t Tue\t Wed\t Thu\t \n";
	for (int i = 0; i < 4; i++) {
		cout << CoachJ.getShift(i) << "\t";
		for (int j = 0; j < 4; j++) {
			if (CoachJ.isAvailableForSingleOrGroup(i, j) && CoachA.isAvailableForSingleOrGroup(i, j))
				cout << "\t" << 'G';
			else
				cout << "\t" << '-';
		}
		cout << endl;
	}
	cout << endl << endl;
}

// Ex Cred functions
void writeOut() {
	cout << "Enter a name for your file: ";
	string fName;
	cin >> fName;
	ofstream output;
	fName += ".txt";
	output.open(fName);
	output << "Jeff:\n" << "\t\t Mon\t Tue\t Wed\t Thu\t \n";
	for (int i = 0; i < 4; i++) {
		output << CoachJ.getShift(i) << "\t";
		for (int j = 0; j < 4; j++) {
			output << "\t" << CoachJ.getSchedule(i,j);
		}
		output << endl;
	}
	output << endl << endl;
	output << "Anna:\n" << "\t\t Mon\t Tue\t Wed\t Thu\t \n";
	for (int i = 0; i < 4; i++) {
		output << CoachA.getShift(i) << "\t";
		for (int j = 0; j < 4; j++) {
			output << "\t" << CoachA.getSchedule(i, j);
		}
		output << endl;
	}
	output << endl << endl;
	output.close();
	cout << "Output written successfully \n";
}

// Main function
void app() {
	char choice;
	do {
		CoachJ.printSchedule();
		CoachA.printSchedule();
		cout << "Enter one of the following commands: \n"
			<< "p - Print schedules \n"
			<< "s - Schedule a free slot  \n"
			<< "f - Free a slot \n"
			<< "i - Show slots available for individual lessons \n"
			<< "g - Show slots available for group lessons \n"
			<< "w - Write to file \n" // Ex Cred 1 Part 1
			<< "q - Quit \n"
			<< "Command: ";
		cin >> choice;

		switch (choice) {
		case 'p':
			break; // start loop again and view schedules
		case 's':
			scheduleSlot();
				break;
		case 'f':
			freeSlot();
			break;
		case 'i':
			showIndividual();
			break;
		case 'g':
			showGroup();
			break;
		case 'w':
			writeOut();
			break;
		case 'q':
			break; // loop should terminate
		}

	} while (choice != 'q'); // Prompt user then loop repeatedly until q is selected.
}

// Entry point
int main() {
	app();
	return 0;
}