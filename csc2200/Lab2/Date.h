
#ifndef DATE_H
#define DATE_H

#include <stdexcept>
#include <iostream>

#pragma warning( disable : 4290 )

using namespace std;

class Date {
  public:
    Date();
    Date(int day, int month, int year) throw (logic_error);

    int getDay() const;
    int getMonth() const;
    int getYear() const;

    void showStructure() const;

    static bool isLeapYear(int year);
    static int daysInMonth(int month, int year);

    // Programming Exercise 2
    int getDayOfWeek() const;

    // Programming Exercise 3
    bool operator<(const Date& rhs) const;
    bool operator==(const Date& rhs) const;
    bool operator>(const Date& rhs) const;

    friend ostream& operator<<(ostream& out, const Date& date);

  private:
    int day;
    int month;
    int year;

};

#endif
