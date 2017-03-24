// Lab 02 Programmed by Caleb Latimer

#include<iostream>
using namespace std;

int main()
{
	double perimeter, volume, underground_surface_area, length, width, average_depth, product_LW, sum_LW; // Declaring all vars as type double 
	
	cout << "Tell me the Length Width and Average Depth " << endl; // Prompt user 
	cin >> length >> width >> average_depth; // Get 3 measurements 
	product_LW = length * width;
	sum_LW = length + width; // immediately calculates product & sum after inputs 
	cout << length << " " << width <<" " << average_depth << " " << product_LW << " " << sum_LW << " "  << endl; // Shows 5 vars for clarity before further computations

	    perimeter = 2 * sum_LW;
	    volume = product_LW * average_depth;
		underground_surface_area = perimeter * average_depth + product_LW; // Finds last 3 vars 

		cout << "The perimeter is " << perimeter << endl;
	    cout << "The volume is " << volume << endl;
	    cout << "The underground_surface_area is " << underground_surface_area << endl; // Prints results 

	return 0; 
}