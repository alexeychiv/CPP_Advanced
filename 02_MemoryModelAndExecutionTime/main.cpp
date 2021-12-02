#include <stdio.h>
#include <iostream>
#include <clocale>
#include <vector>
#include <algorithm>
#include <unordered_set>
#include <string>
#include <fstream>

#include <locale>
#include <codecvt>

#include "intArrayUtils.h"
#include "Timer.h"

//=================================================================================================

//  TASK 1
template <typename T>
void swapPointers(T*& ptr1, T*&ptr2)
{
    T* tmp = ptr1;
    ptr1 = ptr2;
    ptr2 = tmp;
}

//=================================================================================================

//  TASK 2
template <typename T>
void sortPointerVector(std::vector<T*>& vecOfPtr)
{
    std::sort(vecOfPtr.begin(), vecOfPtr.end(),
        [](const T* first, const T* second) -> bool {
            return *first < *second;
        }
    );
}

//=================================================================================================

//  TASK 3
std::wstring textFileToWString(const std::string & textFile)
{
	std::ifstream ifs(textFile, std::ifstream::in);
    
	if(!ifs)
		throw std::runtime_error("Error reading text file!");
    
    std::string buf;
	std::wstring result;
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    
    while(!ifs.eof())
    {
        std::getline(ifs, buf);
        result.append(converter.from_bytes(buf));
        result += L' ';
    }
    
    return result;
}

size_t countChars_countIf_find(const std::wstring& wStr, const std::unordered_set<wchar_t>& charSet)
{
    Timer timer;
    
    return std::count_if(wStr.begin(), wStr.end(),
            [&charSet](const wchar_t& wch)->bool {
                return charSet.find(wch) != charSet.end();
            }
        );
}

size_t countChars_countIf_for(const std::wstring& wStr, const std::unordered_set<wchar_t>& charSet)
{
    Timer timer;
    
    return std::count_if(wStr.begin(), wStr.end(),
            [&charSet](const wchar_t& wch)->bool {
                for (const auto& it: charSet)
                    if (wch == it)
                        return true;
                
                return false; 
            }
        );
}

size_t countChars_for_find(const std::wstring& wStr, const std::unordered_set<wchar_t>& charSet)
{
    Timer timer;
    
    size_t counter = 0;
    
    for (const auto& it: wStr)
        if (charSet.find(it) != charSet.end())
            ++counter;
    
    return counter;
}

size_t countChars_for_for(const std::wstring& wStr, const std::unordered_set<wchar_t>& charSet)
{
    Timer timer;
    
    size_t counter = 0;
    
    for (const auto& it: wStr)
        for (const auto& ch: charSet)
            if (it == ch)
                ++counter;
    
    return counter;
}


//=================================================================================================

int main()
{
    //  1.  Реализуйте шаблонную функцию Swap, которая принимает два
    //      указателя и обменивает местами значения, на которые указывают
    //      эти указатели (нужно обменивать именно сами указатели,
    //      переменные должны оставаться в тех же адресах памяти).
    {
        printf("====================\nTASK 1:\n\n");
        
        int val1 = 10;
        int * ptr1 = &val1;
        int val2 = 20;
        int * ptr2 = &val2;
        
        printf("val1 = %d *ptr1 = %d\n", val1, *ptr1);
        printf("val2 = %d *ptr2 = %d\n", val2, *ptr2);
        
        printf(">>> SWAP <<<\n");
        swapPointers<int>(ptr1, ptr2);
        //swapPointers<int>(*ptr1, *ptr2); // CE
        //swapPointers<int>(val1, val2); // CE
        
        printf("val1 = %d *ptr1 = %d\n", val1, *ptr1);
        printf("val2 = %d *ptr2 = %d\n", val2, *ptr2);
        
        printf("\n");
    }
    
    //  2.  Реализуйте шаблонную функцию SortPointers, которая принимает
    //      вектор указателей и сортирует указатели по значениям,
    //      на которые они указывают.
    {
        printf("====================\nTASK 2:\n\n");
        
        int SIZE = 10;
        int arr[SIZE];
        
        intArrayUtils::fillAscending(arr, SIZE, 1);
        intArrayUtils::shuffle(arr, SIZE, 5);
        intArrayUtils::print(arr, SIZE);
        
        std::vector<int *> vecOfPtr;
        vecOfPtr.resize(SIZE);
        
        for (int i = 0; i < SIZE; ++i)
            vecOfPtr[i] = &arr[i];
        
        printf("VecOfPtr: ");
        for (const auto& it: vecOfPtr)
            printf("%d ", *it);
        printf("\n");
        
        printf(">>> SORT <<<\n");
        sortPointerVector<int>(vecOfPtr);
        
        intArrayUtils::print(arr, SIZE);
        printf("VecOfPtr: ");
        for (const auto& it: vecOfPtr)
            printf("%d ", *it);
        printf("\n");
        
        printf("\n");
    }
    
    //  3.  Подсчитайте количество гласных букв в книге “Война и мир”.
    //      Для подсчета используйте 4 способа:
    //          - count_if и find
    //          - count_if и цикл for
    //          - цикл for и find
    //          - 2 цикла for
    //      Замерьте время каждого способа подсчета и сделайте выводы.
    {
        printf("====================\nTASK 3:\n\n");
        
        const std::unordered_set<wchar_t> vowels = { L'а', L'е', L'ё', L'и', L'й', L'о', L'у', L'ы', L'э',
            L'ю', L'я', L'А', L'Е', L'Ё', L'И', L'Й', L'О', L'У', L'Ы', L'Э', L'Ю', L'Я' };
        
        const std::wstring text = textFileToWString("text.txt");
        
        wprintf(L"text size = %d\n", text.size());
        
        wprintf(L"count_if & find: %d", countChars_countIf_find(text, vowels));
        wprintf(L" (%.3fms)\n", Timer::getLastElapsedMs());
        
        wprintf(L"count_if & for:\t%d", countChars_countIf_for(text, vowels));
        wprintf(L" (%.3fms)\n", Timer::getLastElapsedMs());
        
        wprintf(L"for & find:\t%d", countChars_for_find(text, vowels));
        wprintf(L" (%.3fms)\n", Timer::getLastElapsedMs());
        
        wprintf(L"for & for:\t%d", countChars_for_for(text, vowels));
        wprintf(L" (%.3fms)\n", Timer::getLastElapsedMs());
    }
    
    return 0;
}



