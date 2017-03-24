// Program ex of lab 5 built by Caleb Latimer
#include<iostream>
#include<fstream> 
#include<string>
using namespace std;

int main(){
	int A[4] = {1,2,3,4};
	int B[5] = {0,2,4,6,8};
	int C[5] = {3,5,7,9,11};
	int D[11] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 11 }; // Domain of all 
	int R1[7];
	int R2[7];
	int R3[4];
	////////////////////////////// All of the above are either given indexes or calculated indexes so these should be fine/////////////////////
	/*int *R3;
	R3 = new int[7000];*/

	cout << "Problem 1 : \n"; // The first problem 
	int s1[2]; // Intermediate step built for finding and saving the intersection 
	int o = 0;
	for (int i = 0; i < 4; i++){ // Finds intersection 
		for (int j = 0; j < 5; j++){
			if (A[i] == B[j]){
				s1[o] = B[j];
				o++;
			}
		}
	}
		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < 5; j++) // finds next step union of intersection and C but rules out duplicates
			{
				if (s1[i] == C[j])
					C[j] = NULL; // duplicates become null 
			}
		}
		for (int i = 0; i < 5; i++)
		{
			if (C[i] == NULL)// Checks the flag for each element and only executes if found 
			{
				for (int k = i; k <(5 - 1); k++)
				{
					C[k] = C[k + 1]; //Now equal to the value to the right so everything shifts left.  
					C[k + 1] = NULL; // Null moves to the end of the array 
					//cout << "Test2" << endl; 
				}

			} //cout << "Test" << endl; 
		}
		int q = 0; // counter 
		for (int i = 0; i < 5; i++)
		{
			if (C[i] != NULL)
				q++;// finds size of array of not null values 
		}
		int rcont = 0;// counter for result of 1
		for (int i = 0; i < 2; i++)
		{
			R1[rcont] = s1[i]; // grabs everything from the intersection since that's in my answer and not a duplicate
			rcont++;
		}
		for (int j = 0; j < q; j++)// grabs everything from C that has not been Nulled out
		{
			R1[rcont] = C[j];
			rcont++;
		}

		cout << "Solution to problem 1 is : \n";
		for (int i = 0; i < rcont; i++) // returns solution to user
			cout << R1[i] << " ";
	
	/*for (int i = 0; i < 2; i++) // checks s1 
		cout << s1[i] << " ";*/ 

	cout << "\nProblem 2 : \n";
	int subtract[5]; // array for intermediate step of B-C
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			if (B[i] == C[j])
			{
				subtract[i] = NULL;// If there is a duplicate it becomes null 
			}
			else
				subtract[i] = B[i];// Since we only want what is in B with subtraction 
		}
	}
	//for (int i = 0; i < 5; i++)
		//cout << subtract[i] << " ";
	//
	for (int i = 0; i < 5; i++) //  Same as code for problem 1 except I am looking for union A instead of union C
	{
		for (int j = 0; j < 4; j++)
		{
			if (subtract[i] == A[j])
				A[j] = NULL;
		}
	}
	for (int i = 0; i < 4; i++)
	{
		if (A[i] == NULL)// Checks the flag for each element and only executes if found 
		{
			for (int k = i; k <(4 - 1); k++)
			{
				A[k] = A[k + 1]; // myArray is now equal to the value to the right so everything shifts left.  
				A[k + 1] = NULL;
				//cout << "Test2" << endl; 
			}

		} //cout << "Test" << endl; 
	}
	int z = 0; // New counter variable for problem 2 
	for (int i = 0; i < 4; i++)
	{
		if (A[i] != NULL)
			z++;
	}
	int r2cont = 0;
	for (int i = 0; i < 5; i++)
	{
		R2[r2cont] = subtract[i];
		r2cont++;
	}
	for (int j = 0; j < z; j++)
	{
		R2[r2cont] = A[j];
		r2cont++;
	}

	cout << "Solution to problem 2 is : \n";
	for (int i = 0; i < rcont; i++)
		cout << R2[i] << " "; // returns result 

	/*for (int i = 0; i < 2; i++)
		cout << s1[i] << " ";*/


	cout << "\nProblem 3 : \n"; // 
	int temp[7]; // Array for intermediate step of AUB, same as problems 2 and 3 save for union B 
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			if (A[i] == B[j])
				B[j] = NULL;
		}
	}
	for (int i = 0; i < 5; i++)
	{
		if (B[i] == NULL)// Checks the flag for each element and only executes if found 
		{
			for (int k = i; k <(5 - 1); k++)
			{
				B[k] = B[k + 1]; // myArray is now equal to the value to the right so everything shifts left.  
				B[k + 1] = NULL;
				//cout << "Test2" << endl; 
			}

		} //cout << "Test" << endl; 
	}
	int u = 0; // new counter var for the intermediate step 
	for (int i = 0; i < 5; i++)
	{
		if (B[i] != NULL)
			u++;
	}
	int tempcont = 0;
	for (int i = 0; i < 3 ; i++)
	{
		temp[tempcont] = A[i];
		tempcont++;
	}
	for (int j = 0; j < u; j++)
	{
	
		temp[tempcont] = B[j];
		tempcont++;
	}
	//for (int i = 0; i < tempcont; i++)
	//	cout << temp[i] << " "; // returns temp which is AUB for checking 
	////cout << "Tempcont" << tempcont << endl; // returns temp comp for clarity
	//cout << endl; // temp is the value of AUB which I calculated and is correct

	//////////////////////////////////////////// For some reason this causes an out of scope error when I compare it to D[] the total domain /////////////////////////////////
	/*for (int i = 0; i < tempcont; i++){
		for (int i = 0; i < 11; i++){
			if (R3[i] == NULL){
				for (int j = (i); j < 10; j++){
					R3[j] = R3[j + 1];
					R3[j + 1] = NULL;
				}
				break;
			}
		}
	}*/

	int r3cont = 0;// counter for R3
	int pop = 0; 
	bool kill = false; // loop killer
	int *test;
	test = new int[4];
	int trigger = 0; // will serve to trigger the kill 
		// cout << tempcont << " dskjafnsdjf"; checking temp cont its 7 
		for (int i = 0; i < tempcont; i++) // This segement goes out of scope. But why...., temp cont is 7 

		{
			for (int j = 0; j < 5; j++)// C is 5, max amount of increments are 35
			{
				if (temp[i] != C[j])// If temp and D are not equal ...fixed problem in else
				{
					for (int k = 0; k < 4; k++)
					{
						test[k] = C[j]; 
						for (int m = 0; m < 4; m++){
							if (test[k] == A[m])
								test[k] = NULL;
						}
						if (test[k] != NULL)
						{
							for (int n = 0; n < 5; n++)
							{
								if (test[k] == B[n])
									test[k] = NULL;
							}
						}
						if (test[k] != NULL){
							R3[r3cont] = test[k]; // R3[it's index] is assigned to D[j] This line is causing the scope break, but I have no idea as to why... This code breaks because it goes way too far out of scope since it takes in every combination of when the intersection and C are not equal over and over so something must be done to stop it. Time to try a flag to trigger breaks  
							r3cont++; // If it stores a value then it increments to fill in the next index THIS HAS TO BE IN THE ELSE STATEMENT! 
							trigger++;
							//cout << "Yes" << pop << endl; // check of how many times if is run 
							//pop++; // counter for yes statements 69 times
						}
						if (trigger >= 4){
							cout << trigger << " TRIGGERED!" << endl;
							kill = true;
						}
						if (kill == true)
							break;
					}
					if (kill == true)
						break;
				}
				if (kill == true)
					break;
				/*if (trigger > 4){
					cout << trigger << " TRIGGERED!" << endl;
					kill = true; 
				}
				if (kill == true)
					break;*/
				//(D[j] != temp[i])
				//else { // Shouldn't need this. If temp and D are equal then nothing will pass to r3 and the iterations will continue 
				//	//cout << "NO\n"; // check of how many times else is run 7 times
				//	R3[r3cont] = NULL;
				//	r3cont++;
				//}
			}
			if (kill == true)
				break;
		}
	
	cout << "R3 counter is : " << r3cont << endl; // Check for the r3 counter... 34.... 34??? WHY? WHY ARE YOU RUNNING 34 TIMES! 
	/*r3cont = 0; */

	//for (int i = 0; i < r3cont; i++)// sorts r3 , shouldn't be needed because there will be no null values in R3
	//{
	//	if (R3[i] == NULL)// Checks the flag for each element and only executes if found 
	//	{
	//		for (int k = i; k <(r3cont- 1); k++)
	//		{
	//			R3[k] = R3[k + 1]; // myArray is now equal to the value to the right so everything shifts left.  
	//			R3[k + 1] = NULL;
	//			//cout << "Test2" << endl; 
	//		}

	//	} //cout << "Test" << endl; 
	//}

	for (int i = 0; i < 4; i++){// checks R3
		//if (R3[i] != NULL)// prints if r3 is not null, again shouldn't need null check 
			cout << R3[i] << " ";
	}
	/////////////////////////////////////////// What is the problem ^? //////////////////////////////////////////////////////////
	//cout << "\nAnswer should be " << 5 << 7 << 9 << 11 << endl; // Outputs proper result for checking against code 
	 
	return 0; 
}