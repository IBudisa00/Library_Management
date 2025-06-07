#include <fstream>
#include <iostream>
#include "../inc/define.h"
#include "../inc/library.h"
#include "../inc/libraryImpl.h"
#include "../inc/helperFunctions.h"


/**
 * @brief Set ID's counter for library books.
 * 
 */
LibraryImpl::LibraryImpl()
{
    idCounter = 0;
}

/**
 * @brief Constructor to populate library with books by
 * parsing starting textual file. In case of any book which
 * would have invalid data won't be added into library.
 * 
 * @param initFileName The string for a file name used to initialize starting library data.
 */
LibraryImpl::LibraryImpl(std::string initFileName)
{
    std::ifstream initFile;
    std::string lineText;
    unsigned int bookId;
    std::string genre;
    std::string bookTitle;
    std::string bookAuthor;
    std::vector<std::string> bookGenres;
    unsigned int id;
    unsigned int year;
    bool bookAvailability;
    std::string target = " | ";
    std::vector<std::string> words;
    int start = 0;
    int last = 0;
    bool firstRun = true;
    bool lineBeingParsed = true;
    bool allowAddingBook =  true;
   
    idCounter = 0;

    if(initFileName.substr(initFileName.size() - 4) != ".txt")
    {
        std::cout << "Error | Init file name not valid.\n";
        exit(-1);
    }
    else
    {
        initFileName = "../" + initFileName;
        initFile.open(initFileName, std::ios::in);
    }

    if(initFile.is_open())
    {
        while(getline(initFile, lineText))
        {
            while(lineBeingParsed)
            {
                if(firstRun)
                {
                    last = lineText.find(target);
                    firstRun = false;
                }
                words.push_back(lineText.substr(start, last - start));
                start = last + target.size();
                last = lineText.find(target, start);

                if(last == std::string::npos)
                    lineBeingParsed = false;
            }
            words.push_back(lineText.substr(start));
            firstRun = true;
            lineBeingParsed = true;
            start = 0;
            last = 0;
           
            for(int i = 0; i < words.size(); i++)
            {
                if(i == 0)
                {
                    if(!checkIdValidity(words[i]))
                    {
                        std::cout << "Error | Unexpected value '" << words[i] << "' for book ID.\n";
                        allowAddingBook = false;
                    }
                    else
                        bookId = std::stoi(words[i]);
                }
                else if(i == 1)
                {
                    bookTitle = words[i];
                }
                else if(i == 2)
                {
                    bookAuthor = words[i];
                }
                else if(i == 3)
                {
                    for(auto& letter : words[i])
                    {
                        if(letter != ' ' || letter != ',')
                            genre += letter;
                        else
                        {
                            if(!genre.empty())
                            {
                                bookGenres.push_back(genre);
                                genre.clear();
                            }
                        }
                    }
                    if(!genre.empty())
                    {
                        bookGenres.push_back(genre);
                        genre.clear();
                    }
                }
                else if(i == 4)
                {
                    if(words[i] == "1")
                        bookAvailability = true;
                    else if(words[i] == "0")
                        bookAvailability = false;
                    else
                    {
                        std::cout << "Error | Unexpected value '" << words[i] << "' for availability.\n";
                        allowAddingBook = false;
                    }
                }
                else
                {
                    if(!checkIdValidity(words[i]))
                    {
                        std::cout << "Error | Unexpected value '" << words[i] << "' for year.\n";
                        allowAddingBook = false;
                    }
                    else
                    {
                        if(checkDigits(words[i]))
                            year = std::stoi(words[i]);
                        else
                        {
                            std::cout << "Error | Invalid character in year '" << year <<"'.\n";
                            allowAddingBook = false;
                        }
                        if(year > 2025)
                        {
                            std::cout << "You are moving through time. That book doesn't exist, yet.\n";
                            allowAddingBook = false;
                        }
                    }  
                }
            }
            id = getIdCounter(); // ovo je init pa moze tu doc bez provjere sto je free jer je ovo na pocetku tek
            if(allowAddingBook)
                m_books.push_back(new BookImpl(bookAuthor, bookTitle, true, bookGenres, id, year));
            else
                allowAddingBook = true;
               
            words.clear();
            bookGenres.clear();
        }
    }
    else
    {
        std::cout << "Error | Error while opening init file.\n";
        exit(-1);
    }
    initFile.close();
}

