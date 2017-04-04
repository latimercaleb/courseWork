// program to find parent id before and after it's parent terminates
// By Caleb Latimer
#include<stdlib.h>
#include<unistd.h>
#include<iostream>
#include<signal.h>
using namespace std;
int main(int argc, char *argv[]){

  int currentPid;
  int killMyDad;
  cout << "parent-id: " << getpid() << endl;// this is my current id which is gonna be a parent
  currentPid = fork(); // fork starts here


  if(currentPid < 0){ // error handling if fork failed
    cout << "Fork failed\n";
    exit(-100);
  }

  else if(currentPid == 0){ // inside child
    cout << "I am a child" << endl;
    cout << "My id: " << getpid()<< endl;
    cout << "My parent-id: " << getppid() << endl;
    sleep(10); // make the parent sleep for awhile
    cout << "my new parent id is " << getppid() << endl; // tested multiple times new id is 14937
    //killMyDad = getppid(); // apparently I have difficulty killing my parents
  }
  sleep(1);
  exit(1);
  return 0;
}
