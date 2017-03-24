//--------------------------------------------------------------------
//
//  Laboratory 2                                           test2.cpp
//
//  Test program for the operations in the Date and BlogEntry ADTs.
//
//--------------------------------------------------------------------

#include <iostream>
#include "BlogEntry.h"
#include "config.h"

using namespace std;

void print_help() {
    cout << endl << "Tests:" << endl;

    cout << "  1  Tests the Date constructors";
#if !LAB2_TEST1
    cout << " (inactive)";
#endif
    cout << endl;

    cout << "  2  Tests the Date accessors/getters";
#if !LAB2_TEST2
    cout << " (inactive)";
#endif
    cout<< endl;

    cout << "  3  Tests the Date isLeapYear function";
#if !LAB2_TEST3
    cout << " (inactive)";
#endif
    cout << endl;

    cout << "  4  Tests the daysInMonth function";
#if !LAB2_TEST4
    cout << " (inactive)";
#endif
    cout << endl;

    cout << "  5  Test the Date operator<< function";
#if !LAB2_TEST5
    cout << " (inactive)";
#endif
    cout << endl;

    cout << "  6  Test the BlogEntry constructors";
#if !LAB2_TEST6
    cout << " (inactive)";
#endif
    cout << endl;

    cout << "  7  Test the BlogEntry getters/setters";
#if !LAB2_TEST7
    cout << " (inactive)";
#endif
    cout << endl;

    cout << "  8  Tests the Date printHTML function (ex. 1)";
#if !LAB2_TEST9
    cout << " (inactive)";
#endif
    cout << endl;

    cout << "  9  Tests the Date getDayOfWeek function (ex. 2)";
#if !LAB2_TEST9
    cout << " (inactive)";
#endif
    cout << endl;

    cout << " 10  Tests the Date relational operators (ex. 3)";
#if !LAB2_TEST10
    cout << " (inactive)";
#endif
    cout << endl;
    cout << endl << "Select the test to run : ";
}

void inactive_test(char selection) {
    cout << "'" << selection << "' specifies an inactive test." << endl;
    cout << "Change config.h to activate this test, recompile, and run again." << endl;

    exit(1);
}

/*
 * This is a fun C++ function that takes advantage of advanced C++
 * knowledge.  If you don't understand it, that's okay.  You can be
 * rest assured that it does the right thing and let it do its magic.
 *
 * The function takes a pointer to a member function of the Date class
 * that returns a boolean and receives a constant reference to a Date
 * object.  This is the perfect signature for a relational operator.
 * The function uses this pointer to call the function passed to it
 * (see the weird (object.*fcn)(parameter) syntax).  The ability of
 * this function to take a member function as a parameter and use it
 * allows this function to be written once and reused for all the
 * relational operators.  Yeah!
 */
void test_date_compare(bool (Date::*fcn)(const Date& rhs) const) {
    Date present,
	 past(31, 12, 2000),
	 future(29, 2, 2096);

    cout << "\tpast\tpresent\tfuture" << endl;
    cout << "past\t";
    cout << (past.*fcn)(past);
    cout << "\t";
    cout << (past.*fcn)(present);
    cout << "\t";
    cout << (past.*fcn)(future);
    cout << endl;
    cout << "present\t";
    cout << (present.*fcn)(past);
    cout << "\t";
    cout << (present.*fcn)(present);
    cout << "\t";
    cout << (present.*fcn)(future);
    cout << endl;
    cout << "future\t";
    cout << (future.*fcn)(past);
    cout << "\t";
    cout << (future.*fcn)(present);
    cout << "\t";
    cout << (future.*fcn)(future);
    cout << endl;
}

