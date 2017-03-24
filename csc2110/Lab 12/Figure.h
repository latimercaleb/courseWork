// Base Class 
#ifndef Fig // macro cannot be used with class name 
#define Fig
#include<iostream>
using namespace std; 

class Figure{
public:
	  void erase();
	  void draw();
	  void center();
	/*virtual void erase();
	virtual void draw();
	virtual void center();*/
};
#endif