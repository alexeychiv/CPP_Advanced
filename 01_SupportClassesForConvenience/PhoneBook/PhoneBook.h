#pragma once

#include <vector>
#include <string>
#include <tuple>

#include "Person.h"
#include "PhoneNumber.h"


class PhoneBook
{
    private:
        std::vector<std::pair<Person, PhoneNumber>> phoneBookData;
        
        void parseDataFromFile(const char * file);
        
    public:
        PhoneBook(const char * file);
        ~PhoneBook();
        
        void SortByPhone();
        void SortByName();
        std::tuple<std::string, std::string> GetPhoneNumber(const std::string & surname);
        void ChangePhoneNumber(const Person & person, const PhoneNumber & phoneNumber);
        
        friend std::ostream& operator<<(std::ostream & os, const PhoneBook & phoneBook);
};
