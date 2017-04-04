#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include<sys/wait.h>
#define BUFSIZE 10
int main(void) {
    char bufin[BUFSIZE] = "empty";
    char bufout[] = "hello";
    int bytesin;
    pid_t childpid;
    int fd[2];
    if (pipe(fd) < 0) { /* create a pipe */
        perror("Failed to create the pipe");
        return 1;
    }
    bytesin = strlen(bufin);
    childpid = fork();
    if (childpid < 0) {
        perror("Failed to fork");
        return 1;
    }
    if (childpid == 0){
    /* child code */
        close(fd[0]);
        write(fd[1],bufout, strlen(bufout)+1);
        close(fd[1]);
      }
    else{
    /* parent code */
        close(fd[1]);
        bytesin = read(fd[0], bufin, BUFSIZE);
        close(fd[0]);
      }
    fprintf(stderr, "[%ld]:my bufin is {%.*s}, my bufout is {%s}\n", (long)getpid(), bytesin, bufin, bufout);
    if(childpid > 0){
      wait(0);
    }
    return 0;
}
