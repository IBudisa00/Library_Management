#include <iostream>
#include <vector>
#include "../inc/library.h"
#include "../inc/libraryImpl.h"
#include "../inc/helperFunctions.h"


/**
 * @brief Prints menu as a help legend for user.
 * 
 */
void printMenu()
{
    std::cout << "\n0 Exit\n";
    std::cout << "1 Add book\n";
    std::cout << "2 Delete book\n";
    std::cout << "3 Output all books\n";
    std::cout << "4 Borrow book\n";
    std::cout << "5 Search book\n";
    std::cout << "6 Return book\n";
    std::cout << "Select command: ";
}

/**
 * @brief Search book based on category specified by user.
 * Available categories as by title, author's name and unique ID.
 * In case of value presented by user which would prove as invalid
 * user gets warned without being presented a book's information.
 * 
 * @param lib Pointer to a central library where we search for a book.
 */
void searchBookHandler(Library* lib)
{
    std::string parameter1, parameter2;

    std::cout << "\nSelect how to search for a book: ";
    std::cout << "\n1 by Title";
    std::cout << "\n2 by Author";
    std::cout << "\n3 by Unique ID\n";
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

/**
 * @brief Checks if the string contains only digits.
 * 
 * @param number The input string to check.
 * @return true if the string contains only digits, false otherwise.
 */
bool checkDigits(std::string& number)
{
    bool validNumber = true;
   
    for(auto& letter : number)
    {
        if(letter < '0' || letter > '9')
            validNumber = false;
    }
    return validNumber;
}
