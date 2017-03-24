#include<iostream>
#include<string>
using namespace std;

// User defined classes here
class List{
public:
  List(){
    head = new node();
    emptyCount = 1;
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
    node* temp;
    temp = head;

    for(int i = 0; i < max; i++){
      temp->child = new node();
      temp = temp->child;
      emptyCount++;
    }
  }
  void printList(){
    node* temp = head;
    while(temp-> child != NULL){
      cout << temp->procName << " .. " << temp->processCount << endl;
    }
  }
  void addProcess(string t, int num){
    if(num <= emptyCount){
      int count = 0;
      bool flag = 0;
      while(count < num){
        current->procName = t;
        current-> type = flag;
        current = current->child;
        current->processCount = current->processCount + 1;
        num++;
      }
    }
    else{
      cout << "Cannot add any more processes, memory maxed. \n";
      return;
    }
  }
  void removeProcess(string t, int num){
    if(num <= emptyCount){
      if(t == "Empty"){
        cout << "Cannot remove empty memory cells \n";
      }
      else{
        current = head;
        while(current->procName != t){
          current = current->child;
        }
        if(current-> procName == "Empty"){
          cout << "Process name is already deleted \n";
          return;
        }
        else{
          int count = 0;
          bool flag = 1;
          while(count < num){
            current -> procName = "Empty";
            current -> type = flag;
            current->processCount = current->processCount - 1;
            current = current->child;
          }
        }
      }
    }
    else{
      cout << "Cannot remove more than maximum memory for processes \n";
      return;
    }
  }
  int sizeOfProcess(){
    return processCount;
  }
private:
  class node{
  public:
    node(){
        procName = "Empty";
        child = NULL;
        procCount = 1;
    }

    ~node(){
          procName = "Empty";
          child = NULL;
    }

    int procCount;
    string procName;
    bool type;
    node* child;

  };

  node* head;
  node* current;
  int emptyCount;

};

int main(){
  //cout << "Hello world \n"; // Test of makefile and program
  List myList;
  string nameOfproc;
  int numOfunits;
  int SIZE; // Var for the global size of the list declared by the user in the beginning and does not change
  cout << "Enter the total amount of memory for the processes: ";
  cin >> SIZE;

  myList.makeList(SIZE);
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
