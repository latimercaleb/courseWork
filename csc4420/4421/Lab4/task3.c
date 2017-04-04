// Task 3 written by Caleb Latimer
// ej1297
#include<sys/types.h> // for specific data types
#include"stdio.h" // for c-functions
#include<unistd.h> // system calls
#include<sys/wait.h> // for wait calls
#include<string.h> // for string functions
#include<stdlib.h> // for other c-functions

int main(){
  int PID;
  char lineGot[256];
  char *cmd;
  char *argcmd;
  char *param1;
  char *param2;

  while(1){ // while shell is active
    printf("cmd: ");
    fgets(lineGot, 256, stdin); // Gets a string from the user (includes \n)
    cmd = strtok(lineGot, "\n"); // Get the string without the \n

    if(strcmp(cmd,"e") == 0) // loop terminates when "e" is typed
        exit (0); // terminates the loop
    // Parses input from fgets() into seperate strings which will be used for exec system call
    argcmd = strtok(cmd," ");
    param1 = strtok(NULL," ");
    param2 = strtok(NULL, " ");

        // Creates a new process. Parent gets the child's process ID. Child gets 0.
      if ((PID = fork()) > 0) {
        wait(NULL);
      }

      else if(PID == 0){
        char * mycalls[] = {argcmd,param1,param2,NULL}; //stores all parsed strings into its own array
        execvp(argcmd,mycalls); // exits current process and flies off to do whatever the input was
        // execlp(cmd,cmd,NULL); // part of sample
        // cannot return so do the following
        fprintf(stderr, "Cannot execute %s \n", cmd); // If it can't do the command comes back
        exit (1); // exec failed
      }

      else if(PID == -1){
        fprintf(stderr, "Cannot create a new process \n");
        exit (2);
      }
  }
}