int main(int argc, char **argv) {
    print_help();

    int selection;
    cin >> selection;
    cout << endl;

    Date present,
	 past(31, 12, 2000),
	 future(29, 2, 2096);
    BlogEntry empty,
	      full("Tester", "This is a small test.");
    int day, month, year,
        day2, month2, year2;

    switch (selection) {
      case 1:			// Date constructors
#if LAB2_TEST1
	cout << "Current date: ";
	present.showStructure();
	cout << "Last day of twentieth century (Dec 31, 2000): ";
	past.showStructure();
	cout << "Last leap day of twenty-first century (Feb 29, 2096): ";
	future.showStructure();
	cout << endl;
#else
	inactive_test(selection);
#endif
	break;

      case 2:			// Date getters
#if LAB2_TEST2
	cout << "Testing getters for 12/31/2000: " 
	     << " Month = " << past.getMonth() << ", "
	     << " Day = " << past.getDay() << ", "
	     << " Year = " << past.getYear() 
	     << endl;
#else
	inactive_test(selection);
#endif
	break;

      case 3:			// isLeapYear
#if LAB2_TEST3
	// Is not a leap year -- std multiple of 4 rule
        if(Date::isLeapYear(2001)) {
	    cout << "** Incorrectly says 2001 is a leap year." << endl;
	} else {
	    cout << "Correctly says 2001 is NOT a leap year." << endl;
	}
	// Is a leap year -- std multiple of 4 rule
        if(Date::isLeapYear(2004)) {
	    cout << "Correctly says 2004 IS a leap year." << endl;
	} else {
	    cout << "** Incorrectly says 2004 is NOT a leap year." << endl;
	}
	// Is not a leap year -- multiple of 100 rule
        if(Date::isLeapYear(2100)) {
	    cout << "** Incorrectly says 2100 IS a leap year." << endl;
	} else {
	    cout << "Correctly says 2100 is NOT a leap year." << endl;
	}
	// Is a leap year -- multiple of 400 rule
        if(Date::isLeapYear(2000)) {
	    cout << "Correctly says 2000 IS a leap year." << endl;
	} else {
	    cout << "** Incorrectly says 2000 is NOT a leap year." << endl;
	}
	cout << endl;
#else
	inactive_test(selection);
#endif
	break;

      case 4:			// daysInMonth
#if LAB2_TEST4
	cout << "Testing < operator" << endl;
	cout << "April 2000 has " << Date::daysInMonth(4, 2000) << " days (30)." << endl;	
	cout << "February 2001 has " << Date::daysInMonth(2, 2001) << " days (28)." << endl;	
	cout << "January 2002 has " << Date::daysInMonth(1, 2002) << " days (31)." << endl;	
	cout << endl;
#else
	inactive_test(selection);
#endif
	break;

      case 5:			// Date operator<<
#if LAB2_TEST5
	cout << "Printing data via showStructure" << endl;
	past.showStructure();
	cout << "Printing date via operator<< (should be very similar to showStructure." << endl;
	cout << past << endl;
	cout << endl;
#else
	inactive_test(selection);
#endif
	break;

      case 6:			// BlogEntry constructors
#if LAB2_TEST6
	cout << "Empty blog entry:" << endl;
	empty.showStructure();
	cout << endl;
	cout << "Test blog entry:" << endl;
	full.showStructure();
	cout << endl;
#else
	inactive_test(selection);
#endif
	break;

      case 7:			// BlogEntry getters/setters
#if LAB2_TEST7
	cout << "Tester starts looking like:" << endl;
	full.showStructure();
	cout << endl;

	cout << "Now setting author ('New Test') and new contents ('Brand new contents')" << endl;
	full.setAuthor("New Test");
	full.setContents("Brand new contents");
	cout << "New test looks like:" << endl;
	full.showStructure();
	cout << endl;

	cout << "Now getting author, contents, created, and modified" << endl;
	cout << "getAuthor(): " << full.getAuthor() << endl;
	cout << "getContents(): " << full.getContents() << endl;
	cout << "getCreated(): " << full.getCreateDate() << endl;
	cout << "getModified(): " << full.getModifyDate() << endl;
	cout << endl;
#else
	inactive_test(selection);
#endif
	break;

      case 8:
#if LAB2_TEST8
	cout << "Blog's HTML: " << endl;
	full.printHTML( cout );
#else
	inactive_test(selection);
#endif
	break;

      case 9:
#if LAB2_TEST9
	cout << "Enter day (e.g, 1-31): ";
	cin >> day;
	cout << "Enter month (e.g, 1-12): ";
	cin >> month;
	cout << "Enter year (>1901): ";
	cin >> year;

	cout << "Day of week is: " << Date(day, month, year).getDayOfWeek() << endl;
#else
	inactive_test(selection);
#endif
	break;

      case 10:
#if LAB2_TEST10
	cout << "Testing < operator" << endl;
	test_date_compare(&Date::operator<);
	cout << endl;
	cout << "Testing == operator" << endl;
	test_date_compare(&Date::operator==);
	cout << endl;
	cout << "Testing > operator" << endl;
	test_date_compare(&Date::operator>);
#else
	inactive_test(selection);
#endif
	cout << endl;
	break;

      default:
	cout << "'" << selection << "' specifies an invalid test" << endl;
	return 1;
    }

    return 0;
}

