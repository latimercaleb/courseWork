
#include <stdexcept>
#include <iostream>

using namespace std;

#include "Text.h"
#include "Date.h"

class BlogEntry {
  public:
    BlogEntry();
    BlogEntry(const Text& initAuthor, const Text& initContents);

    Text getAuthor() const;
    Text getContents() const;
    Date getCreateDate() const;
    Date getModifyDate() const;

    void setAuthor(const Text& newAuthor);
    void setContents(const Text& newContents);

    void showStructure() const;

    // Programming Exercise 1
    void printHTML( ostream& out ) const;

  private:
    Text author;
    Date created;
    Date modified;
    Text contents;
};
