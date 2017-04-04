// Task 2 of Lab 3
// Written by Caleb Latimer
#include<unistd.h> // required library for the system calls
#include<fcntl.h> // required for system calls usage
#include <stdlib.h> // required for the use of exit statement, and atoi
#include<stdio.h> // required for the use of perror
using namespace std;

int main(int argc,char *argv[]){
  int m = atoi(argv[1]); // taking command line args by conversion with atoi
  int n = atoi(argv[2]); // taking commmand line args by conversion with atoi
  int file; // integer value for holding the file descriptor
  ssize_t display; // holds bytes for buffer read
  char buff[1]; // single char buffer to check for the newline char
  int currentLine = 1; // counter for the current line

  // open the first file for reading
  file = open(argv[3],O_RDONLY);// system call to open()
  if(file == -1 ){ // error handler for system call 1: open()
    perror("Did not open, exiting...");
    exit (1);
  }

  while(((display = read(file,&buff,1)) > 0)){ // system call to read()
    if(buff[0] == '\n'){ // checks for newline char
      currentLine++; // increments for newline
    }

    if((currentLine >= m) && (currentLine <= n)){ // does the write only if the currentLine is within the bounds required
      if(write(STDOUT_FILENO, &buff,display) != display){ // if statement doubles as error handling for read(), system call to write()
        perror("Problem with writing..."); // errror handling for write()
        exit(-1);
        }
      }

      else{
          // added for the sake of completion nothing else needs to be done...
      }
}

  file = close(file); // Final system call close()
  return 0;
}
