// Problem 5 programmed by Caleb Latimer 
#include<iostream>
using namespace std;
bool FindtheCoprime(int &a, int &b)
{
	int gcd = 1; 
	int max =0;
	bool coprime = false;
	int track = 0;

	if (max < a)
		max = a;
	if (max < b)
		max = b; 
	while (gcd <= max){
		if ((a%gcd == 0) && (b%gcd == 0)){
			cout << "This is a gcd " << gcd << endl;
			track++;
		}
		gcd++;
	}

	if (track > 1)
		coprime = false;
	else
		coprime = true;
	return coprime;

}
int main(){
	int a, b;
	bool ans;
	cout << "Enter two integers : ";
	cin >> a >> b;
	
	if ((a > 0) && (b > 0))
		ans = FindtheCoprime(a, b);
	else{
		while ((a <= 0) || (b <= 0))
		{
			cout << "Your inputs are invalid, put in numbers greater than 0 : ";
			cin >> a >> b;
		}
		ans = FindtheCoprime(a, b);
	}

	cout << "The result is : ";
	if (ans == true)
		cout << "CO-PRIME" << endl;
	else
		cout << "NOT CO-PRIME" << endl; 
	return 0; 
}