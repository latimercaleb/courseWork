//  Problem for lab 12 programmed by Caleb Latimer
#include<iostream>
using namespace std;
void change(int a, int& hundreds, int& fifties, int& twenties, int& tens, int& fives, int& ones);

int main()
{
	int a = 2;
	cout << a % 100;
	/*int amount,hundreds,fifties,twenties,tens,fives,ones;
	cout << "Enter amount: ";
	cin >> amount; 
	change(amount,hundreds,fifties,twenties,tens,fives,ones);
	cout << hundreds << "- " <<  "hundreds" << endl;
	cout << fifties << "- " << "fifties" << endl;
	cout << twenties << "- " << "twenties" << endl;
	cout << tens << "- " << "tens" << endl;
	cout << fives << "- " << "fives" << endl;
	cout << ones << "- " << "ones" << endl;*/

}

void change(int a, int& hundreds, int& fifties, int& twenties, int& tens, int& fives, int& ones)
{
	hundreds = a / 100;
	a = a % 100; 
	

	fifties = a / 50;
	a = a % 50; 
	

	twenties = a / 20;
	a = a % 20;
	

	tens = a / 10; 
	a = a % 10;
	

	fives = a / 5;
	a = a % 5;
	
    ones = a / 1; 
	a = a % 1;
	
}