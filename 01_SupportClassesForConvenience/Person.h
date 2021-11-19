#pragma once

#include <string>
#include <optional>
#include <ostream>


class Person
{
    public:
        static size_t surnameSizeMax;
        static size_t nameSizeMax;
        static size_t middleNameSizeMax;
        
        std::string surname;
        std::string name;
        std::optional<std::string> middleName;
        
        Person(
            const std::string & surname,
            const std::string & name,
            const std::string & middleName = ""
        );
        
        ~Person();
        
        bool operator<(const Person & other) const;
        bool operator==(const Person & other) const;
        
        std::string toString() const;
        
        friend std::ostream& operator<<(std::ostream & os, const Person & person);
};


