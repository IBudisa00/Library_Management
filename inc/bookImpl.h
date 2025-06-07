#ifndef BOOK_IMPL_H
#define BOOK_IMPL_H

#include <string>
#include <vector>
#include "../inc/book.h"

class BookImpl : public Book
{
    private:
        std::string m_author;
        std::string m_bookTitle;
        bool m_availability;
        std::vector<std::string> m_genre;
        unsigned int m_id;
        unsigned int m_year;

    public:
        BookImpl(std::string author, std::string bookTitle, bool availability, std::vector<std::string> genre, unsigned int id, unsigned int year);
        ~BookImpl();
        bool getAvailability() override;
        void setAvailabilityState(bool state) override;
        std::vector<std::string>& getGenre() override;
        std::string getBookTitle() override;
        std::string getBookAuthor() override;
        unsigned int getBookId() override;
        void outputBookInfo() override;
        unsigned int getYear() override;
};

#endif // BOOK_IMPL_H