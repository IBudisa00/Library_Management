#include <iostream>
#include "../inc/book.h"
#include "../inc/bookImpl.h"

/**
 * @brief Set values of created book.
 * 
 * @param author String author's name.
 * @param bookTitle String book's title.
 * @param availability Bool value for availability.
 * @param genre Vector of strings representing genres of book.
 * @param id unsigned int book's unique ID inside library.
 * @param year unsigned int year of book.
 */
BookImpl::BookImpl(std::string author, std::string bookTitle, bool availability, std::vector<std::string> genre, unsigned int id, unsigned int year)
{
    m_author = author;
    m_bookTitle = bookTitle;
    m_availability = availability;
    m_genre = genre;
    m_id = id;
    m_year = year;
}

/**
 * @brief Destructor for deleting BookImpl object.
 */
BookImpl::~BookImpl()
{
}

/**
 * @brief Get availability of book.
 * 
 * @return availability as bool value.
 */
bool BookImpl::getAvailability()
{
    return m_availability;
}

/**
 * @brief Setting availability of book.
 * 
 * @param state Bool value to set.
 */
void BookImpl::setAvailabilityState(bool state)
{
    m_availability = state;
}

/**
 * @brief Get container of genres of book.
 * 
 * @return vector container of strings.
 */
std::vector<std::string>& BookImpl::getGenre()
{
    return m_genre;
}

/**
 * @brief Get book title.
 * 
 * @return book's title as a string.
 */
std::string BookImpl::getBookTitle()
{
    return m_bookTitle;
}

/**
 * @brief Get book's author.
 * 
 * @return author's name as a string.
 */
std::string BookImpl::getBookAuthor()
{
    return m_author;
}

/**
 * @brief Get book's unique ID.
 * 
 * @return book's unique ID as a unisgned int.
 */
unsigned int BookImpl::getBookId()
{
    return m_id;
}

/**
 * @brief Print book's all information, unique ID, title, author's name, genres, availability and year.
 * 
 */
void BookImpl::outputBookInfo()
{
    std::cout << getBookId() << " | " << getBookTitle() << " | " << getBookAuthor() << " | " ;
    for(int i = 0; i < getGenre().size(); i++)
    {
        std::cout << getGenre()[i];
        if(i != getGenre().size() - 1)
            std::cout << ", ";
    }
    std::cout << " | " << getAvailability();
    std::cout << " | " << getYear() << std::endl;
}

/**
 * @brief Get book's year.
 * 
 * @return book's year as a unsigned int.
 */
unsigned int BookImpl::getYear()
{
    return m_year;
}