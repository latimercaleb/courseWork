// Directory crawler
// Written by Caleb Latimer, ej1297

#include<iostream>
#include <dirent.h>
#include<string.h>
#include <errno.h>
#include <stdio.h>
#include<string>
#include <stdint.h>
#include <sys/types.h>
#include <sys/stat.h>
#include<stdlib.h>
using namespace std;

int binCount = 0; // count of total bins which are nodes in the linked-list

struct node{ // struct node will be the content of each bin, each bin will be a linked-list
	int count, name, min, max;
	node* next;
	node(){
		name = binCount;
	  count = 0;
		min = 0;
		max = 0;
		next = NULL;
	}
};
node *head = new node; // head declared globally and attached to the first parameter
node *current = head; // current is used to iterate the list, change values, add nodes etc

void traverseNewDirectory(const char *dirName, int binWidth){ // recursive function for the traversal of nested folders and subdirectories 
	DIR * nwd;
	struct dirent *dip;
	bool isadirectory,isHidden;
	if((nwd = opendir(dirName))== NULL){
		perror("Can't open derived directory"); // error handling for directory opening
		return;
	}

	while ((dip = readdir(nwd)) != NULL){
		isadirectory = false;
		isHidden = false;
		if((dip -> d_type) == DT_UNKNOWN ){
			struct stat stbuf;
      stat(dip->d_name, &stbuf);
      isadirectory = S_ISDIR(stbuf.st_mode);
		}
		else if((dip -> d_type) == DT_DIR ){
			if((strcmp(dip->d_name, ".") == 0) || (strcmp(dip->d_name, "..")) == 0){
				isHidden = true;
				isadirectory = true;

			}
			else{
				isadirectory = true;
			}
		}
		else{
			if((dip-> d_reclen <= current->max)&&(dip->d_reclen >=current->min)){
					current->count = current->count+1;
			}
			else if(dip->d_reclen < current->min){
				node*temp = head;
				while(temp != NULL){
					if((dip-> d_reclen <= temp->max)&&(dip->d_reclen >=temp->min)){
							temp->count = temp->count+1;
							break;
					}
					else if(dip->d_reclen < temp->min){
						temp = temp->next;
				}
			}
			temp = NULL;
			delete temp;
		}
			else{
				current->next = new node;

				current->next->count = 1;
				current->next->min = current->max + 1;
				current->next->max = current->max + binWidth;
				current = current->next;

				binCount++;
			}
		}
		if(isadirectory){
			string path = string(dirName) + "/"+dip->d_name;
			if(isHidden == true){}
			else{
			traverseNewDirectory(path.c_str(), binWidth);
			}
		}
	}
	while ( ( closedir (nwd) == -1) && ( errno == EINTR) );
}
void printHistogram(node *head){
	node*temp;
	temp = head;
	while(temp!=NULL){
		cout << "[B " << temp->name << "] from  " << temp->min << " to " << temp->max << " : ";
		for(int i = 0; i < temp->count; i++){
			cout << "x";
		}
		cout << endl;
		temp = temp->next;
	}
}
int main(int argc,char *argv[]){
	// Ensures that a valid directory is provided by the cmd line argument
	if (argc != 3){
		if(argc == 1){
			fprintf (stderr, " argc = %d no directory given  \n", argc);
			return 1;
		}
		else if(argc == 2){
		fprintf (stderr, " argc = %d no size given \n", argc);
		return 2;
		}
		else{
			fprintf(stderr, "argc = %d invalid parameters \n", argc);
			return 3;
		}
	}
	DIR * cwd; // current working directory pointer
	struct dirent *cwdP; // pointer to dirent struct
	int binWidth; // variable for the width of the grouping in the histogram
	binWidth = atoi(argv[2]);
	if(binWidth <= 0){
		fprintf(stderr, "argv[2] = %s invalid parameters \n", argv[2]);
		return 4;
	}
	binWidth = binWidth - 1;
	if(binWidth == 0){
		binWidth++;
	}
	head->max = binWidth;
	binCount++;
	bool isadirectory,isHidden;
	if((cwd = opendir(argv[1]))== NULL){
		perror("Can't open  main directory");
		return 2;
	}

	while ((cwdP = readdir(cwd)) != NULL){
		isadirectory = false;
		isHidden  = false;
		if((cwdP -> d_type) == DT_UNKNOWN ){
			struct stat stbuf;
			stat(cwdP->d_name, &stbuf);
			isadirectory = S_ISDIR(stbuf.st_mode);
		}
		else if((cwdP -> d_type) == DT_DIR ){
			if((strcmp(cwdP->d_name, ".") == 0) || (strcmp(cwdP->d_name, "..")) == 0){
				isHidden = true;
				isadirectory = true;
			}
			else{
				isadirectory = true;
			}
		}
		else{
			if((cwdP-> d_reclen <= current->max)&&(cwdP->d_reclen >=current->min)){
					current->count = current->count+1;
			}
			else if(cwdP->d_reclen < current->min){
				node*temp = head;
				while(temp != NULL){
					if((cwdP-> d_reclen <= temp->max)&&(cwdP->d_reclen >=temp->min)){
							temp->count = temp->count+1;
							break;
					}
					else if(cwdP->d_reclen < temp->min){
						temp = temp->next;
				}
			}
			temp = NULL;
			delete temp;
		}
			else{
				current->next = new node;

				current->next->count = 1;
				current->next->min = current->max + 1;
				current->next->max = current->max + binWidth;


				current = current->next;
				binCount++;
			}
		}
		if(isadirectory){
			string fullPath = string(argv[1]) + "/" + cwdP ->d_name;
			if(isHidden == true){

			}
			else{
			traverseNewDirectory(fullPath.c_str(), binWidth);
			}
		}
	}
	while ( ( closedir (cwd) == -1) && ( errno == EINTR) );
	printHistogram(head);
	return 0;
}