/**
 * @brief Destructor of library where before deleting library
 * all data is sent to hardcoded output file.
 * 
 */
LibraryImpl::~LibraryImpl()
{
    std::ofstream outputFile;
   
    outputFile.open(outputFileName, std::ios::out | std::ios::trunc);
   
    if(outputFile.is_open())
    {
        for(auto book : m_books)
        {    
            outputFile << book->getBookId() << " | " << book->getBookTitle() << " | " << book->getBookAuthor() << " | ";
            for(int i = 0; i < book->getGenre().size(); i++)
            {
                outputFile << book->getGenre()[i];
                if(i != book->getGenre().size() - 1)
                    outputFile << ", ";
            }
            outputFile << " | " << book->getAvailability();
            outputFile << " | " << book->getYear() << std::endl;
        }
    }
    else
        std::cout << "Error | Error while opening output file " << outputFileName << std::endl;

    outputFile.close();

    for(auto book : m_books)
        delete book;
}

/**
 * @brief Adding book into library, in case of ivalid
 * data adding is cancelled and user is warned of issue.
 * 
 */
void LibraryImpl::addBook()
{
    std::string author;
    std::string bookTitle;
    std::string genre;
    bool availability;
    std::vector<std::string> genres;
    unsigned int id;
    std::string year;
    Book* newBook = NULL;
    bool genresBeingAdded = true;
    bool addGenre = true;
    bool bookAlreadyExists = false;

    std::cout << "Author's name: ";
    std::cin >> author;
    std::cout << "\nBook title: ";
    std::cin >> bookTitle;
    std::cout << "\nYear: ";
    std::cin >> year;
   
    if(!checkDigits(year))
    {
        std::cout << "\nError | Invalid year.";
        return;
    }
    else
    {
        if(std::stoi(year) > 2025)
        {
            std::cout << "\nError | Year unavailable.";
            return;
        }
    }
   
    std::cout << "\n*To stop adding genres type 'STOP'";
    while(genresBeingAdded)
    {
        std::cout << "\nGenre: ";
        std::cin >> genre;

        if(genre == "STOP")
            break;

        for(auto& category : genres)
        {
            if(category == genre)
            {
                std::cout << "\nGenre already added.";
                addGenre = false;
            }
        }
        if(addGenre)
            genres.push_back(genre);
        else
            addGenre = true;
    }

    if(checkIfBookExists(author, bookTitle))
    {
        std::cout << "\nBook already exists in database/library.";
        return;
    }
    else
    {
        availability = true;
        acquireFreedId(id);
        if(!genres.empty())
        {
            newBook = new BookImpl(author, bookTitle, availability, genres, id, std::stoi(year));
            if(!newBook)
            {
                std::cout << "Error | newBook = NULL. Unsuccessful adding of book.\n";
                return;
            }
            m_books.push_back(newBook);
        }
        else
            std::cout << "Error | Genres category empty.\n";
    }
}

/**
 * @brief Mark book's availability state to false if book
 * is possible to be taken (availability is true at that moment).
 * 
 */
void LibraryImpl::takeBook()
{
    std::string bookTitle;

    std::cout << "\nBook title: ";
    std::cin >> bookTitle;

    for(auto book : m_books)
    {
        if(book->getBookTitle() == bookTitle)
        {
            if(book->getAvailability())
                book->setAvailabilityState(false);
            else
                std::cout << "\nBook is not available at the moment.";
            return;
        }
    }
}

/**
 * @brief Mark book's availability state as true if
 * previous state was true.
 * 
 */
void LibraryImpl::returnBook()
{
    std::string bookTitle;

    std::cout << "\nBook title: ";
    std::cin >> bookTitle;

    for(auto book : m_books)
    {
        if(book->getBookTitle() == bookTitle)
        {    
            book->setAvailabilityState(true);
            std::cout << "Book '" << bookTitle << "' returned.\n";
            return;
        }
    }
}

/**
 * @brief Printing all books data contained in library.
 * 
 */
void LibraryImpl::outputLibraryList()
{
    for(auto book : m_books)
    {
        book->outputBookInfo();
    }
}

