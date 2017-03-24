// Lab 12 programmed by Caleb Latimer
// 7 files needed in solution 
#include<iostream>
#include"Rectangle.h"
#include"Triangle.h"
int main(){
	Triangle tri; 
	tri.draw();
	cout << "\n In main, Derived class Triangle object calling" << " center().\n";
	tri.center();
	Rectangle rect;
	rect.draw();
	cout << "\nIn main, Derived class Rectangle object calling" << "center().\n";
	rect.center();
	return 0; 
}
// explanation of the difference....
// In main without virtual functions when .center is called main will reference the code inside of the base class and call the base erase() and draw() functions, since center is a part of the base class only.
// With the virtual functions .center calls the base for the first line but then calls objects own class (the derived class) when the erase() and draw() functions are called
// The reason why they are not ignored again is because of the virtual being called in the base class 
// When a function is made virtual it enables that function to be overwritten by another function in a derived class with the same signature(name, return type, parameters) 
// Since all the functions in our code have the same type(void) and take no parameters and return nothing they can be overwritten easily
// when a function is made virtual in the base class it allows that function to call the derived classes version of it 
// So when ran with virtual functions it prints the first statement in the base class but when erase() and draw() are called then they are calling to the derived versions and not the base versions
