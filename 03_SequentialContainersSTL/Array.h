#pragma once

#include <cstring>


class Array
{
    private:
        const size_t SIZE;
        int * data;
        
    public:
        Array(const int * data, const size_t SIZE);
        ~Array();
        
        class Iterator
        {
            private:
                int * ptr;
            
            public:
                Iterator(int * ptr) : ptr(ptr) {}
                
                Iterator& operator++ ()
                {
                    ++ptr;
                    return *this;
                }
                
                Iterator operator++ (int)
                {
                    Iterator it = *this;
                    ++ptr;
                    return it;
                }
                
                Iterator& operator-- ()
                {
                    --ptr;
                    return *this;
                }
                
                Iterator operator-- (int)
                {
                    Iterator it = *this;
                    --ptr;
                    return it;
                }
                
                int& operator[] (const int index)
                {
                    return *(ptr + index);
                }
                
                int& operator* ()
                {
                    return *ptr;
                }
                
                int* operator-> ()
                {
                    return ptr;
                }
                
                bool operator== (const Iterator& other) const
                {
                    return ptr == other.ptr;
                }
                
                bool operator!= (const Iterator& other) const
                {
                    return !(*this == other);
                }
        };
        
        Iterator begin() {return Iterator(data);}
        Iterator end() {return Iterator(data + SIZE);}
};
