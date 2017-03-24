
#include "Text.h"
#include<cassert>

Text::Text ( const char *charSeq )
{
	bufferSize = strlen(charSeq);
	buffer = new char[bufferSize + 1];
	strcpy(buffer,charSeq);
}

Text::Text ( const Text &other )
{
	*this = other;
}

void Text::operator = ( const Text &other )
{
	if (this != &other)
	{
		strcpy(buffer,other.buffer);
		bufferSize = other.bufferSize;
	}
}

Text::~Text ()
{
	delete [] buffer;
	
}

int Text::getLength () const
{
	return bufferSize;
}

char Text::operator [] ( int n ) const
{
	assert(0 <= n && n < bufferSize);
	return buffer[n];
}

void Text::clear ()
{
	strcpy(buffer,"" );
	memcpy(buffer, "",2);
	/*delete[] buffer;
	char *temp = "";
	int tsize=strlen(temp);
	bufferSize = tsize;
	buffer = new char[tsize+1];
	strcpy(buffer,temp);*/
}

void Text::showStructure () const
{
	cout << buffer << endl;
}

Text Text::toUpper( ) const
{
	Text temp;
	strcpy(temp.buffer, buffer);
	temp.bufferSize = bufferSize;
	for (int i = 0; i < bufferSize; i++) {
		strcpy(temp.buffer[i], toupper(temp.buffer[i]));
	}
	/*int t = 0;
	while (buffer[t]) {
		putchar(toupper(buffer[t]));
		t++;
	}*/
	return temp;
}

Text Text::toLower( ) const
{
	Text temp;
	int t = 0;
	while (buffer[t]) {
		putchar(tolower(buffer[t]));
		t++;
	}
	return temp;
}

bool Text::operator == ( const Text& other ) const
{
	Text tempText;
	tempText.bufferSize = other.bufferSize;
	tempText.buffer = new char[tempText.bufferSize + 1];
	strcpy(other.buffer, tempText.buffer);
	return true;
}

bool Text::operator <  ( const Text& other ) const
{
	if (bufferSize < other.bufferSize)
		return true;
	else
	return false;
}

bool Text::operator >  ( const Text& other ) const
{
	if (bufferSize > other.bufferSize)
		return true;
	else
	return false;
}
