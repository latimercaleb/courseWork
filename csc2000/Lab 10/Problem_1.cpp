// Lab 11 problem 1 programmed by Caleb Latimer

#include<iostream>
#include <cmath>
#include <iomanip>    // Included all libraries 

using namespace std;

const double PI = 3.1416;

double distance(double x, double x2, double y, double y2);
double radius(double c, double c2, double p, double p2);
double circumference(double radius);
double area(double radius);
double diameter(double radius); // All included function prototypes

int main()
{
	double c1, c2, p1, p2;
	cout << "Tell me your center and point coordinates." << endl;
	cin >> c1 >> c2 >> p1 >> p2;
	cout << fixed << showpoint << setprecision(3)<< setfill('*');
	cout << "The radius is : "<< setw(16) << radius(c1, c2, p1, p2) << endl; // Prompts user and gets all data 
	
	
	double q = radius(c1, c2, p1, p2);
	cout << "The diameter is : " <<  setw(14) << diameter(q) << endl;
	cout << "The circumference is : "  << setw(10) << circumference(q) << endl;
	cout << "The area is : " << setw(19) << area(q) << endl; // sets radius to Q and then uses that to pass value to remaining functions

	return 0;
}

double distance(double x, double x2, double y, double y2)
{
	double result, ans;
	ans = pow(x2 - x, 2) + pow(y2 - y, 2);
	result = ceil(sqrt(ans));

		return result;
}
double radius(double c, double c2, double p, double p2)
{
	double radius = distance(c, c2, p, p2);
	return radius;
}
double circumference(double radius)
{
	double circumference = 2 * PI*radius;
	return circumference;
}
double area(double radius)
{
	double area = pow(PI*radius, 2);
	return area;
}

double diameter(double radius)
{
	double diameter = 2 * radius;
	return diameter; 
}