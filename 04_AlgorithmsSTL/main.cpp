#include <stdio.h>
#include <iostream>

#include <vector>
#include <list>
#include <algorithm>
#include <numeric>
#include <iterator>

#include <random>

#include <boost/foreach.hpp>
#include <boost/range/combine.hpp>

#include "Timer.h"


//=================================================================================================

//  TASK 1
template <typename Container, typename T>
void insert_sorted(Container& container, const T value)
{
    container.insert(
        std::find_if(container.begin(), container.end(), [&value](const T& it){
            return it > value;
        }),
        value
    );
}

//=================================================================================================

//  TASK 2

double countError_for(const std::vector<double>& analog, const std::vector<long>& digital)
{
    if (analog.size() != digital.size())
        return 0;
    
    Timer timer;
    
    double error = 0;
    
    for (size_t i = 0; i < analog.size(); ++i)
        error += (analog[i] - digital[i]) * (analog[i] - digital[i]);
    
    return error;
}

double countError_boostForEach(const std::vector<double>& analog, const std::vector<long>& digital)
{
    if (analog.size() != digital.size())
        return 0;
    
    Timer timer;
    
    double d;
    long l;
    
    double error = 0;
    
    BOOST_FOREACH(boost::tie(d, l), boost::combine(analog, digital))
    {
        error += (d - l) * (d - l);
    }
    
    return error;
}

//=================================================================================================

int main()
{
    //  1.  Имеется отсортированный массив целых чисел.
    //      Необходимо разработать функцию insert_sorted,
    //      которая принимает вектор и новое число и вставляет
    //      новое число в определенную позицию в векторе,
    //      чтобы упорядоченность контейнера сохранялась.
    //      Реализуйте шаблонную функцию insert_sorted,
    //      которая сможет аналогично работать с любым контейнером,
    //      содержащим любой тип значения. 
    
    {
        printf("====================\nTASK 1:\n\n");
        
        const size_t SIZE = 10;
        
        std::vector<int> vec(SIZE);
        std::iota(vec.begin(), vec.end(), 0);
        
        printf("Vector: ");
        std::copy(vec.begin(), vec.end(), std::ostream_iterator<int>{std::cout, " "});
        printf("\n");
        
        printf(">>> instert sorted <<<\n");
        insert_sorted(vec, 5);
        
        printf("Vector: ");
        std::copy(vec.begin(), vec.end(), std::ostream_iterator<int>{std::cout, " "});
        printf("\n");
        
        printf("\n");
        
        
        std::list<long> list(SIZE);
        std::iota(list.begin(), list.end(), 0);
        
        printf("List: ");
        std::copy(list.begin(), list.end(), std::ostream_iterator<long>{std::cout, " "});
        printf("\n");
        
        printf(">>> instert sorted <<<\n");
        insert_sorted(list, 5);
        
        printf("List: ");
        std::copy(list.begin(), list.end(), std::ostream_iterator<long>{std::cout, " "});
        printf("\n");
        
        printf("\n");
    }
    
    
    //  2.  Сгенерируйте вектор a, состоящий из 100 вещественный чисел,
    //      представляющий собой значения аналогового сигнала.
    //      На основе этого массива чисел создайте другой вектор целых чисел b,
    //      представляющий цифровой сигнал, в котором будут откинуты дробные
    //      части чисел. Выведите получившиеся массивы чисел.
    //      Посчитайте ошибку, которой обладает цифровой сигнал по сравнению
    //      с аналоговым по формуле:
    //      sum[0..n-1] (ai - bi) ^ 2,
    //      где:
    //          n - количество элементов в векторе,
    //          a - элемент вектора с дробными числами,
    //          b - элемент вектора с целыми числами
    
    {
        printf("====================\nTASK 2:\n\n");
        
        const size_t SIZE {100};
        
        std::vector<double> a(SIZE);
        
        std::random_device dev;
        std::mt19937 rng(dev());
        std::uniform_int_distribution<std::mt19937::result_type> distribution(1000,9999);
        
        
        std::generate(a.begin(), a.end(), [&rng, &distribution](){return (double)distribution(rng) / 100;});
        
        printf("Analog: ");
        std::copy(a.begin(), a.end(), std::ostream_iterator<double>{std::cout, " "});
        printf("\n");
        
        std::vector<long> digital(SIZE);
        std::copy(a.begin(), a.end(), digital.begin());
        
        printf("Digital: ");
        std::copy(digital.begin(), digital.end(), std::ostream_iterator<long>{std::cout, " "});
        printf("\n");
        
        printf("countError_for = %f", countError_for(a, digital));
        printf(" (%fms)\n", Timer::getLastElapsedMs());
        
        printf("countError_boostForEach = %f", countError_for(a, digital));
        printf(" (%fms)\n", Timer::getLastElapsedMs());
        
        printf("\n");
    }
    
    return 0;
}



