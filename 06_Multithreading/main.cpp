#include <stdio.h>
#include <iostream>

#include <thread>

#include <math.h>

#include <vector>
#include <atomic>

#include "Pcout.h"


//=================================================================================================

// TASK 1

void coutStreamer()
{
    for (int i = 0; i < 10; ++i)
        std::cout << "Thread #" << std::this_thread::get_id() << " ---> " << "BLAH" << std::endl;
}

Pcout pcout(std::cout);

void pcoutStreamer()
{
    for (int i = 0; i < 10; ++i)
        pcout.printLine("Thread #", std::this_thread::get_id(), " ---> ", "BLAH");
}

//=================================================================================================

// TASK 2

bool isNumberPrime(const int number)
{
	if (number < 2)
		return false;
	
	if (number < 4)
		return true;
	
    double dividerLimit = sqrt(number);
    
	for (int divider = 2; divider <= dividerLimit; ++divider)
		if (number % divider == 0)
			return false;
	
	return true;
}

//=================================================================================================




//=================================================================================================


int main()
{
    //  1.  Создайте потокобезопасную оболочку для объекта cout.
    //      Назовите ее pcout. Необходимо, чтобы несколько потоков
    //      могли обращаться к pcout и информация выводилась в консоль.
    //      Продемонстрируйте работу pcout.
    {
        printf("====================\nTASK 1:\n\n");
        
        {
            printf("Two threads use cout:\n");
            
            std::thread thread1(coutStreamer);
            std::thread thread2(coutStreamer);
            
            thread1.join();
            thread2.join();
        }
        
        printf("\n");
        
        {
            printf("Two threads use Pcout:\n");
            
            std::thread thread1(pcoutStreamer);
            std::thread thread2(pcoutStreamer);
            
            thread1.join();
            thread2.join();
        }
        
        printf("\n");
    }
    
    
    //  2.  Реализовать функцию, возвращающую i-ое простое число
    //      (например, миллионное простое число равно 15485863).
    //      Вычисления реализовать во вторичном потоке. В консоли
    //      отображать прогресс вычисления. 
    {
        printf("====================\nTASK 2:\n\n");
        
        unsigned int primeIndex = 10;
        //unsigned int primeIndex = 1'000'000;
        unsigned int currentIndex = 0;
        
        std::thread threadFindPrimeObserver(
            [&primeIndex, &currentIndex]()
            {
                while(true)
                {
                    std::this_thread::sleep_for(std::chrono::milliseconds(500));
                    if (currentIndex > primeIndex)
                        break;
                    printf("Progress: %.2f%\n", (double)currentIndex / primeIndex * 100);
                }
            }
        );
        
        std::thread threadFindPrime(
            [&primeIndex, &currentIndex]()
            {
                unsigned int number = 1;
                
                for (currentIndex = 1; currentIndex <= primeIndex; ++currentIndex)
                {
                    ++number;
                    while(!isNumberPrime(number))
                        ++number;
                }
                
                printf("prime number #%u = %u\n", primeIndex, number);
            }
        );
        
        threadFindPrime.join();
        threadFindPrimeObserver.join();
        
        printf("\n");
    }
    
    
    //  1.  Промоделировать следующую ситуацию.
    //      Есть два человека (2 потока): хозяин и вор.
    //      Хозяин приносит домой вещи (функция добавляющая случайное
    //      число в вектор с периодичностью 1 раз в секунду).
    //      При этом у каждой вещи есть своя ценность.
    //      Вор забирает вещи (функция, которая находит наибольшее число
    //      и удаляет из вектора с периодичностью 1 раз в 0.5 секунд),
    //      каждый раз забирает вещь с наибольшей ценностью.
    
    {
        printf("====================\nTASK 3:\n\n");
        
        srand(time(0));
        
        std::vector<int> storage;
        
        std::mutex storageMutex;
        
        std::thread master(
            [&storage, &storageMutex]()
            {
                for(int i = 0; i < 20; ++i)
                {
                    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                    printf("Master approaches the storage...\n");
                    int newItem = rand() % 100;
                    std::this_thread::sleep_for(std::chrono::milliseconds(500));
                    printf("Master puts %d in storage --> [ ", newItem);
                    storage.emplace_back(newItem);
                    for(const auto& it: storage)
                        printf("%d ", it);
                    printf("]\n");
                    printf("Master leaves the storage...\n");
                }
            }
        );
        
        std::thread thief(
            [&storage, &storageMutex]()
            {
                for(int i = 0; i < 20; ++i)
                {
                    std::this_thread::sleep_for(std::chrono::milliseconds(500));
                    printf("Thief approaches the storage...\n");
                    std::lock_guard<std::mutex> lock(storageMutex);
                    if (!storage.size())
                    {
                        printf("Thief leaves cause the storage is empty...\n");
                        continue;
                    }
                    auto mostValuableItemIterator = storage.begin();
                    for(auto it = storage.begin() + 1; it != storage.end(); ++it)
                        if (*mostValuableItemIterator < *it)
                            mostValuableItemIterator = it;
                    std::this_thread::sleep_for(std::chrono::milliseconds(500));
                    printf("Thief steals %d from storage --> [ ", *mostValuableItemIterator);
                    storage.erase(mostValuableItemIterator);
                    for(const auto& it: storage)
                        printf("%d ", it);
                    printf("]\n");
                    printf("Thief leaves the storage...\n");
                }
            }
        );
        
        master.join();
        thief.join();
        
        printf("\n");
    }
    
    
    return 0;
}



