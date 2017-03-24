#include<iostream> 
// must use type char 
#include<string>
void bitOr(char x[], char y[]);
void bitAnd(char x[], char y[]);
void bitXor(char x[], char y[]);
int main()
{
	int choice;
	char a[] = { 1, 0, 1, 0, 0, 1, 1, 0, 1, 0, 1, 1 };
	char b[] = { 0, 0, 1, 1, 1, 1, 1, 0, 1, 0, 0, 1 };
	std::cout << "Which problem do you want to call for? (1-3) \n";
	std::cin >> choice;
	if (choice == 1)
		bitOr(a,b);
	else if (choice == 2)
		bitAnd(a,b);
	else if (choice == 3)
		bitXor(a,b);
	else
		std::cout << "You did not enter a valid number. \n"; 
}
void bitOr(char x[], char y[])
{
	char result[12];
	for (int i = 0; i < 12; i++)
	{ 
		if (x[i] > 1 || y[i] > 1)
			result[i] = 1;
		else
			result[i] = 0;
		 
	}
	for (int j = 0; j < 12; j++)
		std::cout << result[j] << " " << std::endl;

}
void bitAnd(char x[], char y[])
{

}
void bitXor(char x[], char y[])
{

}

