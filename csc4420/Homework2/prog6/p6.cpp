// Program 6 written by Caleb Latimer
#include<unistd.h>
#include<time.h>
#include<iostream>
#include<stdio.h>
#include<stdlib.h>

using namespace std;

int main(){

int myID;

clock_t begin_time;
clock_t end_time;
double totalTime = 0;

for (int i = 0; i < 5; i++){
begin_time = clock();
myID = fork();

if (myID < 0){
cout << "You broke me";
exit(1);
}

else if (myID > 0){

}

else {
	exit(1);
}

end_time = clock();
double sub = (((end_time-begin_time)*1.0)/CLOCKS_PER_SEC);
totalTime += sub;
}

totalTime /= 5;
cout << "Total time was: " << totalTime << endl;

return 0;
}
