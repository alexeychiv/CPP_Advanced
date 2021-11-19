#include "PhoneBook.h"
#include <fstream>
#include <stdexcept>
#include <algorithm>


PhoneBook::PhoneBook(const char * file)
{
    parseDataFromFile(file);
}

PhoneBook::~PhoneBook()
{
}

void PhoneBook::parseDataFromFile(const char * file)
{
    std::ifstream ifs(file);
    
    if (!ifs.is_open())
        throw std::runtime_error("ERROR: Unable to open data file!");
    
    std::string buf;
    
    while (!ifs.eof())
    {
        std::getline(ifs, buf);
        size_t cursor = 0;
        
        std::vector<std::string> bufParts;
        
        bufParts.emplace_back("");
        
        for (; cursor < buf.size(); ++cursor)
            if (buf[cursor] == ' ')
                bufParts.emplace_back("");
            else
                bufParts.back() += buf[cursor];
        
        if (bufParts.size() != 7)
            throw std::runtime_error("ERROR: Data file is corrupt!");
        
        phoneBookData.emplace_back(
            std::pair(
                Person(bufParts[0], bufParts[1], bufParts[2] == "-" ? "" : bufParts[2]),
                PhoneNumber(bufParts[3], bufParts[4], bufParts[5], bufParts[6] == "-" ? "" : bufParts[6])
            )
        );
    }
    
    ifs.close();
}

void PhoneBook::SortByPhone()
{
    std::sort(phoneBookData.begin(), phoneBookData.end(), 
        [](
            std::pair<Person, PhoneNumber> personLeft,
            std::pair<Person, PhoneNumber> personRight
        )
        {
            return personLeft.second < personRight.second;
        }
    );
}

void PhoneBook::SortByName()
{
    std::sort(phoneBookData.begin(), phoneBookData.end(), 
        [](
            std::pair<Person, PhoneNumber> personLeft,
            std::pair<Person, PhoneNumber> personRight
        )->bool
        {
            return personLeft.first < personRight.first;
        }
    );
}

std::tuple<std::string, std::string> PhoneBook::GetPhoneNumber(const std::string & surname)
{
    size_t foundCounter = 0;
    PhoneNumber * foundPhoneNumber = nullptr;
    
    for (auto & it : phoneBookData)
        if (it.first.surname == surname)
        {
            if (!foundCounter)
                foundPhoneNumber = &it.second;
            ++foundCounter;
        }
    
    switch (foundCounter)
    {
        case 0:
            return std::make_tuple("not found", "");
        case 1:
            return std::make_tuple("", foundPhoneNumber->toString());
        default:
            return std::make_tuple("found more than 1", "");
    }
}

void PhoneBook::ChangePhoneNumber(const Person & person, const PhoneNumber & phoneNumber)
{
    for (auto & it : phoneBookData)
        if (it.first == person)
        {
            it.second = phoneNumber;
            return;
        }
}

std::ostream& operator<<(std::ostream & os, const PhoneBook & phoneBook)
{
    for (const auto & it: phoneBook.phoneBookData)
        os << it.first << std::string(" ") << it.second << std::endl;
    
    return os;
}
