// Lab 8 written by Caleb Latimer, ej1297
#include<iostream> // for I/O
#include<sys/types.h> // for kill()
#include<signal.h> // for signals
#include<unistd.h> // for pause()
#include<fstream> // for file manipulations
using namespace std;

void wake(int input){
	sleep(1);
}; // empty function to prevent closure
int main(){
	int x;
	ofstream init; // stream for initializing x to proper value at the beginning of each run, helpful for testing

	ifstream pinput; // parent streams
	ofstream poutput;

	ifstream cinput; // child streaks
	ofstream coutput;

	init.open("localstore.txt",ofstream::out | ofstream::trunc);
	if(!(init.good())){
		cout << "Initialization stream failed\n";
		return 1;
	}
	init << 19530; // initializes the text file to the proper starting value
	init.close();

	pinput.open("localstore.txt");
	if(!(pinput.good())){
		cout << "Parent input stream failed \n";
		return 1;
	}
	pinput >> x;
	pid_t myPid;
	cout << "x = " << x << endl << endl;
	pinput.close();
	myPid = fork();

	if(myPid < 0){
		cout << "Error fork failed\n";
		return -1;
	}
	else if(myPid > 0){ // Parent process does x=x-5 and prints iteration
		sleep(1);
		for(int i =1; i<=5;i++){
			cout << "ITERATION "<< i << endl;
			pinput.open("localstore.txt");
			if(!(pinput.good())){
				cout << "Parent input stream failed \n";
				return 1;
			}
			pinput >> x;
			pinput.close();
			x = x-5;
			cout << "Parent: x = " << x << endl;
			poutput.open("localstore.txt", ofstream::out | ofstream::trunc);
			if(!(poutput.good())){
				cout << "Parent output stream failed \n";
				return 1;
			}
			poutput << x;
			poutput.close();
			kill(myPid,SIGUSR1);
			signal(SIGUSR1,wake);
			pause();
		}
	}
	else{ // Child Process does x=x/5 and prints a blank line
		for(int i=1;i<=5;i++){
			signal (SIGUSR1,wake);
			pause();
			cinput.open("localstore.txt");
			if(!(cinput.good())){
				cout << "Child input stream failed \n";
				return 1;
			}
			cinput >> x;
			x = x/5;
			cout << "Child: x = " <<  x << endl << endl;
			cinput.close();
			coutput.open("localstore.txt", ofstream::out | ofstream::trunc);
			if(!(coutput.good())){
				cout << "Child output stream failed \n";
				return 1;
			}
			coutput << x;
			coutput.close();
			kill(getppid(),SIGUSR1);
		}
	}
	return 0;
}
