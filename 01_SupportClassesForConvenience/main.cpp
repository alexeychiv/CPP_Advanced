#include <stdio.h>
#include <iostream>

#include <tuple>
#include "PhoneBook.h"


int main(int argc, char* argv[])
{
    PhoneBook book("PhoneBook.txt");
    std::cout << book;
    
    std::cout << "------SortByPhone-------" << std::endl;
    book.SortByPhone();
    std::cout << book;
    
    std::cout << "------SortByName--------" << std::endl;
    book.SortByName();
    std::cout << book;
    
    std::cout << "-----GetPhoneNumber-----" << std::endl;
    // лямбда функция, которая принимает фамилию и выводит номер телефона этого    	человека, либо строку с ошибкой
    auto print_phone_number = [&book](const std::string& surname) { 
        std::cout << surname << "\t"; 
        auto answer = book.GetPhoneNumber(surname);
        
        if (std::get<0>(answer).empty()) 
            std::cout << std::get<1>(answer); 
        else 
            std::cout << std::get<0>(answer);
        std::cout << std::endl; 
    };
    
    // вызовы лямбды
    print_phone_number("Ilin");
    print_phone_number("Ivanov");
    print_phone_number("Petrov");
    
    std::cout << "----ChangePhoneNumber----" << std::endl;
    book.ChangePhoneNumber(
        Person{ "Kotov", "Vasilii", "Eliseevich" },
        PhoneNumber{7, 123, "15344458"}
    );
    book.ChangePhoneNumber(
        Person{ "Mironova", "Margarita", "Vladimirovna" },
        PhoneNumber{ 16, 465, "9155448", 13 }
    );
    std::cout << book;
}



