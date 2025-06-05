#ifndef LIBRARY_H
#define LIBRARY_H

#include <string>
#include "../inc/bookImpl.h"

class Library
{
    public:
        virtual ~Library(){};
        virtual void addBook() = 0;
        virtual void takeBook() = 0;
        virtual void returnBook() = 0;
        virtual void outputLibraryList() = 0;
        virtual void checkBookByName(std::string bookName, bool outputBookInfo = false) = 0;
        virtual void checkBookByAuthor(std::string authorName, bool outputBookInfo = false) = 0;
        virtual void checkBookById(unsigned int bookId, bool outputBookInfo = false) = 0;
        virtual void deleteBook() = 0;
};

#endif // LIBRARY_H