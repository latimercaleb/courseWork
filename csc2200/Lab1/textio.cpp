//--------------------------------------------------------------------
//
//  Laboratory 1, In-lab Exercise 1                        textio.cpp
//
//  String input/output operations
//
//--------------------------------------------------------------------

#include <iostream>
#include <iomanip>

#include "Text.h"

//--------------------------------------------------------------------

istream & operator >> ( istream &input, Text &inputText )

// Text input function. Extracts a string from istream input and
// returns it in inputText. Returns the state of the input stream.

{
    const int textBufferSize = 256;     // Large (but finite)
    char textBuffer [textBufferSize];   // text buffer

    // Read a string into textBuffer, setw is used to prevent buffer
    // overflow.

    input >> setw(textBufferSize) >> textBuffer;

    // Apply the Text(char*) constructor to convert textBuffer to
    // a string. Assign the resulting string to inputText using the
    // assignment operator.

    inputText = textBuffer;

    // Return the state of the input stream.

    return input;
}

//--------------------------------------------------------------------

ostream & operator << ( ostream &output, const Text &outputText )

// Text output function. Inserts outputText in ostream output.
// Returns the state of the output stream.

{
   output << outputText.buffer;
   return output;
}

