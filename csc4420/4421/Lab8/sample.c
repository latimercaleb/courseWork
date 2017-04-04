//From 60-256 System Programming: Signals II by Dr. B. Boufama, http://kobti.myweb.cs.uwindsor.ca/60-256/c6-2.pdf
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
void action(int);
void action(int dummy){
	sleep(1);
	printf("Switching\n");
}

int main(int argc, char *argv[]){
	pid_t pid;
	if((pid=fork())>0){//parent
	sleep(1);
	while(1){
	printf("Parent is running\n");
	kill(pid, SIGUSR1);
	signal(SIGUSR1, action);
	pause();
	}
}
else
	while(1){//child
	signal(SIGUSR1, action);
	pause();
	printf("Child is running\n");
	kill(getppid(), SIGUSR1);
	}
}
