#include <stdio.h>
#include <time.h>
#include <sys/stat.h>
int main (int argc, char *argv[])
{
 // define an instance of struct stat (don’t use a pointer).
 struct stat myBuffer;
 // Use the stat function store the status of the file in your stat struct
 // stat takes a pointer, so pass your struct by reference with &
 if ( (stat(argv[1],&myBuffer)) == -1)
 {
 // use perror to print error message then exit program
perror("You miscalculated!");
return 1;
 }
 // print the last access time for the file using defined instance of
 // struct stat. ctime requires a pointer, hence the & below.
 printf ("%s last accessed at %s", argv[1], ctime(&myBuffer.st_atime));
}
