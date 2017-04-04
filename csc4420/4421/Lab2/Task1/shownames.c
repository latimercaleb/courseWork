#include <dirent.h>
#include <errno.h>
#include <stdio.h>
int main (int argc, char *argv[])
{
struct dirent *direntp;
// define a pointer with type directory stream (DIR):
DIR *mine;
// check the number of arguments (argc). It should be two. If it
// is not two, then print an error message and exit the program:
if (argc != 2)
{
 fprintf (stderr, "Usage: %s directory name \n", argv[0]);
 return 1;
}
// The following lines should open the directory given by
// argument argv[1] (by using opendir).
// Store it in your defined directory stream variable.
// The rest checks if the system call returned a proper value
// if not an error message is printed and the program closed
if ((mine = opendir(argv[1]))== NULL)
{
 perror ( "Failed to open directory" );
return 1;
}
// Read all the entries in this directory and store them in
// direntp. readdir will read one entry at a time and increment
// automatically. This is why it is in a while loop.
// Then, print all the file names (using the struct from readdir).
while ((direntp = readdir(mine)) != NULL)
 printf ("%s \n" , direntp->d_name);
// close the defined directory stream.
while ( ( closedir (mine) == -1) && ( errno == EINTR) );
return 0;
}
