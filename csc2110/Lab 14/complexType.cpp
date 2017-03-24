   
//Implementation file complexType.cpp

#include <iostream>
#include<iomanip>
#include "complexType.h" 
 
using namespace std;

void complexType::printComplex()const
{
	cout << "The real part is : " << fixed << showpoint << setprecision(2) << realPart << endl;
	cout << "The imaginary part is : " << fixed << showpoint << setprecision(2) << imaginaryPart << endl;

}
ostream& operator<< (ostream& os, const complexType& complex)
{
	os << "(" << complex.realPart << ", "
	   << complex.imaginaryPart << ")";
	return os;
}

istream& operator>> (istream& is, complexType& complex)
{
	char ch;

	is >> ch;                     //read and discard (
	is >> complex.realPart;       //get the real part
	is >> ch;                     //read and discard,
	is >> complex.imaginaryPart;  //get the imaginary part
	is >> ch;                     //read and discard)

	return is;
}

bool complexType::operator==(const complexType& otherComplex) const
{
	return(realPart == otherComplex.realPart && 
		   imaginaryPart == otherComplex.imaginaryPart);
}

  //constructor
complexType::complexType(double real, double imag)
{
	realPart = real;
	imaginaryPart = imag;
}

void complexType::setComplex(const double& real, const double& imag)
{
	realPart = real;
	imaginaryPart = imag;
}

void complexType::getComplex(double& real, double& imag) const
{
    real = realPart;
    imag = imaginaryPart;
}

   //overload the operator +
complexType complexType::operator+(const complexType& otherComplex) const
{
	complexType temp;

	temp.realPart = realPart + otherComplex.realPart;
	temp.imaginaryPart = imaginaryPart + otherComplex.imaginaryPart;

	return temp;
}

   //overload the operator *
complexType complexType::operator*(const complexType& otherComplex) const
{
	complexType temp;

	temp.realPart = (realPart * otherComplex.realPart) -
                    (imaginaryPart*otherComplex.imaginaryPart);
	temp.imaginaryPart = (realPart * otherComplex.imaginaryPart) +
                      (imaginaryPart * otherComplex.realPart);
	return temp;
}

 //overload the operator -
complexType complexType::operator - (const complexType & other) const
{ 
	complexType copy;
	copy.realPart = realPart - other.realPart;
	copy.imaginaryPart = imaginaryPart - other.imaginaryPart;
	return copy;
}

complexType complexType :: operator / (const complexType & otherComplex) const
{ 
	complexType copy;
	// add imaginary divison here, add the division function
	copy.realPart = ((realPart*otherComplex.realPart) + (imaginaryPart*otherComplex.imaginaryPart)) / (pow(otherComplex.realPart,2) + pow(otherComplex.imaginaryPart,2));
	copy.imaginaryPart = ((-realPart * otherComplex.imaginaryPart) + (imaginaryPart*otherComplex.realPart)) / (pow(otherComplex.realPart,2) + pow(otherComplex.imaginaryPart,2));
	return copy;
}
 //overload the operator /


