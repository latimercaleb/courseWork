// Program 4 of lab 5 built by Caleb Latimer
#include<iostream>
#include<fstream> 
//#include<set> not needed 
using namespace std;
int main(){
	int o = 0;
	int x;
	int *mine;
	mine = new int[1000]; // from problem 1 
	ifstream doc;
	doc.open("A2Output.txt");
	while (!doc.eof()){
		doc >> mine[o];
		o++;
	}
	cout << "Enter a number you want to search for : \n";
	cin >> x; // trigger flag 
	int i = 0;
	int j = 999; // size - 1
	int mid;// midpoint
	int spot; // if x is found 
	int next; // stores next index to the left and right of x 
	while (i < j){
		mid = floor((i + j) / 2);
		if (x > mine[mid])
			i = mid + 1;
		else
			j = mid;
	}
	if (x == mine[i]){
	spot = i; // meaning x is found at i 
	}
	else
		spot = 1001;// arbitrary number for some reason use of NULL here gave me a ton of issues so I entered a random number 

	if (spot == 1001)
		cout << "The number you input cannot be found in the array\n"; // failed to find message triggered by spot becoming random number
	else{
		cout << "Tag! The number was found\n" << "The number is at index " << spot << endl;
		int sniff = 1;// detects one space ahead or behind spot for an equal value
		while (mine[spot] == mine[spot + sniff])// keeps grabbing indexes until condition is broken 
		{
			next = spot + sniff;
			cout << "And also :\n" << next << endl;
			sniff++;
		}
		sniff = 1; // reinitializes back to 1 and then tries to find area before spot 
		while (mine[spot] == mine[spot - sniff])
		{
			next = spot + sniff;
			cout << "And also :\n" << next << endl;
			sniff++;
		}
	}

}