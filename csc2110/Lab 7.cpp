// Lab 7 written by Caleb Latimer 
#include<iostream>
using namespace std;
class swimmingPool{
public:
	swimmingPool();
	swimmingPool(double, double, double, double, double, double, double);

	double setVolume();
	double neededTillFull();
	void RateSpec(double);
	
private:
	double length; // in feet
	double width; // *
	double depth; // *
	double volume; // will be in cubic feet ,gallons in cubic feet is 7.48 
	double fillRate; // gallons per minute
	double leakRate; // gpm 
	double waterLevel; // current level of water in pool will change depending on constructor
	double maxLevel;// can be =total capacity or <
	double drainTime(double &b);
};
swimmingPool::swimmingPool() // basic constructor everything is 1
{
	length = 1;
	width = 1;
	depth = 1;
	fillRate = 1;
	fillRate = 1;
	leakRate = 1;
	waterLevel = 1;
}
swimmingPool::swimmingPool(double a, double b, double c, double d, double e, double f, double g)// 2nd constructor everything is set to whatever goes into this
{
	length = a;
	width = b;
	depth = c;
	fillRate = d;
	fillRate = e;
	leakRate = f;
	waterLevel = g;

}
double swimmingPool::setVolume(){ // we have volume
	volume = length * width * depth;
	return volume; 
}
double swimmingPool::neededTillFull(){// determines the amount needed to be full 
	maxLevel = volume * 7.48;
	if (waterLevel == 0){
		cout << "The amount of water you need to fill up the pool is : " << maxLevel << endl;
	}
	else{
		maxLevel -= waterLevel;
		cout << "You had some water! The amount of water you need to fill up the pool is : " << maxLevel << endl;
	}
	return maxLevel;
}
double swimmingPool::drainTime(double &b){ // takes from time spec the rate entered from reference and finds total time needed based off rate
	int j;
	double totalTime;
	cout << "Adding or draining? (1 or 2)";
	cin >> j;
	switch (j){
case 1: 
		fillRate = b;
		totalTime = maxLevel / b;
		cout << "The total time needed to fill is : " << totalTime << endl;
		break;
		return fillRate;
case 2: 
		leakRate = b;
		totalTime = maxLevel / b;
		cout << "The total time needed to drain is : " << totalTime << endl;
		break;
		return leakRate;
default: cout << "Exiting drainTime" << endl;
	break;
	return 0;
	}

}
void swimmingPool::RateSpec(double b){// sets rate and calls drainTime
	drainTime(b);
}
int main()
{
	swimmingPool hotTub(10,20,30,40,50,60,70);
	hotTub.setVolume();
	hotTub.neededTillFull();
	hotTub.RateSpec(2.0);
	return 0; 
}