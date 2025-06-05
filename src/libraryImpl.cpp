#include <fstream>
#include <iostream>
#include "../inc/define.h"
#include "../inc/library.h"
#include "../inc/libraryImpl.h"

LibraryImpl::LibraryImpl()
{
    idCounter = 0;
}

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
    std::vector<std::string> words;  //sve pohranjeno iz linije rascjepano (znam raspored to navet u dokumentaciji)
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
        initFile.open(outputFileName, std::ios::in);

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
                    if(words[i] == "true")
                        bookAvailability = true;
                    else if(words[i] == "false")
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
                        year = std::stoi(words[i]);
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
        }
    }
    else
    {
        std::cout << "Error | Error while opening init file.\n";
        exit(-1);
    }
    initFile.close();
}

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
            outputFile << " | " << book->getAvailability() << std::endl;
        }
    }
    else
        std::cout << "Error | Error while opening output file " << outputFileName << std::endl;

    outputFile.close();

    for(auto book : m_books)
        delete book;
}

void LibraryImpl::addBook()
{
    std::string author;
    std::string bookTitle;
    std::string genre;
    bool availability;
    std::vector<std::string> genres;
    unsigned int id;
    unsigned int year;
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
        newBook = new BookImpl(author, bookTitle, availability, genres, id, year);
        if(!newBook)
        {
            std::cout << "Error | newBook = NULL. Unsuccessful adding of book.\n";
            return;
        }
        m_books.push_back(newBook);
    }
}

void LibraryImpl::takeBook()
{
    std::string bookTitle;

    std::cout << "\nBook title: ";
    std::cin >> bookTitle;

    for(auto book : m_books)
    {
        if(book->getBookTitle() == bookTitle)
            book->setAvailabilityState(false);
    }
}

void LibraryImpl::returnBook()
{
    std::string bookTitle;

    std::cout << "\nBook title: ";
    std::cin >> bookTitle;

    for(auto book : m_books)
    {
        if(book->getBookTitle() == bookTitle)
            book->setAvailabilityState(true);
    }
    std::cout << "Book '" << bookTitle << "' returned.\n";
}

void LibraryImpl::outputLibraryList()
{
    for(auto book : m_books)
    {
        book->outputBookInfo();
    }
}

void LibraryImpl::checkBookByName(std::string bookName, bool outputBookInfo)
{
    for(auto book : m_books)
    {
        if(book->getBookTitle() == bookName)
        {
            if(outputBookInfo)
                book->outputBookInfo();
        }
    }
    if(outputBookInfo)
        std::cout << "\nBook doesn't exist in library.";
}

void LibraryImpl::checkBookByAuthor(std::string authorName, bool outputBookInfo)
{
    for(auto book : m_books)
    {
        if(book->getBookAuthor() == authorName)
        {
            if(outputBookInfo)
                book->outputBookInfo();
        }
    }
    if(outputBookInfo)
        std::cout << "\nAuthor has no records in library.";
}

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

bool LibraryImpl::checkIdValidity(std::string& idValue)
{
    for(auto& number : idValue)
    {
        if(number < '0' || number > '9')
            return false;
    }
    return true;
}

int LibraryImpl::getIdCounter()
{
    idCounter++;
    return idCounter;
}

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

bool LibraryImpl::checkIfBookExists(std::string author, std::string title)
{
    for(auto book : m_books)
    {
        if(book->getBookAuthor() == author && book->getBookTitle() == title)
            return true;
    }
    return false;
}

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