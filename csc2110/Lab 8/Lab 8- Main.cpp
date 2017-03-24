// Lab 8 programmed by Caleb Latimer 
#include<iostream>
#include "extClockType.h"
#include"clockType.h"

using namespace std;
int main()
{
	int x = 5, y = 15, z = 35;
	clockType myClock(x,y,z);
	extClockType superClock("Detroit Time");
	myClock.printTime();
	superClock.printzone();

	superClock.changezone("E.S.T");
	myClock.setTime(x,y,z);
	myClock.printTime();
	superClock.printzone();

	system("Pause");

}
