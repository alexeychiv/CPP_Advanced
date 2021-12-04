#pragma once

#include <ostream>
#include <mutex>
#include <stdarg.h>

#include <atomic>


class Pcout
{
    private:
        std::ostream& ostream;
        std::mutex mutex;
        
        template <typename Streamable>
        void print(Streamable t) 
        {
            ostream << t;
        }
        
        template<typename Streamable, typename... Args>
        void print(Streamable t, Args... args)
        {
            ostream << t;
            print(args...);
        }
        
    public:
        Pcout(std::ostream& ostream) : ostream(ostream) {}
        
        template<typename Streamable, typename... Args>
        void printLine(Streamable t, Args... args)
        {
            std::lock_guard<std::mutex> lock(mutex);
            print(t, args...);
            ostream << std::endl;
        }
};