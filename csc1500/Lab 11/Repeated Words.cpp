// Repeated words lab 11 problem 4 programmed by Caleb Latimer
#include<iostream>
#include<string>
#include<sstream>
#include<cstdlib>
#include<map>
using namespace std;
int main()
{
	/*	string input = "Hello hello hello Hello";

		vector<pair<string, int>> wordCount;

		for (string::size_type p = 0; p < input.size(); )
		{
			const auto p2 = input.find_first_of(' ', p);

			const auto word = input.substr(p, (p == string::npos) ? string::npos : (p2 - p));

			if (wordCount.empty() || wordCount.back().first != word)
				wordCount.push_back(make_pair(word, 1));
			else
				++wordCount.back().second;

			if (p2 == string::npos)
				break;

			p = p2 + 1;
		}

		for (const auto& it : wordCount)
			if (it.second > 1)
				std::cout << it.first << " " << it.second << std::endl;


		return 0;
	*/
	string input; // user input
	cout << "Input a string : ";
	getline(cin, input); // populates input
	istringstream iss(input); // makes input an input stream which holds the user input in it's buffer
	map<string, size_t> m; // creates a map of two types string which is the key and size_t which is the length of the string and the value
	string temp; // temp string
	while (iss >> temp) // reads from the buffer into the temp string by string
	{
		auto it = m.find(temp); // check if it is in the map 
		if (it != end(m))
		{
			++(it->second); // if it is increment value
		}
		else
		{
			m.insert(make_pair(temp, 0)); // if not put it in and match it's value with 0
		}
	}

	//display counts as:
	for (auto it = begin(m); it != end(m); ++it)
	{
		std::cout << it->first << " was duplicated " << it->second << " times" << std::endl; 
	}
	return 0;
}




//#include<iostream>
//#include<string>
//#include<vector>
//using namespace std;
//vector <string> mystring;
//int numberString(string const&in)
//{
//	int total = 0;
//	char temp;
//	for (unsigned i = 0; i < in.length(); i++)
//	{
//		temp = in[i];
//		if (temp == ' ')
//			total++;
//	}
//	total++;
//	return total;
//}
//void findRepeats(string const &in)
//{
//	int numberOfStrings = numberString(in);
//	//int size = in.length();
//	int *wordArray;
//	wordArray = new int[numberOfStrings];
//	for (int i = 0; i < numberOfStrings; i++)
//		wordArray[i] = 0;
//	int counter = 0;
//	string temp = in;
//	int substart = 0;
//	for (int j = 0; j < numberOfStrings;j++)
//	{
//		unsigned static i = 0;
//		for (i; i < in.length(); i++)
//		{
//			if (in[i] == ' ')
//			{
//				temp = in.substr(substart,(i));
//				substart = i + 1;
//				i++;
//				break;
//			}
//		}
//		if ((find(mystring.begin(), mystring.end(), temp) == mystring.end()))
//		{
//			mystring.push_back(temp);
//			wordArray[counter]++;
//		}
//		else
//		{
//			wordArray[counter]++;
//		}
//		counter++;
//	}
//	for (int j = 0; j < numberOfStrings; j++)
//	{
//		if (wordArray[j] > 1)
//			cout << mystring[j] << " : " << wordArray[j] << endl;
//	}
//}
//int main()
//{
//	string input;
//	cout << "Enter a string : ";
//	getline(cin, input);
//	findRepeats(input);
//	return 0; 
//}
