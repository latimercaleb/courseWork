//#include<iostream> // used for testing
#include<unistd.h> // required library for the system calls
#include<fcntl.h> // required for system calls usage
#include <stdlib.h> // required for the use of exit statement
#include<stdio.h> // required for the use of perror
using namespace std;

int main(int argc,char *argv[]){
  //cout << "Library exists" << endl; // test that library was included properly

  // open the first file for reading
  int file;
  ssize_t display;
  char *buff[256];

  file = open(argv[1],O_RDONLY);
  if(file == -1 ){
    perror("Did not open, exiting...");
    exit (1);
  }

  // read from the file to the console
  while((display = read(file,buff,10)) > 0){
    if(write(STDOUT_FILENO, buff,display) != display){
      perror("Problem with writing...");
        write(STDOUT_FILENO, buff,display);
    }


  }

  return 0;
}
