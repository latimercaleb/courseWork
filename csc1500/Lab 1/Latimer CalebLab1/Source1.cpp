#include<iostream>
#include<fstream>
using namespace std;
int main()
{
	ofstream prog1_output;
	prog1_output.open("prog1_output.txt");
	int ans;
	cout << "Type a number 1-5 for truth tables \n" << "1: Conjunction \n" << "2: Disjunction \n" << "3: Conditional \n" << "4: Biconditional \n"
		<< "5. XOR \n";
	cin >> ans;
	switch(ans)
	{
	case 1: // fix boxing method for this case then replicate to other cases 
		prog1_output << "Conjunction \n";
		prog1_output << "P |" << "Q |" << "P ^ Q|" << endl;
		prog1_output <<"_____"<< endl;
		prog1_output << "T|" << "T|" << "T|" << endl;
		prog1_output << "_____" << endl;
		prog1_output << "T|" << "F|" << "F|" << endl;
		prog1_output << "_____" << endl;
		prog1_output << "F|" << "T|" << "F|" << endl;
		prog1_output << "_____" << endl;
		prog1_output << "F|" << "F|" << "F|" << endl;
		prog1_output << "_____" << endl;
		break;

	case 2: 
		prog1_output << "Disjunction \n";
		prog1_output << "P " << "Q " << "P or Q" << endl;
		prog1_output << endl;
		prog1_output << "T " << "T " << "T" << endl;
		prog1_output << "T " << "F " << "T" << endl;
		prog1_output << "F " << "T " << "T" << endl;
		prog1_output << "F " << "F " << "F" << endl;
		break;

	case 3: 
		prog1_output << "Conditional \n";
		prog1_output << "P " << "Q " << "P -> Q" << endl;
		prog1_output << endl;
		prog1_output << "T " << "T " << "T" << endl;
		prog1_output << "T " << "F " << "F" << endl;
		prog1_output << "F " << "T " << "T" << endl;
		prog1_output << "F " << "F " << "T" << endl;
		break;

	case 4: 
		prog1_output << "Bicondtional \n";
		prog1_output << "P " << "Q " << "P <-> Q" << endl;
		prog1_output << endl;
		prog1_output << "T " << "T " << "T" << endl;
		prog1_output << "T " << "F " << "F" << endl;
		prog1_output << "F " << "T " << "F" << endl;
		prog1_output << "F " << "F " << "T" << endl;
		break;

	case 5: 
		prog1_output << "XOR \n";
		prog1_output << "P " << "Q " << "P XOR Q" << endl;
		prog1_output << endl;
		prog1_output << "T " << "T " << "F" << endl;
		prog1_output << "T " << "F " << "T" << endl;
		prog1_output << "F " << "T " << "T" << endl;
		prog1_output << "F " << "F " << "F" << endl;
		break; 

	default: prog1_output << "Enter a valid number \n";
		break; 

	}
	
}