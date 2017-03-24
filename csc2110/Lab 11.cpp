// Lab 11 programmed by Caleb Latimer
#include<iostream>
#include<string>
#include<iomanip>
using namespace std;
int main(){
	int size;
	cout << "How many candidates are there? :"; 
	cin >> size; // enter 5 
	string *name;
	name = new string[size];
	double *votes;
	votes = new double[size];
	int sum = 0;
	for (int i = 0; i < size; i++){
		cout << "What is the candidate name? : ";
		cin >> name[i];
		cout << "How many votes did they get? : ";
		cin >> votes[i];
	}
	string total = "Total";
	for (int i = 0; i < size; i++)
		sum += votes[i];
	double pct;
	double max = 0; 
	int maxposition;
	for (int i = 0; i < size; i++){
		pct = (votes[i] / sum) * 100;
		cout << name[i] << " " << votes[i] << " " << fixed << setprecision(2) << pct << endl;
		if (pct > max){
			maxposition = i;
			max = pct;
		}
	}
	cout << setw(3) << total << " " << sum << " " << " X" << endl;
	cout << "The winner is " << name[maxposition] << endl; 
	return 0; 

	
}