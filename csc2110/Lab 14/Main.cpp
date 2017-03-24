// Lab 14 by Caleb Latimer
// overload addition,subtraction,multiplication and division check 13-1,13-5,13-7 for examples
#include<iostream>
#include"complexType.h"
#include<iomanip>
int main(){
	complexType mynum, myothernum;
	int a = 2, b = 3, c = 4, d = 5;
	mynum.setComplex(4,5);
	myothernum.setComplex(a,b);
	mynum.printComplex();
	myothernum.printComplex();

	cout << "To demonstrate overloads : \n";
	cout << mynum << endl;
	cout << myothernum << endl; 


	cout << (mynum + myothernum) << endl;
	cout << (mynum - myothernum) << endl;
	cout << (mynum * myothernum) << endl;
	cout << (mynum / myothernum) << endl;
	cout << (mynum == myothernum) << endl;





	return 0; 
}