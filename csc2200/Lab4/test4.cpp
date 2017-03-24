//--------------------------------------------------------------------
//
//  Laboratory 4                                           test4.cpp
//
//  Test program for the operations in the Ordered List ADT
//
//--------------------------------------------------------------------

#include <iostream>
#include <cctype>

#include <conio.h>

using namespace std;

#include "OrderedList.cpp"
#include "config.h"

void printHelp();
void fillTwoLists();

class Record
{
  public: 
    Record () { key = char(0); }
    void setKey(char newKey) { key = newKey; }
    char getKey() const { return key; }
  private:
    char key;
};

//--------------------------------------------------------------------

int main()
{
    OrderedList<Record,char> testList(8), // Test lists
         testList2(8);
    Record testData;                 // List element
    char inputKey;                      // User input key
    char cmd;                           // Input command
    char ch;                            // Input holder

    printHelp();

    do
    {
        testList.showStructure();                     // Output list

        cout << endl << "Command: ";                  // Read command
        cin >> cmd;
	cmd = toupper(cmd);                           // Upper-case only
        if ( cmd == '+'  ||  cmd == '='  ||  cmd == '?' )
           cin >> inputKey;

        switch ( cmd )
        {
          case 'H' : 
               printHelp();
               break;

          case '+' :                                  // insert
               testData.setKey(inputKey);
               cout << "Insert : key = " << testData.getKey()
                    << endl;
               testList.insert(testData);
               break;

          case '?' :                                  // retrieve
               if ( testList.retrieve(inputKey,testData) )
                  cout << "Retrieved : key = "
                       << testData.getKey() << endl;
               else
                  cout << "Not found" << endl;
               break;

          case '=' :                                  // replace
               testData.setKey(inputKey);
               cout << "Replace current element :"
                    << " key = " << testData.getKey() << endl;
               testList.replace(testData);
               break;

          case '-' :                                  // remove
               cout << "Remove current element" << endl;
               testList.remove();
               break;

          case '@' :                                  // getCursor
               cout << "Element marked by the cursor : key = "
                    << testList.getCursor().getKey() << endl;
               break;

          case '<' :                                  // gotoBeginning
               testList.gotoBeginning();
               cout << "Go to beginning of list" << endl;
               break;

          case '>' :                                  // gotoEnd
               testList.gotoEnd();
               cout << "Go to end of list" << endl;
               break;

          case 'N' :                                  // gotoNext
               if ( testList.gotoNext() )
                  cout << "Go to next element" << endl;
               else
                  cout << "Failed -- either at end of list "
                       << "or list is empty" << endl;
               break;

          case 'P' :                                  // gotoPrior
               if ( testList.gotoPrior() )
                  cout << "Go to the prior element" << endl;
               else
                  cout << "Failed -- either at beginning of list "
                       << "or list is empty" << endl;
               break;

          case 'C' :                                  // clear
               cout << "Clear the list" << endl;
               testList.clear();
               break;

          case 'E' :                                  // isEmpty
               if ( testList.isEmpty() )
                  cout << "List is empty" << endl;
               else
                  cout << "List is NOT empty" << endl;
               break;

          case 'F' :                                  // isFull
               if ( testList.isFull() )
                  cout << "List is full" << endl;
               else
                  cout << "List is NOT full" << endl;
               break;

#if LAB4_TEST1
	  case 'M' :           
		  // Merge list 2 into list 1.
		  cin.ignore(100, '\n');	// Clean out cin through end of line
		  testList2.clear();
                  cout << endl << "Enter second list of characters (no spaces) : ";
                  cin.get(ch);
                  while ( ch != '\n' )
                  {
                      testData.setKey(ch);
                      testList2.insert(testData);
                      cin.get(ch);
                  }
		  cout << endl << "List 1 : " << endl;
		  testList.showStructure();
                  cout << endl << "List 2 : " << endl;
                  testList2.showStructure();
		  // Do the merge
		  testList.merge(testList2);
		  cout << endl << "After merge -- List 1 : " << endl;
		  testList.showStructure();
		  cout << endl << "After merge -- List 2 : " << endl;
		  testList2.showStructure();
		  cout << endl;
		  break;
#endif	// LAB4_TEST1

#if LAB4_TEST2
	  case 'S' :           
		  // Check whether list 2 is a subset of list 1.
 		  testList2.clear();
		  cin.ignore(100, '\n');	// Clean out cin through end of line
                  cout << endl << "Enter second list of characters (no spaces) : ";
                  cin.get(ch);
                  while ( ch != '\n' )
                  {
                      testData.setKey(ch);
                      testList2.insert(testData);
                      cin.get(ch);
                  }
		  cout << endl << "List 1 : " << endl;
		  testList.showStructure();
                  cout << endl << "List 2 : " << endl;
                  testList2.showStructure();
		  cout << endl;
		  if ( testList.isSubset(testList2) )
		     cout << "List 2 is a subset of list 1" << endl << endl;
		  else
		     cout << "List 2 is NOT a subset of list 1" << endl << endl;
		  break;
#endif	// LAB4_TEST2

          case 'Q' :                              // Quit test program
               break;

          default :                               // Invalid command
               cout << "Invalid command" << endl;
        }
    }
    while ( cin && cmd != 'Q' );

    if( !cin ) {
	cout << "Input error" << endl;
    }

	_getch();

    return 0;
}

//--------------------------------------------------------------------

void printHelp()
{
    cout << endl << "Commands:" << endl;
    cout << "  H    : Help (displays this message)" << endl;
    cout << "  +key : Insert (or update) element" << endl;
    cout << "  ?key : Retrieve the element with the specified key"
         << endl;
    cout << "  =key : Replace the element marked by the cursor"
         << endl;
    cout << "  -    : Remove the element marked by the cursor"
         << endl;
    cout << "  @    : Display the element marked by the cursor"
         << endl;
    cout << "  <    : Go to the beginning of the list" << endl;
    cout << "  >    : Go to the end of the list" << endl;
    cout << "  N    : Go to the next element" << endl;
    cout << "  P    : Go to the prior element" << endl;
    cout << "  C    : Clear the list" << endl;
    cout << "  E    : Empty list?" << endl;
    cout << "  F    : Full list?" << endl;
    cout << "  M    : Merge list into another list               ("
#if LAB4_TEST1
         << "Active   "
#else
         << "Inactive "
#endif	// LAB4_TEST1
         << ": In-lab Ex. 2)" << endl;
    cout << "  S    : Check whether list is subset of another    ("
#if LAB4_TEST2
         << "Active   "
#else
         << "Inactive "
#endif	// LAB4_TEST2
         << ": In-lab Ex. 3)" << endl;
    cout << "  Q    : Quit the test program" << endl;
    cout << endl;
}

