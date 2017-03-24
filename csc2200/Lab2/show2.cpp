
#include "Date.h"
#include "BlogEntry.h"

/**
 * show2.cpp: contains the showStructure member functions for the
 *   Date and BlogEntry classes. Please copy and paste them into the
 *   respective implementation files for each class.
 */


/**
 * showStructure for Date. Feel free to include this
 *   as part of your solution in Date.cpp.
 */
void Date::showStructure() const {
    // Outputs data in same form as operator<<.
    // NOTE: could do "cout << *this << endl", but that would not compile
    // if operator<< has not been defined.
    cout << month << "/" << day << "/" << year << endl;
}

/**
 * showStructure for BlogEntry. Feel free to include this
 *   as part of your solution in BlogEntry.cpp.
 */
// requires operator<<() defined for Date
void BlogEntry::showStructure() const {
    cout << "Author: " << author << endl;
    cout << "Created: " << created << endl;
    cout << "Modified: " << modified << endl;
    cout << "Content: " << contents << endl;
}