/**
 * @brief Print data for book specified by user defined
 * name of wanted book. In case of no data being found user
 * is warned about it.
 * 
 * @param bookName String presenting book title.
 * @param outputBookInfo optional bool value to output data of certain book.
 */
void LibraryImpl::checkBookByName(std::string bookName, bool outputBookInfo)
{
    bool foundSomething = false;
    for(auto book : m_books)
    {
        if(book->getBookTitle() == bookName)
        {
            if(outputBookInfo)
                book->outputBookInfo();
            foundSomething = true;
        }
    }
    if(outputBookInfo && !foundSomething)
        std::cout << "\nBook doesn't exist in library.";
}

/**
 * @brief Print books by certain author specified by user.
 * In case of no data being found user is warned about it.
 * 
 * @param authorName String presenting author's name.
 * @param outputBookInfo optional bool value to output data of certain book.
 */
void LibraryImpl::checkBookByAuthor(std::string authorName, bool outputBookInfo)
{
    bool foundSomething = false;
    for(auto book : m_books)
    {
        if(book->getBookAuthor() == authorName)
        {
            if(outputBookInfo)
                book->outputBookInfo();
            foundSomething = true;
        }
    }
    if(outputBookInfo && !foundSomething)
        std::cout << "\nAuthor has no records in library.";
}

/**
 * @brief Print book's data defined by unique ID specified by user.
 * In case of no data being found user is warned about it.
 * 
 * @param bookId unsigned int presenting book's unique ID.
 * @param outputBookInfo optional bool value to output data of certain book.
 */
void LibraryImpl::checkBookById(unsigned int bookId, bool outputBookInfo)
{
    for(auto book : m_books)
    {
        if(book->getBookId() == bookId)
        {
            if(outputBookInfo)
                book->outputBookInfo();
            return;
        }
    }
    if(outputBookInfo)
        std::cout << "\nBook with ID " << bookId << " doesn't exist in library.";
}

/**
 * @brief Checks if unique ID is composed only out of digits.
 * 
 * @param idValue As a string to be checked.
 * @return true if the string contains only digits, false otherwise.
 */
bool LibraryImpl::checkIdValidity(std::string& idValue)
{
    for(auto& number : idValue)
    {
        if(number < '0' || number > '9')
            return false;
    }
    return true;
}

/**
 * @brief Get ID counter at the moment. Increments counter to be
 * ready for next book that is going to be added.
 * 
 * @return int value of incremented ID which is used for next book.
 */
int LibraryImpl::getIdCounter()
{
    idCounter++;
    return idCounter;
}

/**
 * @brief Delete book specified by author's name and book title.
 * In case of book composed of that data combination not existing
 * user is warned about failed removal.
 * 
 */
void LibraryImpl::deleteBook()
{
    std::string author;
    std::string bookTitle;

    std::cout << "Author's name: ";
    std::cin >> author;
    std::cout << "\nBook title: ";
    std::cin >> bookTitle;

    for(int i = 0; i < m_books.size(); i++)
    {
        if(m_books[i]->getBookAuthor() == author && m_books[i]->getBookTitle() == bookTitle)
        {
            freedIds.push_back(m_books[i]->getBookId());
            m_books.erase(m_books.begin() + i);
            std::cout << "\nBook removed.";
            return;
        }
    }
    std::cout << "\nBook '" << bookTitle << "' by author " << author << " doesn't exist.";
}

/**
 * @brief Check if book defined by author's name and title exists.
 * 
 * @param author name stored as string.
 * @param title of a book as string.
 * @return true if the book of specified author exists, false otherwise.
 */
bool LibraryImpl::checkIfBookExists(std::string author, std::string title)
{
    for(auto book : m_books)
    {
        if(book->getBookAuthor() == author && book->getBookTitle() == title)
            return true;
    }
    return false;
}

/**
 * @brief Get next available ID and store it into function parameter.
 * If there is already deleted book's ID available that ID will be used,
 * otherwise next ID in line is acquired.
 * 
 * @param freeId unsigned int as reference used to acquire available ID.
 */
void LibraryImpl::acquireFreedId(unsigned int& freeId)
{
    if(freedIds.empty())
        freeId = getIdCounter();
    else
    {
        freeId = freedIds[0];
        freedIds.erase(freedIds.begin());        
    }
}