// Problem 2: Movie Review
#include <iostream>
#include<string>
#include<stdlib.h>
#include<time.h>
#include<iomanip>
using namespace std;
// class defined
class Movie {
public:
	// Constructors
	Movie();
	Movie(string, string);
	// Mutations
	void changeMPAA(char);
	void changeName(string);
	bool addRating(int);
	void printMovie();
	// Accessors
	string getMPAA() const;
	string getName() const;
	double getAverage() const;
	
private:
	string name;
	string MPAA;
	int rating[5];
};

// Method definitions
Movie::Movie() {
	name = "";
	MPAA = "";
	for (int i = 0; i < 5; i++)
		rating[i] = 0;
}
Movie::Movie(string Name, string Rate) {
	name = Name;
	MPAA = Rate;
	for (int i = 0; i < 5; i++)
		rating[i] = 0;
}
void Movie::changeMPAA(char x) {
	this->MPAA = x;
}
void Movie::changeName(string x) {
	this->name = x;
}

string Movie::getMPAA() const {
	return this->MPAA;
}
string Movie::getName() const {
	return this->name;
}
bool Movie::addRating(int category) {
	if (category >= 1 && category <= 5) {
		rating[category - 1]++;
		return true;
	}
	else
		return false;
}
double Movie::getAverage() const {
	double sum = 0;
	for (int i = 0; i < 5; i++)
		sum += (rating[i] *(i+1));
	sum = sum / 5;
	return sum;
}
void Movie::printMovie() {
	cout << name << ", " << MPAA << " ";
}
int main() {
	Movie First("The Adjustment Bureau", "PG-13");
	Movie Second("I Am Number Four", "PG-13");

	First.printMovie();
	First.addRating(5);
	First.addRating(5);
	First.addRating(4);
	First.addRating(4);
	First.addRating(5);
	cout << "Average Rating: " << fixed << showpoint << setprecision(1) << First.getAverage() << endl;

	Second.printMovie();
	Second.addRating(3);
	Second.addRating(2);
	Second.addRating(2);
	Second.addRating(4);
	Second.addRating(1);
	cout << "Average Rating: " << fixed << showpoint << setprecision(1) << Second.getAverage() << endl;
	cout << "Press any key to exit ... \n";
	char exitChar;
	cin >> exitChar;
	return 0;
}
