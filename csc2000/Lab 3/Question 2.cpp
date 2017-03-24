// Question 2 programmed by Caleb Latimer

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
using namespace std; // Calling libraries 

int main()
{ 
	ifstream ifile;
	ofstream ofile;

	ifile.open("Data.txt");
	ofile.open("Output.txt");

	double new_sal, sal, raise;
	string L_name, F_name;


	ifile >> L_name >> F_name >> sal >> raise;

	new_sal = sal + (sal*(raise / 100));

	ofile << fixed << showpoint << setprecision(2); 

	ofile << F_name<< " " << L_name << ' ' <<  new_sal << endl;

	ifile >> L_name >> F_name >> sal >> raise;

	new_sal = sal + (sal*(raise / 100));

	ofile << fixed << showpoint << setprecision(2);

	ofile << F_name << " " << L_name << ' ' << new_sal << endl;

	ifile >> L_name >> F_name >> sal >> raise;

	new_sal = sal + (sal*(raise / 100));

	ofile << fixed << showpoint << setprecision(2);

	ofile << F_name << " " << L_name << ' ' << new_sal << endl;


	return 0; 
}