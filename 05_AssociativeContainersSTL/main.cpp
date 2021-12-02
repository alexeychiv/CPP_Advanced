#include <stdio.h>
#include <iostream>

#include <unordered_set>
#include <string>
#include <vector>
#include <list>

#include <set>

#include "Timer.h"


//=================================================================================================

// TASK 1

template <typename Iterator>
void printUnique(const Iterator& begin, const Iterator& end)
{
    std::unordered_set<std::string> words;
    
    for (auto it = begin; it != end; ++it)
        words.emplace(*it);
    
    for (const auto& word: words)
        printf("'%s' ", word.c_str());
}

//=================================================================================================

// TASK 2

bool stringSizeComparator(const std::string& str1, const std::string& str2)
{
    return str1.size() <= str2.size();
}

//=================================================================================================

int main()
{
    //  1.  Создать шаблонную функцию, которая принимает итераторы на начало
    //      и конец последовательности слов, и выводящую в консоль список
    //      уникальных слов (если слово повторяется больше 1 раза, то вывести
    //      его надо один раз). Продемонстрировать работу функции, передав
    //      итераторы различных типов.
    

    {
        printf("====================\nTASK 1:\n\n");
        
        {
            std::vector<std::string> words {"blah", "bleh", "blah", "bluh", "bleh"};
            
            printf("Initial words in vector: ");
            for (const auto& word: words)
                printf("'%s' ", word.c_str());
            printf("\n");
            printf("Unique words in vector: ");
            printUnique(words.begin(), words.end());
            printf("\n");
        }
        printf("\n");
        {
            std::list<std::string> words {"blah", "bleh", "blah", "bluh", "bleh"};
            
            printf("Initial words in list: ");
            for (const auto& word: words)
                printf("'%s' ", word.c_str());
            printf("\n");
            printf("Unique words in list: ");
            printUnique(words.begin(), words.end());
            printf("\n");
        }
        
        
        printf("\n");
    }
    
    //  2.  Используя ассоциативный контейнер, напишите программу, которая
    //      будет считывать данные, введенные пользователем из стандартного
    //      потока ввода, и разбивать их на предложения. Далее программа должна
    //      вывести пользователю все предложения, отсортировав их по длине.
    
    {
        printf("====================\nTASK 2:\n\n");
        
        std::string text;
        
        printf("Enter text:\n");
        std::getline(std::cin, text);
        
        //auto stringSizeComparator = [](const std::string& str1, const std::string& str2)
        //{
        //    return str1.size() <= str2.size();
        //};
        //std::set<std::string, decltype(stringSizeComparator)> sentenses(stringSizeComparator);
        
        std::set<std::string, bool(*)(const std::string& str1, const std::string& str2)> sentenses(stringSizeComparator);
        
        size_t cursor = 0;
        std::string sentense;
        
        while (cursor < text.size())
        {
            sentense += text[cursor];
            
            if (text[cursor] == '.' || text[cursor] == '?' || text[cursor] == '!')
            {
                sentenses.emplace(sentense);
                sentense.clear();
            }
            
            ++cursor;
        }
        
        for (const auto& sentense: sentenses)
            printf("%s\n", sentense.c_str());
        
        printf("\n");
    }
    
    return 0;
}



