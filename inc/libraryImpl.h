#ifndef LIBRARY_IMPL_H
#define LIBRARY_IMPL_H

#include <string>
#include "../inc/bookImpl.h"
#include "../inc/library.h"

class LibraryImpl : public Library
{
    private:
    std::vector<Book*> m_books;
    unsigned int idCounter;
    std::vector<int> freedIds;
    public:
        LibraryImpl();
        LibraryImpl(std::string initFileName);
        ~LibraryImpl();
        void addBook() override;
        void takeBook() override;
        void returnBook() override;
        void outputLibraryList() override;
        void checkBookByName(std::string bookName, bool outputBookInfo = false) override;
        void checkBookByAuthor(std::string authorName, bool outputBookInfo = false) override;
        void checkBookById(unsigned int bookId, bool outputBookInfo = false) override;
        void deleteBook() override;
        bool checkIdValidity(std::string& idValue);
        int getIdCounter();
        bool checkIfBookExists(std::string author, std::string title);
        void acquireFreedId(unsigned int& freeId);
};

#endif // LIBRARY_IMPL_H