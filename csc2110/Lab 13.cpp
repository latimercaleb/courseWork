// Lab 13 programmed by Caleb Latimer
#include<iostream>
#include<string>
using namespace std;
void comma2blank(string my,string *r){
	for (int i = 0; i < my.length(); i++){
		
		if (my[i] == ',')
			my.replace(i, 1, " ");
	}
	//r = &my;
	
}
int main(){
	string myString;
	cout << "Enter a 10 char string with some commas : ";
	cin >> myString;
	string * result;
	//result = new string[myString.length()];
	result = &myString;
	comma2blank(myString, result);
	cout << "The switched string is " << endl;
	cout << *result << endl;

	return 0; 
}