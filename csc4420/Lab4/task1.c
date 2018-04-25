// Task 1 done by Caleb Latimer
// ej1297
#include<stdio.h>
#include<unistd.h>

int main(void){
    printf("I am process %ld \n", (long) getpid()); // returns and prints current process id
    printf("My parent is %ld \n",(long) getppid()); // returns and prints parent process id
    printf("Process userid is %ld \n", (long) getuid()); // prints userid
    printf("Group id is %ld \n", (long) getgid()); // prints groupid
    return 0;
}
