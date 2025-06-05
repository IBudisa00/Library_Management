# Set minimum required version
cmake_minimum_required(VERSION 3.10)

# Define project name
project(library)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)

# Define where to look for header files
include_directories(${PROJECT_SOURCE_DIR}/inc)

# Add source files
set(SOURCES
    src/main.cpp
    src/bookImpl.cpp
    src/libraryImpl.cpp
    src/helperFunctions.cpp
)

# Add executable
add_executable(libraryTask ${SOURCES})
