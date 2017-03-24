// Lab 4 Problem 3 by Caleb Latimer
#include <iostream>
using namespace std;
struct Time // Struct type time created here
{
	int hours;
	int minutes;
	int seconds;

}myClock;// struct var name created for use in main
void toSeconds(struct Time)// specified as parameter for function here
{
	int totalS;
	totalS = (myClock.hours * 3600) + (myClock.minutes * 60) + myClock.seconds;
	cout << "Total Seconds : " << totalS << endl; // Result output

}
int main()
{
	cout << "Input hours : ";
	cin >> myClock.hours; // initialization form for struct
	cout << "\nInput minutes : ";
	cin >> myClock.minutes;
	cout << " \nInput seconds : ";
	cin >> myClock.seconds;
    toSeconds(myClock);
	return 0; 
}