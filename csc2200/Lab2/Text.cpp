//--------------------------------------------------------------------
//
//  Laboratory 1                                          Text.cpp
//
//  SOLUTION: Array implementation of the String ADT
//
//--------------------------------------------------------------------

#include <iostream>
#include <iomanip>
#include <cassert>
#include <cstring>
#include "Text.h"

//--------------------------------------------------------------------

Text::Text(const char *charSeq)

// Creates a string containing the delimited sequence of characters
// charSeq. Allocates enough memory for this string.

{
	bufferSize = strlen(charSeq) + 1;   // Account for null

	try
	{
		buffer = new char[bufferSize];   // Allocate memory
	}
	catch (bad_alloc &e)
	{
		cerr << "Text::Text(const char): bad_alloc: buffer == 0\n";
		throw bad_alloc();
	}

	strcpy(buffer, charSeq);             // Copy the string
}

//--------------------------------------------------------------------

Text::Text(const Text &valueText)

// Copy constructor, creates a copy of valueText. Called whenever
//
//   1) a string is passed to a function using call by value,
//   2) a function returns a string, or
//   3) a string is initialized using another string -- as in the
//      declarations:
//                      Text str1("First"),
//                             str2 = str1;

	: bufferSize(valueText.bufferSize)

{
	buffer = new char[bufferSize];    // Allocate memory
	strcpy(buffer, valueText.buffer);   // Copy the string
}

//--------------------------------------------------------------------

void Text:: operator = (const Text& other)

// Assigns other to a Text object.

{
	int rlen = other.getLength();   // Length of other

	if (rlen >= bufferSize)          // If other will not fit
	{
		delete[] buffer;                    // Release buffer and
		bufferSize = rlen + 1;               //  allocate a new
		buffer = new char[bufferSize];    //  (larger) buffer
	}

	strcpy(buffer, other.buffer);   // Copy other
}

//--------------------------------------------------------------------

Text:: ~Text()

// Frees the memory used by the Text object buffer.

{
	delete[] buffer;
}

//--------------------------------------------------------------------

int Text::getLength() const

// Returns the number of characters in the Text object buffer (excluding the
// null character).

{
	return strlen(buffer);
}

//--------------------------------------------------------------------

char Text:: operator [] (int n) const

// Returns the nth character in a Text object -- where the characters are
// numbered beginning with zero.

{
	if (n >= 0 && n <= getLength())
		return buffer[n];
	else
		return '\0';
}

//--------------------------------------------------------------------

void Text::clear()

// Clears a Text object -- i.e., makes it empty. The buffer size
// remains unchanged.

{
	buffer[0] = '\0';
}

//--------------------------------------------------------------------

void Text::showStructure() const

// Outputs the characters in a string. This operation is intended for
// testing/debugging purposes only.

{
	int j;   // Loop counter

	for (j = 0; j < bufferSize; j++)
		cout << j << "\t";
	cout << endl;
	for (j = 0; buffer[j] != '\0'; j++)
		cout << buffer[j] << "\t";
	cout << "\\0" << endl;
}

//--------------------------------------------------------------------
//
//                        In-lab operations
//
//--------------------------------------------------------------------

//istream & operator >> (istream &input, Text &inputText)
//
//// (In-lab 1)  Text input function. Extracts a string from istream input and
//// returns it in inputText. Returns the state of the input stream.
//
//{
//	const int textBufferSize = 256;     // Large (but finite)
//	char textBuffer[textBufferSize];   // text buffer
//
//									   // Read a string into textBuffer, setw is used to prevent buffer
//									   // overflow.
//
//	input >> setw(textBufferSize) >> textBuffer;
//
//	// Apply the Text(char*) constructor to convert textBuffer to
//	// a string. Assign the resulting string to inputText using the
//	// assignment operator.
//
//	inputText = textBuffer;
//
//	// Return the state of the input stream.
//
//	return input;
//}

//--------------------------------------------------------------------

//ostream & operator << (ostream &output, const Text &outputText)
//
//// (In-lab 1)  Text output function. Inserts outputText in ostream output.
//// Returns the state of the output stream.
//
//{
//	output << outputText.buffer;
//	return output;
//}


//--------------------------------------------------------------------

Text Text::toUpper() const

// (In-lab 2)  Returns a Text object containing an upper-case copy of Text object.

{
	const int length = strlen(buffer);
	char *tempBuf;
	tempBuf = new char[length + 1];
	strcpy(tempBuf, buffer);
	for (int i = 0; i<length; i++) {
		tempBuf[i] = toupper(tempBuf[i]);
	}

	// Option 1: Correct. Create correctly initialized object, and return object reference by
	// dereferencing new object's address.
	//return Text( tempBuf );

	// Option 2: Also correct. Wordier, but perhaps easier for students to follow.
	Text upper(tempBuf);
	return upper;
}

//--------------------------------------------------------------------

Text Text::toLower() const

// (In-lab 2)  Returns a Text object containing a lower-case copy of Text object.

{
	int length = strlen(buffer);
	char *tempBuf = new char[length + 1];
	strcpy(tempBuf, buffer);
	for (int i = 0; i<length; i++) {
		tempBuf[i] = tolower(tempBuf[i]);
	}
	return Text(tempBuf);
}


//--------------------------------------------------------------------

bool Text::operator == (const Text &other) const

// (In-lab 3)  Equality relational operator. Returns true if leftText is equal to
// other. Otherwise returns false.

{
	return (strcmp(buffer, other.buffer) == 0);
}

//--------------------------------------------------------------------

bool Text::operator < (const Text &other) const

	// (In-lab 3)  "Less than" relational operator. Returns true if leftText is less
	// than other. Otherwise returns false.

{
	return (strcmp(buffer, other.buffer) < 0);
}

//--------------------------------------------------------------------

bool Text::operator > (const Text &other) const

// (In-lab 3)  "Greater than" relational operator. Returns true if leftText is
// greater than other. Otherwise returns false.

{
	return (strcmp(buffer, other.buffer) > 0);
}

