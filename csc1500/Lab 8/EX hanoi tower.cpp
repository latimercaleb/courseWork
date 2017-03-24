// Tower of hanoi recursion practice
#include<iostream>
using namespace std;
void Tower(int disk, int beg, int  mid, int end)
{
	if (disk == 1)
		cout << "Move " << disk << " from " << beg << " to " << end << endl;
	else
	{
		Tower((disk-1), beg,end,mid);
		cout << "Move " << disk << " from " << beg << " to " << end << endl;
		Tower((disk - 1), mid,beg,end);
	}
}
int main()
{
	int size;
	cout << "How many disks in tower : ";
	cin >> size;
	Tower(size,1,2,3);
	return 0;
}