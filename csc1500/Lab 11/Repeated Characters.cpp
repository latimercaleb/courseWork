// Repeated Characters Problem 3 Lab 11
#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
using namespace std;
vector <char> alreadyprintedcharacters;
void findrepeats(string const&);
int main()
{
	string input;
	cout << "Enter the input : ";
	getline(cin, input);
	findrepeats(input);
	return 0;
}
void findrepeats(string const &in)
{
	int trackerOfDuplicates = 0; 
	int asciiArray[256];
	char ch;
	int charconv;
	for (int i = 0; i < 256; i++) // creates my refference array for the comparison and sets all the values equal to zero
		asciiArray[i] = 0;
	for (unsigned int i = 0; i < in.length(); i++)
	{
		ch = in[i];
		charconv = static_cast<int>(ch);
		asciiArray[charconv]++;
		/*if (asciiArray[charconv] == 0)
		{
			asciiArray[charconv] = 1;
		}
		else if (asciiArray[charconv] > 0)
		{
			asciiArray[charconv] = asciiArray[charconv]++;
		}*/
		
	}
	bool trip = false;
	for (unsigned int i = 0; i < in.length(); i++)
	{
		char static alreadyprinted;
		char ch = in[i];
		
		if ((asciiArray[ch] > 1) && (ch != alreadyprinted) && (find(alreadyprintedcharacters.begin(), alreadyprintedcharacters.end(), ch)== alreadyprintedcharacters.end()))
		{
			cout << in[i] << " : " << asciiArray[ch] << endl;
			trip = true;
			alreadyprinted = ch;
			alreadyprintedcharacters.push_back(alreadyprinted);
		}
		
			
		

	}
	if (trip == false)
		cout << "No repeated characters were found.\n";
}