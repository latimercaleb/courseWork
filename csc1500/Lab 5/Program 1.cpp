// Program 1 of lab 5 built by Caleb Latimer
// find duplicates 
#include<iostream>
#include<fstream>
//#include<array> <- didn't need this 
#include<string>
//#include<vector> needed for vector method uncomment if used 
using namespace std;
int main(){
	////////////////////////////////////////////////ARRAY METHOD///////////////////////////////////////////////////
	int *a; // pointer to my dynamic array 
	a = new int[10000]; // makes array
	bool flag = false; // flag needed for later initialized to false because it being true will be the satisfied condition
	ifstream file;// name of doc in file
	file.open("A1.txt");
	for (int i = 0; i < 9999; i++)// sets array to negative 2 
		a[i] = -2;
	int g = 0;// this is counter of the number of inputs or the true size of the array
	while (!file.eof())
	{
		file >> a[g]; // overwrites inputs and puts in files from the array 
		g++;
	}
	cout <<" Total number of inputs : "<< g << endl; // we have 1000 inputs this information will be used in later problems
	cout << "Input the number that you want to look for must be greater than 0" << endl;
	int val; // this is the value I want to find
	cin >> val;
	while (val <= 0){ // check to rule out negative numbers 
		cout << "Invalid value input a number greater than or equal to 0\n";
		cin >> val; // forces user to enter 0 or a positive number
	}
	for (int i = 0; i < g; i++) // loop only goes through the numbers from the file and does not check the negative 2 
	{
		if (a[i] == val)
		{
			cout << "Found at " << i << endl; // prints found and index 
			flag = true;
			//break; // break is commented since we want all indexes, if we wanted one index or the first index I'd modify this statement
		}
	}

	if (flag == true)// message conditions 
		cout << "Your val was found!\n";
	else
		cout << "Your val was not found!\n";

	
	///////////////////////////////////////////// VECTOR METHOD////////////////////////////////////////////
//	string input; // string to hold all the data from the 
//	vector<int> mine; // struggled with trying to make a dynamic array since my index is unknown here the only type I found that works is a vector
//	//mine = new char[10];
//	int num; // this is the number we will look for
//	bool found = false; // flag that trips if the number we are looking for is found 
//	//int i = 0;
//	//char flag = " ";
//	string temp; // temporary string that will hold the value we want to put into the vector via pushback
//	ifstream myDoc("A1.txt");// text file is open if initialized this way proved with the commented test below 
//	//myDoc.open;
//	/*if (myDoc.is_open())
//	{
//		cout << "File is open";
//	}
//	else
//		cout << "File is closed"; // test to see if myDoc is open 
//*/
//	// make eof controlled loop into dynamic 
//	/*while (!myDoc.eof()){*/ // need to fix loop 
//		//getline(myDoc, mine[i]); // getline only works with type string and does not work because dynamic array goes out of bounds since my index is unknown
//		//myDoc >> mine[i];
//		getline(myDoc, input);// transforms text file into one string to read
//		//i++;
//		int pos = 0;// positon counter 
//		for (int x = 0; x <= input.size();x++)// size being an integer that is the size of the string
//		{
//			temp.push_back(input[x]);// inserts value into temp string feeding it data bit by bit
//
//			if (input[x]== ' ')// seeks whitespace
//			{
//				mine.push_back(stoi(temp));// pushes value to mine and converts it into int 
//				temp.clear();// clears temp so that temp can hold the next value 
//				pos++;// increments because position increased 
//			}
//			//pos++;// maybe it should increment here? test later
//		}
//
//		//cin.ignore();
//	//} // eof controlled while loop populates the dynamic array 
//	//cout << input; 
//	cout << "The total number of inputs was : " << pos << endl; // tells me the total number of inputs, read is gigantic for some reason...
//	cout << "Input the number that you want to find : "; // user prompt
//	cin >> num; // user input 
//	/*for (int y = 0; y < ; y++)
//	{
//		cout << mine[y] << endl;
//	}*/
//	
//	  // this is the value i need to locate
//	cout << "You selected : " << num << " it is located in the following positions\n";// header of answer 
//	for (int j = 0; j < mine.size(); j++){
//		if (mine[j] == num){
//			cout << num << "found at position " << j << endl; // outputs index of where location is found
//			found = true; // found becomes true 
//			break;// leaves loop since location was found 
//		}
//	}
//	if (found != true)
//		cout << "Your number: " << num << " is not available!" << endl;// executes only if bool is still false,  
//	
	file.close(); // closes text file now that it's job is done. 
	system("pause");// pause for debugging 
}