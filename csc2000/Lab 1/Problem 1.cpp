// Question 1 Programmed by Caleb Latimer
#include <iostream>
#include <cmath>
using namespace std;

int main()
{
	float bag_amt, num_of_bags;
	float m_ton = 2205; // Declaring vars 

	cout << "Enter the weight of your bag \n"; // Prompting user to enter bag amount 
	cin >> bag_amt;
    cout << "The amount you entered is " << bag_amt << " lbs \n";

	num_of_bags = ceil(m_ton / bag_amt); // Math for number in tons, using ceil() to take the highest possible value  
	cout << "The amount of rice that makes a metric ton according to your bag is " << num_of_bags << endl; // Output answer 

    return 0;

}

