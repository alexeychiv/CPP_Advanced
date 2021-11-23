#include <iostream>
#include <random>
#include <time.h>

#include "intArrayUtils.h"


namespace intArrayUtils
{
    void print(const int * arr, const int SIZE)
    {
        std::cout << "IntArray[" << SIZE << "]: { ";
        if (SIZE > 0)
        {
            std::cout << arr[0];
            for (int i = 1; i < SIZE; ++i)
                std::cout << ", " << arr[i];
        }
        std::cout << " }"<< std::endl;
    }
    
    void fillAscending(int * arr, const int SIZE, const int start)
    {
        for (int i = 0; i < SIZE; ++i)
            arr[i] = start + i;
    }
    
    void fillDescending(int * arr, const int SIZE, const int start)
    {
        for (int i = 0; i < SIZE; ++i)
            arr[i] = start - i;
    }
    
    void fillRandom(int * arr, const int SIZE, const int MIN, const int MAX)
    {
        std::default_random_engine randomGenerator(time(0));
        std::uniform_int_distribution<int> distribution(MIN, MAX);
        
        for (int i = 0; i < SIZE; ++i)
            arr[i] = distribution(randomGenerator);
    }
    
    void shuffle(int * arr, const int SIZE, const int randomness)
    {
        std::default_random_engine randomGenerator(time(0));
        std::uniform_int_distribution<int> distribution(0, SIZE - 1);
        
        int first;
        int second;
        int buf;
        
        for (int i = 0; i < randomness; ++i)
        {
            first = distribution(randomGenerator);
            second = distribution(randomGenerator);
            
            buf = arr[first];
            arr[first] = arr[second];
            arr[second] = buf;
        }
    }
    
    bool isSortedAscending(const int * arr, const int SIZE)
    {
        for (int i = 1; i < SIZE; ++i)
            if (arr[i] < arr[i - 1])
                return false;
        return true;
    }
    
    bool isAscendingSequence(const int * arr, const int SIZE)
    {
        for (int i = 1; i < SIZE; ++i)
            if (arr[i] - arr[i - 1] != 1)
                return false;
        return true;
    }
    
    bool isSortedDescending(const int * arr, const int SIZE)
    {
        for (int i = 1; i < SIZE; ++i)
            if (arr[i] > arr[i - 1])
                return false;
        return true;
    }
    
    bool isDescendingSequence(const int * arr, const int SIZE)
    {
        for (int i = 1; i < SIZE; ++i)
            if (arr[i - 1] - arr[i] != 1)
                return false;
        return true;
    }
    
    void copy(int * arrSource, int * arrDest, const int SIZE)
    {
        memcpy(arrDest, arrSource, SIZE * sizeof(int));
    }
};
