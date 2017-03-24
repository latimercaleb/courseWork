// Lab 9 built by Caleb Latimer
#include<iostream>
#include "personType.h"
using namespace std;
int main(){
	personType stranger;
	stranger.setName("Johnny", "Storm");
	stranger.print();
	stranger.setFirstname("Caleb");
	stranger.setMiddlename("Caleb");
	stranger.setLastname("Caleb");
	stranger.checkFirst("Waldo");
	stranger.checkLast("Caleb");
	stranger.print();
	system("Pause");

}