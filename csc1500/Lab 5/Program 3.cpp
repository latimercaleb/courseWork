// Program 3 of lab 5 built by Caleb Latimer
#include<iostream>
#include<fstream> 
#include<string>
using namespace std;

int main(){
	int q = 0; // counter needed
	int temp; 
	ifstream Doc;
	Doc.open("A1.txt");
	int *sort;
	sort = new int[1000]; // from problem 1

	while (!Doc.eof()){
		Doc >> sort[q];
		q++;
	}
	//cout << q << endl; 
	for (int i = 1; i < (q-1); i++){ // I already know there are 1000 inputs from previous code
		for (int j = 0; j < (q - i); j++){
			if (sort[j] < sort[j + 1]){ // this control block does the swap
				temp = sort[j];
				sort[j] = sort[j+1];
				sort[j + 1] = temp;
			}
			temp = 0;// reinitialize temp 

		}
	}

	for (int i = 0; i < q; i++)
		cout << sort[i]<< " "; // prints result to console 
	cout << endl;
	//system("pause");
}