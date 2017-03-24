// Undirected Graph
// Problem 2 of lab 12 programmed by Caleb Latimer
#include<iostream>
#include <climits>
#include <iomanip>
using namespace std;
void initializeMatrix(int graph[][9])
{
	graph[0][0] = INT_MAX; // this space is not used otherwise B-B connection does not exist and there is significant overlap
				  
	graph[0][1] = INT_MAX;
	graph[0][2] = INT_MAX;
	graph[0][3] = INT_MAX;
	graph[0][4] = INT_MAX;
	graph[0][5] = INT_MAX;
	graph[0][6] = INT_MAX;
	graph[0][7] = INT_MAX;
	graph[0][8] = INT_MAX;
				  
	graph[1][0] = INT_MAX;
	graph[2][0] = INT_MAX;
	graph[3][0] = INT_MAX;
	graph[4][0] = INT_MAX;
	graph[5][0] = INT_MAX;
	graph[6][0] = INT_MAX;
	graph[7][0] = INT_MAX;
	graph[8][0] = INT_MAX;

	// initialize these to proper values according to the specs, column 1
	graph[1][1] = 0;
	graph[2][1] = 0;
	graph[3][1] = 0;
	graph[4][1] = 0;
	graph[5][1] = 0;
	graph[6][1] = 595;
	graph[7][1] = 760;
	graph[8][1] = 0;

	// column 2	  0
	graph[1][2] = 0;
	graph[2][2] = 0;
	graph[3][2] = 0;
	graph[4][2] = 0;
	graph[5][2] = 0;
	graph[6][2] = 0;
	graph[7][2] = 191;
	graph[8][2] = 0;

	// column 3	  0
	graph[1][3] = 606;
	graph[2][3] = 860;
	graph[3][3] = 0;
	graph[4][3] = 908;
	graph[5][3] = 0;
	graph[6][3] = 0;
	graph[7][3] = 722;
	graph[8][3] = 1855;

	// column 4	  0
	graph[1][4] = 0;
	graph[2][4] = 0;
	graph[3][4] = 0;
	graph[4][4] = 0;
	graph[5][4] = 834;
	graph[6][4] = 0;
	graph[7][4] = 0;
	graph[8][4] = 957;

	// column 5	  0
	graph[1][5] = 0;
	graph[2][5] = 0;
	graph[3][5] = 0;
	graph[4][5] = 0;
	graph[5][5] = 0;
	graph[6][5] = 0;
	graph[7][5] = 2451;
	graph[8][5] = 349;

	//column 6	  0
	graph[1][6] = 0;
	graph[2][6] = 0;
	graph[3][6] = 0;
	graph[4][6] = 0;
	graph[5][6] = 0;
	graph[6][6] = 0;
	graph[7][6] = 0;
	graph[8][6] = 0;

	// column 7	  0
	graph[1][7] = 0;
	graph[2][7] = 0;
	graph[3][7] = 0;
	graph[4][7] = 0;
	graph[5][7] = 0;
	graph[6][7] = 1090;
	graph[7][7] = 0;
	graph[8][7] = 0;
	
	//column 8 
	graph[1][8] = 0;
	graph[2][8] = 0;
	graph[3][8] = 0;
	graph[4][8] = 0;
	graph[5][8] = 349;
	graph[6][8] = 0;
	graph[7][8] = 254;
	graph[8][8] = 0;
} 
// Function to initialize
void showMatrix(int array[][9])
{
	cout << "The matrix is as follows : " << endl;
	char cityName[9] = { ' ','A','B','C','D','L','M','N','S' };
	for (int i = 0; i <9; i++)
	{
		if (array[i][0] == INT_MAX)
			cout <<cityName[i] << " ";
		for (int j = 1; j < 9; j++)
		{
			if (array[i][j] == INT_MAX)
				cout<<setw(3) << cityName[j] << " ";
			else
			cout << setw(3) <<array[i][j] << " ";
		}
		cout << endl;
	}
}
// Print matrix 
void addConnection(int graph[][9])
{
	cout << "You have chosen to connect two of the cities! \n";
	char firstCity, secondCity;
	cout << "Select the first vertex (the first letter of the city) : ";
	cin >> firstCity;
	firstCity = toupper(firstCity);
	cout << "Select the second vertex (the first letter of the city) : ";
	cin >> secondCity;
	secondCity = toupper(secondCity);
	int coordinate1, coordinate2;
	bool passed = false;
	while (passed != true)
	{
		passed = true;
		switch (firstCity)
		{
		case 'A': coordinate1 = 1;
			break;
		case 'B': coordinate1 = 2;
			break;
		case 'C': coordinate1 = 3;
			break;
		case 'D': coordinate1 = 4;
			break;
		case 'L': coordinate1 = 5;
			break;
		case 'M': coordinate1 = 6;
			break;
		case 'N': coordinate1 = 7;
			break;
		case 'S': coordinate1 = 8;
			break;
		default: 
			passed = false;
			cout << "Invalid selection, pick a proper source city : ";
			cin >> firstCity;
		}
	}
	bool passed2 = false;
	while (passed2 != true)
	{
		passed2 = true;
		switch (secondCity)
		{
		case 'A': coordinate2 = 1;
			break;
		case 'B': coordinate2 = 2;
			break;
		case 'C': coordinate2 = 3;
			break;
		case 'D': coordinate2 = 4;
			break;
		case 'L': coordinate2 = 5;
			break;
		case 'M': coordinate2 = 6;
			break;
		case 'N': coordinate2 = 7;
			break;
		case 'S': coordinate2 = 8;
			break;
		default: 
			passed2 = false;
			cout << "Invalid selection, pick a proper destination city : ";
			cin >> firstCity;
		}
	}
	int valueOnEdge;
	cout << "Enter the value of the edge : ";
	cin >> valueOnEdge;
	while (cin.fail())
	{
		cin.clear();
		cout << "Input error input an integer ";
		cin >> valueOnEdge;
	}
	if (graph[coordinate1][coordinate2] > 0)
		cout << "Connection already exists between " << firstCity << " & " << secondCity<< endl;
	else
	{
		graph[coordinate1][coordinate2] = valueOnEdge;
		if((coordinate1 ==5 && coordinate2 ==8 ) || (coordinate1 ==8 && coordinate2 ==5 ))
			graph[coordinate2][coordinate1] = valueOnEdge;

		cout << "New connection made between " << firstCity << " & " << secondCity << endl;
	}
}
// add a connection to the matrix
void deleteConnection(int graph[][9])
{
	cout << "You have chosen to delete a connection between the two of the cities! \n";
	char firstCity, secondCity;
	cout << "Select the first vertex (the first letter of the city) : ";
	cin >> firstCity;
	firstCity = toupper(firstCity);
	cout << "Select the second vertex (the first letter of the city) : ";
	cin >> secondCity;
	secondCity = toupper(secondCity);
	int coordinate1, coordinate2;
	bool passed = false;
	while (passed != true)
	{
		passed = true;
		switch (firstCity)
		{
		case 'A': coordinate1 = 1;
			break;
		case 'B': coordinate1 = 2;
			break;
		case 'C': coordinate1 = 3;
			break;
		case 'D': coordinate1 = 4;
			break;
		case 'L': coordinate1 = 5;
			break;
		case 'M': coordinate1 = 6;
			break;
		case 'N': coordinate1 = 7;
			break;
		case 'S': coordinate1 = 8;
		default:
			passed = false;
			cout << "Invalid selection, pick a proper source city : ";
			cin >> firstCity;
		}
	}
	bool passed2 = false;
	while (passed2 != true)
	{
		passed2 = true;
		switch (secondCity)
		{
		case 'A': coordinate2 = 1;
			break;
		case 'B': coordinate2 = 2;
			break;
		case 'C': coordinate2 = 3;
			break;
		case 'D': coordinate2 = 4;
			break;
		case 'L': coordinate2 = 5;
			break;
		case 'M': coordinate2 = 6;
			break;
		case 'N': coordinate2 = 7;
			break;
		case 'S': coordinate2 = 8;
			break;
		default:
			passed2 = false;
			cout << "Invalid selection, pick a proper destination city : ";
			cin >> firstCity;
		}
	}
	if (graph[coordinate1][coordinate2] == 0)
		cout << "No connection exists between " << firstCity << " & " << secondCity << endl;
	else
	{
		graph[coordinate1][coordinate2] = 0;
		if ((coordinate1 == 5 && coordinate2 == 8) || (coordinate1 == 8 && coordinate2 == 5))
			graph[coordinate2][coordinate1] = 0;
		cout << "Connection at " << firstCity << " & " << secondCity << " deleted." << endl;
	}
}
// delete a connection from the matrix
void showConnection(int graph[][9])
{
	int counter = 0;
	for (int i = 1; i < 9; i++)
	{
		for (int j = 1; j < 9; j++)
		{
			if (graph[i][j] >0)
				counter++;
		}
	}
	cout << "The total number of connections is : " << counter << endl;
}
// show the connection of a matrix 
void menu(int graph[][9])
{
	bool run = true;
	while (run == true)
	{
		int menuChoice;
		cout << "Welcome to the menu" << endl;
		cout << "Pick one of the following" << endl;
		cout << "1. add connection" << endl;
		cout << "2. delete connection " << endl;
		cout << "3. show total number of connections " << endl;
		cout << "4. show matrix " << endl;
		cout << "Selection : ";
		cin >> menuChoice;
		if (cin.fail())
		{
			cout << "Improper character input " << endl;
			cout << "Exiting ...\n";
			run = false;
			break;
		}
		switch (menuChoice)
		{
		case 1: addConnection(graph);
			break;
		case 2: deleteConnection(graph);
			break;
		case 3: showConnection(graph);
			break;
		case 4: showMatrix(graph);
			break;
		default:
			cout << "Improper input " << endl;
			cout << "Exiting ...\n";
			run = false;
			break;
		}
	}
}
// the menu function
int main()
{
	int connections[9][9];
	initializeMatrix(connections);// to set the original values from the drawing 
	showMatrix(connections); // views changes 
	menu(connections);
	return 0;
}
// Main Function