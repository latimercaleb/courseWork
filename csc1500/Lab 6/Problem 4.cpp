// Problem 4 programmed by Caleb Latimer 
#include<iostream>
using namespace std;
int main(){
	int a, b;
	cout << "Enter two integers : ";
	cin >> a >> b;
	int biggest;
	if (a > b)
		biggest = a;
	else
		biggest = b;
	do{
		if (biggest %a == 0 && biggest %b == 0){
			cout << "LCM of " << a << " and " << b << " is " << biggest << endl;
			break;
		}
		else
			biggest++;
	} while (true);


}