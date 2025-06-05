#include <iostream>
#include "../inc/library.h"
#include "../inc/libraryImpl.h"
#include "../inc/helperFunctions.h"
#include "../inc/define.h"


bool programRunning = true;

int main (int argc, char *argv[])
{
    Library* library = new LibraryImpl();
    int command;

    printMenu();
    while(programRunning)
    {
        std::cin >> command;
        
        switch(command)
        {
            case EXIT:
                programRunning = false;
                break;
            case ADD_BOOK:
                library->addBook();
                break;
            case DELETE_BOOK:
                library->deleteBook();
                break;
            case OUTPUT_BOOKS:
                library->outputLibraryList();
                break;
            case BORROW_BOOK:
                library->takeBook();
                break;
            case SEARCH_BOOK:
                searchBookHandler(library);
                break;
            case RETURN_BOOK:
                library->returnBook();
                break;
            default:
                std::cout << "Error | Unknown command!\n";
        }
    }
    
    delete library;

    return 0;
}