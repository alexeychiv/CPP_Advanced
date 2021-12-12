#include "Person.h"
#include <tuple>


size_t Person::surnameSizeMax = 0;
size_t Person::nameSizeMax = 0;
size_t Person::middleNameSizeMax = 0;


Person::Person(
    const std::string & surname,
    const std::string & name,
    const std::string & middleName
)
    :
        surname(surname),
        name(name)
{
    if (middleName.size())
        this->middleName = middleName;
    else
        this->middleName = std::nullopt;
    
    if (surnameSizeMax < surname.size())
        surnameSizeMax = surname.size();
    if (nameSizeMax < name.size())
        nameSizeMax = name.size();
    if (middleNameSizeMax < middleName.size())
        middleNameSizeMax = middleName.size();
    
}

Person::~Person()
{
}

bool Person::operator<(const Person & other) const
{
    return std::make_tuple(surname, name, middleName.value_or("")) 
        < std::make_tuple(other.surname, other.name, other.middleName.value_or(""));
}

bool Person::operator==(const Person & other) const
{
    return std::make_tuple(surname, name, middleName.value_or("")) 
        == std::make_tuple(other.surname, other.name, other.middleName.value_or(""));
}

std::string Person::toString() const
{
    char fmt[15];
    
    char stringBuffer[300];
    
    sprintf(fmt, "%%%ds%%%ds%%%ds",
        surnameSizeMax + 1,
        nameSizeMax + 1,
        middleNameSizeMax ? Person::middleNameSizeMax + 1 : 0
    );
    
    sprintf(stringBuffer, fmt,
        surname.c_str(),
        name.c_str(),
        middleName.value_or("").c_str()
    );
    
    return stringBuffer;
}

std::ostream& operator<<(std::ostream & os, const Person & person)
{
    return os << person.toString();
}
