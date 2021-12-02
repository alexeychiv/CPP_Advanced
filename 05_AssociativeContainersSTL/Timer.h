#pragma once

#include <chrono>
#include <stdio.h>


class Timer
{
    private:
        std::chrono::steady_clock::time_point start; 
        static std::chrono::nanoseconds lastElapsed;

public:
    Timer()
    {
        start = std::chrono::steady_clock::now();
    }
    
    ~Timer()
    {
        lastElapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(
            std::chrono::steady_clock::now() - start
        );
    }
    
    static double getLastElapsedMs()
    {
        return (double)(lastElapsed.count() * 0.000001);
    }
};

std::chrono::nanoseconds Timer::lastElapsed = std::chrono::nanoseconds(0);
