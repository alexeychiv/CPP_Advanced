#include <stdio.h>
#include <iostream>

#include <list>

#include "Matrix.h"
#include "Array.h"


//=================================================================================================

// TASK 1
void printListOfDoubles(const std::list<double>& listOfDoubles)
{
    printf("List of doubles");
    
    if (listOfDoubles.empty())
    {
        printf(" is empty...\n");
        return;
    }
    
    bool isFirst = true;
    for (const auto& it: listOfDoubles)
        if (isFirst)
        {
            printf(": <%f>", *listOfDoubles.begin());
            isFirst = false;
        }
        else
            printf("-<%f>", it);
    
    printf("\n");
}

void addArythmeticMeanToList(std::list<double>& listOfDoubles)
{
    if (listOfDoubles.empty())
        return;
    
    double sum {0};
    for (const auto& it: listOfDoubles)
        sum += it;
    listOfDoubles.emplace_back(sum / listOfDoubles.size());
}

//=================================================================================================

int main()
{
    //  1.  Написать функцию, добавляющую в конец списка вещественных
    //      чисел элемент, значение которого равно среднему арифметическому
    //      всех его элементов.
    {
        printf("====================\nTASK 1:\n\n");
        
        std::list<double> listOfDoubles {1.1, 2.2, 3.3, 4.4};
        printListOfDoubles(listOfDoubles);
        
        printf(">>> ADD ARYTHMETIC MEAN TO LIST <<<\n");
        addArythmeticMeanToList(listOfDoubles);
        printListOfDoubles(listOfDoubles);
        
        printf("\n");
    }
    
    //  2.  Создать класс, представляющий матрицу. Реализовать в нем метод,
    //      вычисляющий определитель матрицы.
    {
        printf("====================\nTASK 2:\n\n");
        
        // size_t SIZE_X = 2;
        // size_t SIZE_Y = 2;
        // const int data[SIZE_X * SIZE_Y] {
        //     1, 2,
        //     3, 4
        // };
        
        // size_t SIZE_X = 3;
        // size_t SIZE_Y = 3;
        // const int data[SIZE_X * SIZE_Y] {
        //     1, 2, 3,
        //     4, 5, 6,
        //     7, 8, 10,
        // };
        
        size_t SIZE_X = 4;
        size_t SIZE_Y = 4;
        const int data[SIZE_X * SIZE_Y] {
            1, 2, 3, 4,
            5, 6, 7, 8,
            9, 10, 10, 12,
            13, 14, 15, 20
        };
        
        Matrix matrix(data, SIZE_X, SIZE_Y);
        
        std::cout << "Matrix:" << std::endl << matrix;
        printf("det (Laplas method) = %d\n", matrix.determinantLaplas().value());
        printf("det (Gauss method) = %d\n", matrix.determinantGauss().value());
        
        printf("\n");
    }
    
    //  3.  Реализовать собственный класс итератора, с помощью которого
    //      можно будет проитерироваться по диапазону целых чисел в
    //      цикле for-range-based.
    {
        printf("====================\nTASK 3:\n\n");
        
        int data[5] = {0, 1, 2, 3, 4};
        
        Array arr(data, 5);
        
        printf("Array: ");
        for (const auto& it : arr)
            printf("%d ", it);
        printf("\n");
    }
    
    return 0;
}



