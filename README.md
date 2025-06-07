**How to build and run**

*Linux*
cd build
cmake ..
make
./libraryTask


*Windows (MinGW)*
cd build
cmake .. -G "MinGW Makefiles"
mingw32-make
./libraryTask.exe

*Optional*
To build library with own .txt file instead of last command use:

./libraryTask.exe myOwnFileName.txt

**Code Architecture**

Factory design was used to make code as modular as possible by leaving user choice to make his own book subclass. That way he can implement anything he wishes but he will HAVE TO have few specified functions/methods that are mandatory. Anything extra is up to user. 

Also same factory design was implemented for Library class where user will need to have prerequested methods like adding books, deleting, taking, returning... Anything additional is easy to implement and modular by using dynamic_cast in main control system. That way even if there are new options based on type of library they will be able to do it or will just notify user about boundaries.

Regarding Time Complexity due to having multiple ways of searching/checking for certain book there was no point in sorting in any way so its left to be as O(n) in case of searching and deleting, but for adding O(1) makes it really easy and fast. Due to having to stick with O(n) for most of time there was no use of making linked list as type of architecture for books organization. That is why vector was used, there is no big overhead which implies that less memory will be used.

**Output/input file format**
Files have to be .txt and their tekst is in next form:
UniqueID[unsigned_int] | BookTitle[string] | AuthorName[string] | Genres[string] | Availability[int] | Year[int]

Example:

1 | ClownFest | Author1 | crime | 1 | 1966
2 | Book2 | Author2 | crime, triller | 1 | 2001

Availability has to be *0* or *1*. Genres if there are more than on have to be divided by comma as shown.
