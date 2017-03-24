//--------------------------------------------------------------------
//
//  Laboratory 4                                       lab04-ex1.cpp
//
//  Copy of example problem in prelab section that demonstrates
//  using an ordered list to read in a set of bank accounts and
//  output the accounts in ascending order based on their account
//  numbers.
//
//--------------------------------------------------------------------

#include <iostream>

#include "OrderedList.cpp"

using namespace std;

class Account {
  public:
      int accountNum;             // (Key) Account number
      float balance;              // Account balance
      int getKey () const
          { return accountNum; }  // Returns the key
};


int main()
{
    OrderedList<Account, int> accounts(20);  // List of accounts
    Account acct;                            // A single account
  
    // Read in information on a set of accounts.

    cout << endl << "Enter account number and balance (EOF to end) : ";
    while ( cin >> acct.accountNum >> acct.balance ) {
        accounts.insert(acct);
        cout << "Enter account number and balance (EOF to end) : ";
    }

    // Output the accounts in ascending order based on their account
    // numbers.
  
    cout << endl;
    if ( !accounts.isEmpty() )
    {
       accounts.gotoBeginning();
       do
       {
           acct = accounts.getCursor();
           cout << acct.accountNum << " " << acct.balance << endl;
       }
       while ( accounts.gotoNext() );
    }

    return 0;
} 

