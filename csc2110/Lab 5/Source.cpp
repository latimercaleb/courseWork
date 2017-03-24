// Lab 5 programmed by Caleb Latimer
#include<iostream>
using namespace std;
class Circle{ // Class circle
private:
	double radius;
public: // functions are public to be accessed in main()
		void setRadius();
		void getArea();
}sphere; // instance of class circle called sphere
void Circle::setRadius() // :: used to define the function outside of the class
{
	cout << "Enter a value for a circle" << endl;
	cin >> radius;
}
void Circle::getArea(){
	cout << "The computed area is : ";
	double const Pi = 3.14; 
	double area = (Pi*pow(radius,2)); 
	cout << area;
	cout << endl; 
	 
}

int main()
{
	sphere.setRadius();
	sphere.getArea();
	
}