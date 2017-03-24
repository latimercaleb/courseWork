// Dijkstra's greedy algorithm by Caleb Latimer
#include<iostream>
#include<vector>
#include<climits>
#define SIZE 10
using namespace std;

void showmap(int map[][SIZE])
{
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
			cout << map[i][j] << " ";
		cout << endl;
	}
}
// Test function to show the 2D matrix after initialization
void initializeMatrix(int graph[][SIZE])
{
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			graph[i][j] = 0;
		}
	}
	graph[0][4] = 1;
	graph[0][7] = 10;
	graph[1][2] = 2;
	graph[3][0] = 4;
	graph[3][7] = 1;
	graph[4][5] = 3;
	graph[5][1] = 1;
	graph[5][2] = 3;
	graph[5][6] = 7;
	graph[5][8] = 1;
	graph[7][4] = 5;
	graph[7][8] = 9;
	graph[8][9] = 2;
	graph[9][6] = 1;
	//showmap(graph); // For viewing correct matrix setup
}
// Function to populate the 2D matrix with initial connections
int findTheSmallest(int L[], bool done[])
{
	int smallestIndex, smallestIndexValue = INT_MAX;
	for (int i = 0; i < SIZE; i++)
	{
		if ((done[i] == false) && L[i] <= smallestIndexValue)
		{
			smallestIndexValue = L[i];
			smallestIndex = i;
		}
	}
	return smallestIndex;
}
// Function to loop through the array and return the smallest index found 
void djik(int map[SIZE][SIZE], int sourcenode)
{
	int routeToG[6];
	for (int i = 0; i < 6; i++)
		routeToG[i] = 0;
	int stopG = 0;
	int a = sourcenode;
	int list[SIZE];
	bool visited[SIZE];
	for (int i = 0; i < SIZE; i++)
	{
		list[i] = INT_MAX;
		visited[i] = false;
	}
	list[a] = 0;// since d is source 
	for (int i = 0; i < SIZE-1; i++)
	{
		int u = findTheSmallest(list, visited);
		visited[u] = true;
		if ((visited[6] == false) && (stopG!=6))
		{
			routeToG[i] = u;
			stopG++;
		}
		for (int j = 0; j < SIZE; j++)
		{
				if((visited[j] == false)  && (list[u] + map[u][j] < list[j]) && (map[u][j] !=0))
					list[j] = list[u] + map[u][j];
		}
	}
	char charArray[10] = { 'A','B','C','D','E','F','G','H','I','J' };
	cout << "dijk's result!\n";
	for (int k = 0; k < SIZE; k++)
		cout << "D to "<< charArray[k] << " " << list[k] << endl;
	cout << "The shortest distance between D & G is : ";
	for (int i = 0; i < 6; i++)
	{
		bool exit = false;
		int temp = routeToG[i];
		switch (temp)
		{
		case 3: cout << charArray[7] << " to ";
			break;
		case 7: cout << charArray[4] << " to ";
			break;
		case 0: cout << charArray[5] << " to ";
			break;
		case 4: cout << charArray[8] << " to ";
			break;
		case 5: cout << charArray[9] << " to ";
			break;
		case 8: cout << charArray[6] <<  endl;
			bool exit = true;
			break;
		}
		if (exit == true)
			break;
	}
} 
// the algorithm to find the shortest distance and shortest path
int main()
{
	int map[SIZE][SIZE];
	initializeMatrix(map);// to set the original values from the drawing 
	djik(map,3); 
	return 0;
}
// Main function 
