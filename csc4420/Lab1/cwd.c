#include <limits.h>
#include <stdio.h>
#include <unistd.h>
#ifndef PATHMAX
#define PATHMAX 255
#endif
int main ( void) {
char mycwd [PATHMAX];
if ( getcwd (mycwd, PATHMAX) == NULL){
perror ("Failed to get current working directory");
return 1;
}
printf ("Current working directory : %s \n", mycwd);
return 0;
}
