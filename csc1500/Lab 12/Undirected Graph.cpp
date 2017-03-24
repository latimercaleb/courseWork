#include<iostream>
using namespace std;
void initializeMatrix(char graph[][8])
{
	graph[0][0] = NULL; // this space is not used otherwise B-B connection does not exist and there is significant overlap
	graph[0][1] = 'B';
	graph[0][2] = 'C';
	graph[0][3] = 'D';
	graph[0][4] = 'L';
	graph[0][5] = 'N';
	graph[0][6] = 'S';
	graph[0][7] = 'W';
	graph[1][0] = 'B';
	graph[2][0] = 'C';
	graph[3][0] = 'D';
	graph[4][0] = 'L';
	graph[5][0] = 'N';
	graph[6][0] = 'S';
	graph[7][0] = 'W';
	graph[0][1] = 'B';
	graph[0][2] = 'C';
	graph[0][3] = 'D';
	graph[0][4] = 'L';
	graph[0][5] = 'N';
	graph[0][6] = 'S';
	graph[0][7] = 'W';
	// initialize these to proper values according to the specs, column 1
	graph[1][1] = '0';
	graph[2][1] = '0';
	graph[3][1] = '0';
	graph[4][1] = '0';
	graph[5][1] = '1';
	graph[6][1] = '0';
	graph[7][1] = '0';
	// column 2
	graph[1][2] = '0';
	graph[2][2] = '0';
	graph[3][2] = '1';
	graph[4][2] = '1';
	graph[5][2] = '1';
	graph[6][2] = '0';
	graph[7][2] = '1';
	// column 3
	graph[1][3] = '0';
	graph[2][3] = '1';
	graph[3][3] = '0';
	graph[4][3] = '1';
	graph[5][3] = '0';
	graph[6][3] = '1';
	graph[7][3] = '0';
	// column 4
	graph[1][4] = '0';
	graph[2][4] = '0';
	graph[3][4] = '1';
	graph[4][4] = '0';
	graph[5][4] = '0';
	graph[6][4] = '1';
	graph[7][4] = '0';
	// column 5
	graph[1][5] = '1';
	graph[2][5] = '1';
	graph[3][5] = '0';
	graph[4][5] = '0';
	graph[5][5] = '0';
	graph[6][5] = '0';
	graph[7][5] = '1';
	//column 6
	graph[1][6] = '0';
	graph[2][6] = '0';
	graph[3][6] = '1';
	graph[4][6] = '1';
	graph[5][6] = '0';
	graph[6][6] = '0';
	graph[7][6] = '0';
	// column 7
	graph[1][7] = '0';
	graph[2][7] = '1';
	graph[3][7] = '0';
	graph[4][7] = '0';
	graph[5][7] = '1';
	graph[6][7] = '0';
	graph[7][7] = '0';
}
// function to initialize the values of a matrix 
void showMatrix(char array[][8])
{
	cout << "The matrix is as follows : " << endl;
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			cout << array[i][j] << " ";
		}
		cout << endl;
	}
}
// prints the matrix
void addConnection(char graph[][8])
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
		case 'B': coordinate1 = 1;
			break;
		case 'C': coordinate1 = 2;
			break;
		case 'D': coordinate1 = 3;
			break;
		case 'L': coordinate1 = 4;
			break;
		case 'N': coordinate1 = 5;
			break;
		case 'S': coordinate1 = 6;
			break;
		case 'W': coordinate1 = 7;
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
		case 'B': coordinate2 = 1;
			break;
		case 'C': coordinate2 = 2;
			break;
		case 'D': coordinate2 = 3;
			break;
		case 'L': coordinate2 = 4;
			break;
		case 'N': coordinate2 = 5;
			break;
		case 'S': coordinate2 = 6;
			break;
		case 'W': coordinate2 = 7;
			break;
		default:
			passed2 = false;
			cout << "Invalid selection, pick a proper destination city : ";
			cin >> firstCity;
		}
	}
	if (graph[coordinate1][coordinate2] == '1')
		cout << "Connection already exists between " << firstCity << " & " << secondCity << endl;
	else
	{
		graph[coordinate1][coordinate2] = '1';
		graph[coordinate2][coordinate1] = '0';
		cout << "New connection made between " << firstCity << " & " << secondCity << endl;
	}
}
// adds connections to the matrix
void deleteConnection(char graph[][8])
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
		case 'B': coordinate1 = 1;
			break;
		case 'C': coordinate1 = 2;
			break;
		case 'D': coordinate1 = 3;
			break;
		case 'L': coordinate1 = 4;
			break;
		case 'N': coordinate1 = 5;
			break;
		case 'S': coordinate1 = 6;
			break;
		case 'W': coordinate1 = 7;
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
		case 'B': coordinate2 = 1;
			break;
		case 'C': coordinate2 = 2;
			break;
		case 'D': coordinate2 = 3;
			break;
		case 'L': coordinate2 = 4;
			break;
		case 'N': coordinate2 = 5;
			break;
		case 'S': coordinate2 = 6;
			break;
		case 'W': coordinate2 = 7;
			break;
		default:
			passed2 = false;
			cout << "Invalid selection, pick a proper destination city : ";
			cin >> firstCity;
		}
	}
	if (graph[coordinate1][coordinate2] == '0')
		cout << "No connection exists between " << firstCity << " & " << secondCity << endl;
	else
	{
		graph[coordinate1][coordinate2] = '0';
		graph[coordinate2][coordinate1] = '0';
		cout << "Connection at " << firstCity << " & " << secondCity << " deleted." << endl;
	}
}
// removes connections from matrix
void showConnection(char graph[][8])
{
	int counter = 0;
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (graph[i][j] == '1')
				counter++;
		}
	}
	cout << "The total number of connections is : " << counter << endl;
}
// shows if there is a connection to a matrix
void menu(char graph[][8])
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
	char directedConnections[8][8];
	initializeMatrix(directedConnections);// to set the original values from the drawing 
	showMatrix(directedConnections); // views changes 
	menu(directedConnections);
	return 0;
}