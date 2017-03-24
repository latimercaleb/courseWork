// Lab 21 programmed by Caleb Latimer 
#include<iostream>
#include<vector>
using namespace std;
void print(const vector<int> &item)// Function to handle printing of the vector when appropriate
{
	cout << "Item : ";
	for (auto i : item)
		cout << i << " ";
	cout << endl;
}
void sequence(const vector<int>&item, int key)// function for a sequential search
{
	bool found = false;
	int index = 0;
	for (auto i : item)
	{
		if (i == key)
		{
			found = true;
			break;
		}
		index++;
	}
	if (found == true)
		cout << key << " found at index : " << index << endl;
	else
		cout << key << " was not in the item list\n";
	cout << endl;
}
void binsearch(const vector<int>&item, int key)// Function of a binary search
{
	bool found = false;
	size_t mid, left = 0;
	size_t right = item.size(); // one position passed the right end
	while (left < right) 
	{
		mid = left + (right - left) / 2;
		if (key > item[mid]) {
			left = mid + 1;
		}
		else if (key < item[mid]) {
			right = mid;
		}
		else {
			found = true;
			break;
		}
	}
	if (found == true)
		cout << key << " found at index : " << mid << endl;
	else
		cout << key << " was not in the item list\n";
	cout << endl;
}
void bubble(vector<int> &item)
{
		bool diditswitch = true;
		while (diditswitch) 
		{
			diditswitch= false;
			for (size_t i = 0; i < item.size()-1; i++) 
			{
				if (item[i]>item[i + 1]) 
				{
					item[i] += item[i + 1];
					item[i + 1] = item[i] - item[i + 1];
					item[i] -= item[i + 1];
					diditswitch = true;
				}
			}
		}
		cout << "After Bubble sorting, ";
		print(item);

}
void insertion(vector<int> &item)
{
	cout << "After insertion sorting, ";
	int j, temp;

	for (int i = 0; i < item.size(); i++) {
		j = i;

		while (j > 0 && item[j] < item[j - 1]) {
			temp = item[j];
			item[j] = item[j - 1];
			item[j - 1] = temp;
			j--;
		}
	}
	print(item);

}
int main()
{
	vector<int>item;// Initial vector declaration
	item.push_back(5);
	item.push_back(10);
	item.push_back(3);
	item.push_back(1); // Things stored in the vector
	print(item);
	sequence(item, 3);// sequential search used to print index of the item
	sequence(item, 5);
	sequence(item, 10);
	sequence(item, 3986);// This should not be found 
	cout << "Before bubble :";
	print(item);
	bubble(item);// bubble sort to sort vector
	binsearch(item, 3);// binary search used to print index of the item
	binsearch(item, 1);
	binsearch(item, 10);
	binsearch(item, 3986);// This should not be found 
	// new elements added
	item.push_back(200);
	item.push_back(20);
	item.push_back(2); 
	cout << "Before insertion :";
	print(item);
	insertion(item);
	return 0; 
}