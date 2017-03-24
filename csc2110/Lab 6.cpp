// Lab 6 programmed by Caleb Latimer 
#include<iostream>
#include<string>
using namespace std;
class dayType{
public:
	dayType();
	dayType(int x);

	string setDay(int);
	void sayDay()const;
	string nextDay();
	string yesterDay();
	string makeDay(int x);
private:
	string theDay[7];
	string myDay;
	string newDay;

}myDay;

dayType::dayType(int x)
{
	theDay[0] = "Sunday";
	theDay[1] = "Monday";
	theDay[2] = "Tuesday";
	theDay[3] = "Wednesday";
	theDay[4] = "Thursday";
	theDay[5] = "Friday";
	theDay[6] = "Saturday";
	myDay = theDay[x];

}
dayType::dayType()
{
	theDay[0] = "Sunday";
	theDay[1] = "Monday";
	theDay[2] = "Tuesday";
	theDay[3] = "Wednesday";
	theDay[4] = "Thursday";
	theDay[5] = "Friday";
	theDay[6] = "Saturday";
	myDay = theDay[0];
}
string dayType::setDay(int y)
{
	myDay = theDay[y];
	cout << "The day you set was : " << myDay << endl;
	return theDay[y];
}
void dayType::sayDay()const
{
	cout << "The day is : " << myDay << endl;
}
string dayType::nextDay()
{
	if (myDay == "Sunday")
		myDay = "Monday";
	else if (myDay == "Monday")
		myDay = "Tuesday";
	else if (myDay == "Tuesday")
		myDay = "Wednesday";
	else if (myDay == "Wednesday")
		myDay = "Thursday";
	else if (myDay == "Thursday")
		myDay = "Friday";
	else if (myDay == "Friday")
		myDay = "Saturday";
	else if (myDay == "Saturday")
		myDay = "Sunday";
	cout << "The next day is :" << myDay << endl;
	return myDay;
}
string dayType::yesterDay()
{
	if (myDay == "Sunday")
		myDay = "Saturday";
	else if (myDay == "Monday")
		myDay = "Sunday";
	else if (myDay == "Tuesday")
		myDay = "Monday";
	else if (myDay == "Wednesday")
		myDay = "Tuesday";
	else if (myDay == "Thursday")
		myDay = "Wednesday";
	else if (myDay == "Friday")
		myDay = "Thursday";
	else if (myDay == "Saturday")
		myDay = "Friday";
	cout << "Yesterday was : " << myDay << endl;
	return myDay;
}
string dayType::makeDay(int x){
	if (x > 6)
	x = x % 6;
	newDay = theDay[x];
	cout << "New day is :" << newDay << endl;
	return newDay;

}

int main()
{
	cout << "Hello" << endl;
	dayType myDay;
	myDay.setDay(2);
	myDay.sayDay();
	myDay.nextDay();
	myDay.yesterDay();
	myDay.makeDay(3);
	return 0;
}
