// Lab 5 written by Caleb Latimer
// ej1297

#include<iostream>
#include<fstream>
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/wait.h>
using namespace std;

int main(){
  ifstream init; // initial stream

  ifstream doc; // child streams
  ofstream print;

  ifstream input; // parent streams
  ofstream output;

  int x;
  pid_t mypID,childpID;

  init.open("number.txt");

  if(!(init.is_open())){
    cout << "Init could not open file for reading\n";
    return 1;
    }

  else{
    init >> x;
    init.close();

    cout << "x = " << x << endl;

    int * stat;

    for(int i = 1; i <=5; i++){
    cout << "Iteration " << i << endl;
    mypID = fork();

    if(mypID == 0){ // my child process
    doc.open("number.txt");
    if(!(doc.is_open())){
      cout << "Child could not open document for reading \n";
      return 2;
    }
    else{
      doc >> x;
      doc.close();
      x = x-5;
      cout << "Child : x = " << x << endl;
      print.open("number.txt", ofstream::out | ofstream::trunc);
      if(!(print.is_open())){
        cout << "Child could not open document for writing \n";
        return 3;
      }
      else{
        print << x;
        print.close();
      }
    }
    exit (100);
    }

    else if(mypID > 0){ //  parent process
    pid_t wait = waitpid(mypID,NULL,0);
    if(wait < 0){
      cout << "Error child did not terminate \n";
      return 3;
    }
    else{
      input.open("number.txt");
      if(!(input.is_open())){
        cout << "Parent could not open document for reading \n";
        return 4;
      }
      else{
        input >> x;
        input.close();
        x = x/5;
        cout << "Parent : x = " << x << endl;
        output.open("number.txt", ofstream::out | ofstream::trunc);
        if(!(output.is_open())){
          cout << "Child could not open document for writing \n";
          return 5;
        }
        else{
          output << x;
          output.close();
        }
      }
    }
  }

    else{
      cout << "Fork failed to execute \n";
      return 6;
    }
  }


  }
  return 0;
 }

// Attempt at shmget(), work on this more later in free time
/*
// REFACTOR
#include<unistd.h>
#include<iostream>
#include<errno.h>
#include<stdlib.h>
#include<stdio.h>
#include<cstring>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>
using namespace std;

// Functions for computation
// Function for parent process, returns the value/5
int parent(int in){
  return in/5;
}
// Function for the child process returns the value-5
int child(int in){
  return in-5;
}

int main(){
  //cout << "Hello world \n"; // test of makefile, exe titled run
  int x = 0; // Parameter for parent() & child()
  key_t key = 19530; // Value to pass to shared memory space
  int shmID = -100; // ID of shared memory variable

  //cout << "The size is : " <<sizeof(key) << endl; // size of key is 4
  size_t size = sizeof(key); // size of key to pass to the shared memory space
   // Makes a shared memory space for the key value, makes a space once only, makes a different space each time the computer is restarted
  if(shmget(key,size,IPC_CREAT | IPC_EXCL) < 0){ // checks creates memory space or throws error if the space has been created already
    printf("The following error occurred: %s \n", strerror(errno));
    printf("The old shmID is %d \n", shmID);
  }

  else{
  shmID = shmget(key,size,IPC_CREAT | IPC_EXCL);
  printf("The new shmID is %d \n", shmID);
  }

  return 0;
}
*/
