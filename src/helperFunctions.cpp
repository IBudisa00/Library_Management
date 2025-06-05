#include <iostream>
#include <vector>
#include "../inc/library.h"
#include "../inc/libraryImpl.h"
#include "../inc/helperFunctions.h"

void printMenu()
{
    std::cout << "0 Exit\n";
    std::cout << "1 Add book\n";
    std::cout << "2 Delete book\n";
    std::cout << "3 Output all books\n";
    std::cout << "4 Borrow book\n";
    std::cout << "5 Search book\n";
    std::cout << "6 Return book\n";
    std::cout << "Select command: ";
}

void searchBookHandler(Library* lib)
{
    std::string parameter1, parameter2;

    std::cout << "\nSelect how to search for a book: ";
    std::cout << "\n1 by Title";
    std::cout << "\n2 by Author";
    std::cout << "\n3 by Unique ID";
    std::cin >> parameter1;
    std::cout << "\nValue to search: ";
    std::cin >> parameter2;
    
    if(parameter1 == "1")
    {
        if(dynamic_cast<LibraryImpl*>(lib))
            lib->checkBookByName(parameter2, true);
        else
            std::cout << "\nUnknown library type.";
    }
    else if(parameter1 == "2")
    {
        if(dynamic_cast<LibraryImpl*>(lib))
            lib->checkBookByAuthor(parameter2, true);
        else
            std::cout << "\nUnknown library type.";
    }
    else if(parameter1 == "3")
    {
        if(dynamic_cast<LibraryImpl*>(lib))
            lib->checkBookById(std::stoi(parameter2), true);
        else
            std::cout << "\nUnknown library type.";
    }
    else
        std::cout << "\nInvalid input!";
}
