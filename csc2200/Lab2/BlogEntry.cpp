
#include "BlogEntry.h"

BlogEntry::BlogEntry()
{
	Date present;
	created = present;
	modified =present;
}

BlogEntry::BlogEntry(const Text& initAuthor, const Text& initContents)
{
	Date present;
	created = present;
	modified = present;
	author = initAuthor;
	contents = initContents;
}

Text BlogEntry::getAuthor() const
{
	return author;
}

Text BlogEntry::getContents() const
{
	return contents;
}

Date BlogEntry::getCreateDate() const
{
	return created;
}

Date BlogEntry::getModifyDate() const
{
	return modified;
}

void BlogEntry::setAuthor(const Text& newAuthor)
{
	author = newAuthor;
}

void BlogEntry::setContents(const Text& newContents)
{
	contents = newContents;
}

void BlogEntry::printHTML( ostream& out ) const
{
	out << "<html>"<< endl;
	out << "<body>" << endl;
	out << "<h1>" << getAuthor() << "</h1>" << endl;
	out << "<p>" << endl;
	out << getContents() << endl;
	out << "</p>" << endl;
	out << "<p>" << endl;
	out << "Created: " << created << endl;
	out << "</p>" << endl;
	out << "<p>" << endl;
	out << "Last modified: " << modified << endl;
	out << "</p>" << endl;
	out << "</body>" << endl;
	out << "</html>" << endl;
}