// Program 2 by Caleb Latimer nested loops 
#include<iostream>
#include<fstream>
#include<iomanip>
using namespace std; 
void op1();
void op2();
void op3();
void op4();
void op5();
void main()
{
	int choice;

		std::cout << "This program produces results for problem 2, please select the number(1-5) of the problem you wish to solve..."
			<< "Type anything else to exit \n";
		std::cin >> choice;
		if (choice == 1)
			op1();
		else if (choice == 2)
			op2();
		else if (choice == 3)
			op3();
		else if (choice == 4)
			op4();
		else if (choice == 5)
			op5();
		else
			cout << "Goodbye \n"; 
}

void op1()
{
	std::ofstream result;
	result.open("prog2_output.txt");
	result << "You have chosen the table for 1 \n";
	result << "1. (A ^ B) ^ C \n";
	result << "-------------------- \n";
	result << "  A " << "   B " << "  A ^ B " << " (A ^ B) ^ C \n"; 
	char ans[] = { 'F', 'T' };
	for (int i = 0; i <=1 ; i++)
	{ 
		for (int j = 0; j<=1; j++)
		{
			for (int k = 0; k <= 1; k++)
			{
				result << setw(3) << ans[i];
				result << setw(5) << ans[j];
				result << setw(5) << ans[k];
				result << setw(8) << ans[((i && j) && k)] << endl;
			}
		}
	}
	
} // fix all truth tables with proper values 
void op2()
{
	std::ofstream result;
	result.open("prog2_output.txt");
	result << "You have chosen the table for 1 \n";
	result << "1. (A XOR B) XOR C \n";
	result << "-------------------- \n";
	result << "  A " << "   B " << "  A XOR B " << " (A XOR B) XOR C \n";
	char ans[] = { 'F', 'T' };
	for (int i = 0; i <= 1; i++)
	{
		for (int j = 0; j <= 1; j++)
		{
			for (int k = 0; k <= 1; k++)
			{
				result << setw(3) << ans[i];
				result << setw(5) << ans[j];
				result << setw(5) << ans[k];
				result << setw(8) << ans[((i ^ j) ^ k)] << endl;
			}
		}
	}
}
void op3()
{
	std::ofstream result;
	result.open("prog2_output.txt");
	result << "You have chosen the table for 1 \n";
	result << "1. (A and B) or C \n";
	result << "-------------------- \n";
	char ans[] = { 'F', 'T' };
	for (int i = 0; i <= 1; i++)
	{
		for (int j = 0; j <= 1; j++)
		{
			for (int k = 0; k <= 1; k++)
			{
				result << setw(3) << ans[i];
				result << setw(5) << ans[j];
				result << setw(5) << ans[k];
				result << setw(8) << ans[((i ^ j) || k)] << endl;
			}
		}
	}
}
void op4()
{
	std::ofstream result;
	result.open("prog2_output.txt");
	result << "You have chosen the table for 1 \n";
	result << "1. (A <-> B) <-> C \n";
	result << "-------------------- \n";
	char ans[] = { 'F', 'T' };
	for (int i = 0; i <= 1; i++)
	{
		for (int j = 0; j <= 1; j++)
		{
			for (int k = 0; k <= 1; k++)
			{
				result << setw(3) << ans[i];
				result << setw(5) << ans[j];
				result << setw(5) << ans[k];
				result << setw(8) << ans[(k ==1)|| ((i == 1) || (j == 1))? (1): (0)] << endl;
			}
		}
	}
}
void op5()
{
	std::ofstream result;
	result.open("prog2_output.txt");
	result << "You have chosen the table for 1 \n";
	result << "1. ((A -> B) -> C) -> D \n";
	result << "-------------------- \n";
	char ans[] = { 'F', 'T' };
	char x, y; 

	for (int i = 0; i <= 1; i++)
	{
		for (int j = 0; j <= 1; j++)
		{
			for (int k = 0; k <= 1; k++)
			{
				result << setw(3) << ans[i];
				result << setw(5) << ans[j];
				result << setw(5) << ans[k];
				result << setw(8) << ans[((i == 1) ? (ans[i]) : (ans[1]))] << endl;
			}
		}
	}
}