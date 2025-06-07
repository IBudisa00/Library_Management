#ifndef BOOK_H
#define BOOK_H

#include <string>
#include <vector>

class Book
{
    public:
        virtual ~Book(){};
        virtual bool getAvailability() = 0;
        virtual void setAvailabilityState(bool state) = 0;
        virtual std::vector<std::string>& getGenre() = 0;
        virtual std::string getBookTitle() = 0;
        virtual std::string getBookAuthor() = 0;
        virtual unsigned int getBookId() = 0;
        virtual void outputBookInfo() = 0;
        virtual unsigned int getYear() = 0;
};

#endif // BOOK_H