// Program 5 written by Caleb Latimer
#include<unistd.h>
#include<iostream>
#include<stdlib.h>
using namespace std;
int main(){
  bool death = true;
  cout << "Tonight we die R.I.P " << endl;

  int myID = getpid();
  int next,counter;
  counter =0;

  do{
    next = fork();
    if (next<0){
      cout << "Fork failed we're done!";
      exit(1);
    }
    else if (next>0){
      counter++;
      cout << counter << endl;
    }
    else
      exit(400);
  } while(death = true);
  return 0;
}
