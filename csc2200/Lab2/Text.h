//--------------------------------------------------------------------
//
//  Laboratory 1                                            Text.h
//  **Instructor's Solution**
//  Class declaration for the array implementation of the Text ADT
//
//--------------------------------------------------------------------

#ifndef TEXT_H
#define TEXT_H

#include <stdexcept>
#include <iostream>

using namespace std;

class Text
{
  public:

    // Constructors and operator=
    Text ( const char *charSeq = "" );               // Initialize using char*
    Text ( const Text &other );                      // Copy constructor
    void operator = ( const Text &other );           // Assignment

    // Destructor
    ~Text ();

    // Text operations
    int getLength () const;                          // # characters
    char operator [] ( int n ) const;                // Subscript
    void clear ();                                   // Clear string

    // Output the string structure -- used in testing/debugging
    void showStructure () const;

    //--------------------------------------------------------------------
    // In-lab operations
    // toUpper/toLower operations (Programming Exercise 2)
    Text toUpper( ) const;                           // Create upper-case copy
    Text toLower( ) const;                           // Create lower-case copy

    // Relational operations (Programming Exercise 3)
    bool operator == ( const Text& other ) const;
    bool operator <  ( const Text& other ) const;
    bool operator >  ( const Text& other ) const;

  private:

    // Data members
    int bufferSize;   // Size of the string buffer
    char *buffer;     // Text buffer containing a null-terminated sequence of characters

  // Friends

    // Text input/output operations (In-lab Exercise 1)
    friend istream & operator >> ( istream& input, Text& inputText );
    friend ostream & operator << ( ostream& output, const Text& outputText );

};

#endif
