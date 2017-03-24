//personType.h
  
#include <string> 

using namespace std;

class personType
{
public:
    void print() const;
       //Function to output the first name and last name
       //in the form firstName lastName.
  
    void setName(string first, string last);
      //Function to set firstName and lastName according 
      //to the parameters.
      //Postcondition: firstName = first; lastName = last

	//////////////////////////////////// Defined by me ////////////////////////////////////////////////
	string setFirstname(string);
	string setLastname(string);
	string setMiddlename(string);
	void checkFirst(string);
	void checkLast(string); 
	//////////////////////////////////// Defined by me ////////////////////////////////////////////////
    string getFirstName() const;
      //Function to return the first name.
      //Postcondition: The value of firstName is returned.

    string getLastName() const;
      //Function to return the last name.
      //Postcondition: The value of lastName is returned.

    personType(string first = "", string last = "", string middle = "");
      //Constructor
      //Sets firstName and lastName according to the parameters.
      //The default values of the parameters are null strings.
      //Postcondition: firstName = first; lastName = last  

 private:
    string firstName; //variable to store the first name
    string lastName;  //variable to store the last name
	string middleName; // New member required added here
};

