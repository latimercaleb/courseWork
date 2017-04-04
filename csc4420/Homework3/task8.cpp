#include<iostream>
#include<string>
using namespace std;

class List{
public:
  List(){
    head = new node();
    current = head->child;
  }

  ~List(){
    node* temp = head;
    while(temp != NULL){
      temp = head->child;
      delete head;
      head = temp;
    }
  }

  void makeList(int max){
    node* temp = head;
    emptyCount = 0;
    for(int i = 0; i < max; i++){
      temp->child = new node();
      temp = temp->child;
      emptyCount++;
    }
  }

  void merge(){
	  current = head;
	  node * d;
	  while (current->child != NULL){
		  if ((current->procName == "null") && (current->child->procName == "Empty")){
			  d = current;
			  while (d->procName == "null"){
				  d->procName = "Empty";
				  d = d->child;
			  }
		  }

		  else if ((current->procName == "null") && (current->child->procName == "null")){
			  d = current;
			  while (d->procName == "null"){
				  d->procName = "Empty";
				  d = d->child;
			  }
		  }
		  current = current->child;
	  }
  }

  int proctotal(string name){
	  current = head;
	  while ((current->child != NULL) && (current->procName != name)){
		  current = current->child;
	  }
	  if (current->procName == name){
		  int totalMemUnits = 0;
		  while ((current->procName == name) && (current -> child != NULL)){
			  current = current->child;
			  totalMemUnits++;
		  }

		  return totalMemUnits;
	  }
	  else{
		  return 0;
	  }
  }

  void printList(){
	int index = 0;
    node* temp = head;
    string text = temp->procName;
    if(temp->procName != "Empty"){
      cout << temp->procName << " | "<< index << " | " << proctotal(temp->procName) << endl;
	  index++;
      while(temp-> child != NULL){
		  if (temp->procName != text){
			  cout << temp->procName << " | " << index << " | " << proctotal(temp->procName) << endl;
			  text = temp->procName;
		  }
          temp = temp->child;
		  index++;
      }
    }
    else{
		cout << temp->procName << " | " << index << " | " << emptyCount << endl;
    }

  }

  void addProcess(string t, int num){
    if(num <= emptyCount){
      current = head;
      int count = 0;
	  if (head->procName == "Empty"){
		  while (count < num){
			  current->procName = t;
			  head->procCount = head->procCount + 1;
			  current = current->child;
			  count++;
			  emptyCount--;
		  }
		  return;
	  }
	  else{
		  int totalUnitstoShift = proctotal(head->procName);
		  if (totalUnitstoShift <= emptyCount){
			  while (current->procName != "Empty"){
				  current = current->child;
			  }
			  int count = 0;
			  while (count < num){
				  current->procName = t;
				  head->procCount = head->procCount + 1;
				  current = current->child;
				  count++;
				  emptyCount--;
			  }
			  return;
		  }
		  else{
			  cout << "Not enough space to add requested data \n";
			  return;
		  }
	  }
    }

    else{
      cout << "Cannot add any more processes, memory maxed. \n";
      return;
    }
  }

  void removeProcess(string t, int num){
	  int size = 1;
	  current = head;
	  while (current->child != NULL){
		  current = current->child;
		  size++;
	  }
    if(num <=size ){
      if(t == "Empty"){
        cout << "Cannot remove empty memory cells \n";
		return;
      }
      else{
        current = head;
        while(current->procName != t){
          current = current->child;
        }
       if(current -> procName == t){
          int count = 0;
		  node * temp = current;
          while((count < num) && (current->procName == t)){
            current -> procName = "null";
            temp->procCount = temp->procCount - 1;
            current = current->child;
            emptyCount++;
			count++;
          }
		  if (current->child->procName == "Empty" || current->child->procName == "null"){
			  merge();
		  }
        }
        else{
          cout << "Process name does not exist \n";
          return;
        }
      }
    }
    else{
      cout << "Cannot remove more than maximum memory for processes \n";
      return;
    }
  }

private:
  class node{
  public:
    node(){
        procName = "Empty";
        child = NULL;
        procCount = 0;
    }

    ~node(){
          procName = "Empty";
          child = NULL;
    }

    int procCount;
    string procName;
    node* child;

  };

  node* head;
  node* current;
  int emptyCount;

};

int main(){
  List myList;
  string nameOfproc;
  int numOfunits;
  int size;
  cout << "Enter the total amount of memory for the processes: ";
  cin >> size;

  myList.makeList(size);
  myList.printList();

  int prompt;
  bool exit = false;
  while(exit == false){
    cout << "Enter a number of the following: \n";
    cout << "*************************" << endl;
    cout << "*0 to utilize memory*" << endl;
    cout << "*1 to release memory*" << endl;
    cout << "*Any other number to exit*" << endl;
    cout << "*************************"<< endl;
    cin >> prompt;
    switch(prompt){
      case 0:
                cout << "Enter a string for the process: ";
                cin >> nameOfproc;
                cout << "Determine how much space the process will take: ";
                cin >> numOfunits;
                myList.addProcess(nameOfproc,numOfunits);
                myList.printList();
        break;
      case 1:
                cout << "Enter a string for the process you want to remove: ";
                cin >> nameOfproc;
                cout << "Determine how much space the process will need to remove: ";
                cin >> numOfunits;
                myList.removeProcess(nameOfproc,numOfunits);
                myList.printList();
        break;
      default:
                cout << "Exiting... \n";
                exit = true;
        break;
    }
  }
  return 0;
}
