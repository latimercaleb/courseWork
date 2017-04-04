// Pipe practice written by Caleb Latimer, ej1297
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<errno.h>
#include<sys/types.h>
#include<iostream>
#include<fcntl.h>
using namespace std;

int main(){

int x = 19530; // Original input
size_t XSIZE = sizeof(x); // sizeo of the original input
cout << "x = " << x << endl << endl; // first line of test output

int child[2]; // for child pipe
int parent[2]; // for parent pipe
pid_t ID; // for fork() later
ssize_t check; // ssize_t type for error checking

// opening the pipes, error handling
if((pipe(child)) < 0){ // child pipe
  cout << "Child has no pipe\n";
  return 1;
}

if((pipe(parent))< 0){// parent pipe
  cout << "Parent has no pipe\n";
  return 1;
}
// initial write to parent pipe to initialize
if ((check = write(parent[1],&x,XSIZE)) <= 0){
	cout << "Pre-write failed\n";
	return 1;
}

ID = fork(); // forking, each fork will have two loops which iterate 5 times passing values back and forth
if(ID < 0){
  cout << "Fork failed \n"; // error handling for fork
  return 1;
}

else if(ID == 0){ // child does x = x-5
  for(int i = 1; i <= 5; i++){
		check = 0; // sets check to 0 each time to prevent error

			if((check = read(parent[0], &x, XSIZE)) < 0 ){ // read the new value of x into x from parent[1]
				cout << "Child, read failed \n";
				return 1;
			}
			x = x-5; // do the subtraction
			cout << "ITERATION " << i << endl; // print iteration count
			cout << "Child : x = " << x << endl; // print current x
			if ((check = write(child[1],&x,XSIZE)) < 0) { // write the new value into child[1] for piping for parent
				cout << "Child, write failed \n";
				return 1;
		}
  }
}

else{ // parent does x = x/5
  for(int i =1; i <= 5; i++){
		check = 0; // again, error prevention
		if((check = read(child[0], &x, XSIZE)) < 0){ // read new x value from child[1]
			cout << "Parent read failed \n";
			return 1;
		}
		x = x/5; // do division
		cout<< "Parent : x = " << x << endl << endl; // print new x and skip 2 lines
		if((check = write(parent[1],&x,XSIZE)) < 0){
		cout << "Parent write failed \n"; // write new value to parent[1] for piping back to child
		return 1;
		}
  }
}
  return 0;
}
