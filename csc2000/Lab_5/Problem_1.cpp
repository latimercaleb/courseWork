// Lab 5 Problem 1 programmed by Caleb Latimer
#include <iostream>
#include <fstream>
#include <string>
#include<iomanip> // Part A
using namespace std;

int main()

{
	ifstream inFile;
	ofstream outFile; // Part B

	inFile.open("inData.txt");
	outFile.open("outData.txt"); // Part C 

	string f_name;
	string L_name;
	string department;
	int c_cup;
	double gross, bonus, time, distance, taxes, cost, payCheck, avgSpeed, salesAmt; // since they are %'s I use double

	outFile << showpoint << fixed << setprecision(2);
	
	cout << "Check outfile for Results!" << endl;
	inFile >> f_name >> L_name >> department >> gross >> bonus >> taxes >> distance >> time >> c_cup >> cost;
	outFile << "Name : " << f_name << " " << L_name << " , Department :" << department << endl; 
	outFile << "Monthly Gross Salary : $" << gross << " , Monthly Bonus : " << bonus << " % , " << " Taxes : " << taxes << '%' << endl;
	
	payCheck = (gross + (gross * (bonus/100))) * ((100 - taxes)/100);
	
	outFile << "Paycheck : $"<< payCheck << endl; // paycheck here
	outFile << endl; 
	outFile << "Distance traveled : " << distance << " miles , " << "Traveling time : " << time << " hours " << endl;
	avgSpeed = distance / time;
	outFile << "Average Speed : "<< avgSpeed << " miles per hour" << endl;  // speed here
	outFile << endl; 
	outFile << "Number of Coffee Cups Sold : " << c_cup << "," << " Cost : $" << cost << " per cup " << endl;
	salesAmt = c_cup * cost;
	outFile << "Sales Amount = $"<< salesAmt << endl; // sales here
	
	inFile.close();
	outFile.close(); // Part E
	return 0; // Part F
}