#include <iostream>
#include "../inc/book.h"
#include "../inc/bookImpl.h"

BookImpl::BookImpl(std::string author, std::string bookTitle, bool availability, std::vector<std::string> genre, unsigned int id, unsigned int year)
{
    m_author = author;
    m_bookTitle = bookTitle;
    m_availability = availability;
    m_genre = genre;
    m_id = id;
    m_year = year;
}

BookImpl::~BookImpl()
{
}

bool BookImpl::getAvailability()
{
    return m_availability;
}

void BookImpl::setAvailabilityState(bool state)
{
    m_availability = state;
}

std::vector<std::string>& BookImpl::getGenre()
{
    return m_genre;
}

std::string BookImpl::getBookTitle()
{
    return m_bookTitle;
}

std::string BookImpl::getBookAuthor()
{
    return m_author;
}

unsigned int BookImpl::getBookId()
{
    return m_id;
}

void BookImpl::outputBookInfo()
{
    std::cout << getBookId() << " | " << getBookTitle() << " | " << getBookAuthor();
    for(int i = 0; i < getGenre().size(); i++)
    {
        std::cout << getGenre()[i];
        if(i != getGenre().size() - 1)
            std::cout << ", ";
    }
    std::cout << " | " << getAvailability() << std::endl;
}