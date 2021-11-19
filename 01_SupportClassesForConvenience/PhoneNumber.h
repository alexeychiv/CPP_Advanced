#pragma once

#include <ostream>
#include <string>
#include <optional>


class PhoneNumber
{
private:
    int countryCode;
    int cityCode;
    std::string number;
    std::optional<int> additional;
    
    bool isStringNotNumber(const std::string & str);
    
public:
    PhoneNumber(
        const std::string & countryCode,
        const std::string & cityCode,
        const std::string & number,
        const std::string & additional = ""
    );
    
    PhoneNumber(
        const int & countryCode,
        const int & cityCode,
        const std::string & number,
        const std::optional<int> & additional = std::nullopt
    );
    
    ~PhoneNumber();
    
    bool operator<(const PhoneNumber & other) const;
    bool operator==(const PhoneNumber & other) const;
    
    std::string toString() const;
    
    friend std::ostream& operator<<(std::ostream & os, const PhoneNumber & phoneNumber);
};
