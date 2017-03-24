// Lab 15 programmed by Caleb Latimer
// At least one object needed
#include<iostream>
using namespace std;

class Digit{
public:
	Digit();
	Digit(int); // Constructors

	Digit operator++(); // Operator overloads
	Digit operator++(int);

	void SetDigit(int); // Other Functions
	int getNum();

private:
	int omega;
};
int main(){
	Digit test(0);
	cout << "Starting out my number is : " << test.getNum() << endl;
	cout << "Pre-increment : " <<(++test).getNum() << endl;
	cout << "After increment : " << test.getNum() << endl;
	test.SetDigit(0);
	cout << "Number is now reset to : " << test.getNum() << endl;
	cout << "Post increment : " << (test++).getNum() << endl;
	cout << "After increment : " << test.getNum() << endl;
	

	return 0;
}

Digit::Digit()
{
	omega = 0;
}

Digit::Digit(int x)
{
	omega = x;
}
Digit Digit::operator++()// Prefix ++
{
	omega++;
	return *this;
	
	//cout << "My prefix ++ is : "<< omega++ << endl;
}
Digit Digit::operator++(int)// Postfix ++
{
	Digit place;
	place.omega = omega;
	omega++;
	//cout << "My post fix ++ is : " <<  << endl; 
	return place;	
}

void Digit::SetDigit(int z){
	omega = z;
}

int Digit::getNum(){
	return omega;
}