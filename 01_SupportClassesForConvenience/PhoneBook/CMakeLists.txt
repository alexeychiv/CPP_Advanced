
project(PhoneBook)

add_library(${PROJECT_NAME} STATIC
    Person.h
    Person.cpp
    
    PhoneNumber.h
    PhoneNumber.cpp
    
    PhoneBook.h
    PhoneBook.cpp
)

target_include_directories(${PROJECT_NAME} PUBLIC .)