// Lab 1 Question 2 Programmed by Caleb Latimer
#include <iostream>
using namespace std; // Calling Libraries here

int main()
{
	double frame_length , frame_width; 
	double wire_length; // setting variable names 

	
	cout << "What is the wire length? " << endl;
	cin >>  wire_length; // user sets wire length which is equal to the perimeter of the frame 
    cout << "The length of the wire is " << wire_length << endl;

	frame_width = wire_length / 5;
	frame_length = 1.5 * frame_width; // math required to find values needed

	
	cout << "The length by width of the frame is " << frame_length << " by " <<  frame_width << endl; // printing out the result 
	return 0;
}