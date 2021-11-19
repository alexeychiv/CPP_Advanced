#include "PhoneNumber.h"
#include <tuple>
#include <stdexcept>


PhoneNumber::PhoneNumber(
    const std::string & countryCode,
    const std::string & cityCode,
    const std::string & number,
    const std::string & additional
)
{
    if (isStringNotNumber(countryCode))
        throw std::runtime_error("ERROR: Bad country code! Should be a number!");
    
    this->countryCode = std::stoi(countryCode);
    
    if (isStringNotNumber(cityCode))
        throw std::runtime_error("ERROR: Bad city code! Should be a number!");
    
    this->cityCode = std::stoi(cityCode);
    
    if (isStringNotNumber(number))
        throw std::runtime_error("ERROR: Bad phone number! Should be a number!");
    
    this->number = number;
    
    if (additional.size())
    {
        if (isStringNotNumber(additional))
            throw std::runtime_error("ERROR: Bad additional number! Should be a number!");
        
        this->additional = std::stoi(additional);
    }
}

PhoneNumber::PhoneNumber(
    const int & countryCode,
    const int & cityCode,
    const std::string & number,
    const std::optional<int> & additional
)
    :
        countryCode(countryCode),
        cityCode(cityCode),
        additional(additional)
{
    if (countryCode < 0)
        throw std::runtime_error("ERROR: Bad country code! Cant be negative!");
    
    if (cityCode < 0)
        throw std::runtime_error("ERROR: Bad city code! Cant be negative!");
    
    if (isStringNotNumber(number))
        throw std::runtime_error("ERROR: Bad phone number! Should be a number!");
    
    this->number = number;
    
    if (*additional < 0)
        throw std::runtime_error("ERROR: Bad additional number code! Cant be negative!");
}

PhoneNumber::~PhoneNumber()
{
}

bool PhoneNumber::isStringNotNumber(const std::string & str)
{
    for (size_t i = 0; i < str.size(); ++i)
        if (str[i] < '0' || str[i] > '9')
            return true;
    return false;
}

bool PhoneNumber::operator<(const PhoneNumber & other) const
{
    return std::make_tuple(countryCode, cityCode, number, additional.value_or(0)) 
        < std::make_tuple(other.countryCode, other.cityCode, other.number, other.additional.value_or(0));
}

bool PhoneNumber::operator==(const PhoneNumber & other) const
{
    return std::make_tuple(countryCode, cityCode, number, additional.value_or(0)) 
        == std::make_tuple(other.countryCode, other.cityCode, other.number, other.additional.value_or(0));
}

std::string PhoneNumber::toString() const
{
    char stringBuffer[100];
    
    if (additional)
        sprintf(stringBuffer, "+%i(%i)%s %i",
            countryCode,
            cityCode,
            number.c_str(),
            *additional
        );
    else
        sprintf(stringBuffer, "+%i(%i)%s",
            countryCode,
            cityCode,
            number.c_str()
        );
    
    return stringBuffer;
}

std::ostream& operator<<(std::ostream & os, const PhoneNumber & phoneNumber)
{
    return os << phoneNumber.toString();
}




