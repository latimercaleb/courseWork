// Task1 of Lab3 written by Caleb Latimer
#include<unistd.h> // required library for the system calls
#include<fcntl.h> // required for system calls usage
#include <stdlib.h> // required for the use of exit statement
#include<stdio.h> // required for the use of perror
using namespace std;

int main(int argc,char *argv[]){
  // open the first file for reading
  int file; // integer value for holding the file descriptor
  ssize_t display;
  char *buff[256];

  file = open(argv[1],O_RDONLY);
  if(file == -1 ){ // error handler for system call 1: open()
    perror("Did not open, exiting...");
    exit (1);
  }

  // read from the file to the console
  while((display = read(file,buff,10)) > 0){
    if(write(STDOUT_FILENO, buff,display) != display){ // if statement doubles as error handling for read()
      perror("Problem with writing..."); // errror handling for write()
      exit(-1);
    }
}

  file = close(file); // Final system call close()
  return 0;
}
