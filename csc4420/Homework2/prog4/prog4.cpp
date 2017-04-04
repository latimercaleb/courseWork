// Problem 4, find all the parents of a parent
// Written by Caleb Latimer
#include<unistd.h> // needed for getppid()
#include<iostream> // needed for cout
#include<string> // needed for string
#include<sstream> // needed for stringstream
#include<stdio.h> // needed for scan and FILE protocol
using namespace std;

int findFamily(int input){ // Function to take the input, change it to a string for a path to open the hierachy and return the parent ID to main for printing
  stringstream proc;
  proc << input;
  string path = "/proc/";
  path = path.append(proc.str());
  path = path.append("/stat");

  FILE *theProcess;
  theProcess = fopen(path.c_str(),"r");

  int nextID;
  fscanf(theProcess,"%*d %*s %*c %d",&nextID);
  fclose(theProcess);
  return nextID;
}

int main(){

  int myID = getppid();
  int count = 1;
    //cin >> myID; // test for checking a valid pID input one from the list shown with ps -eaf

  while(myID != 0){ // Loop runs until final ID is 1 for the core process in root
  cout << "The " << count << "th parent-process is " << myID << endl;
  myID = findFamily(myID);
  count++;
}
  return 0;
}
