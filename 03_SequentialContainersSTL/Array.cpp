#include "Array.h"


Array::Array(const int * data, const size_t SIZE)
    :
        SIZE(SIZE),
        data(nullptr)
{
    this->data = new int[SIZE];
    memcpy(this->data, data, SIZE * sizeof(int));
}

Array::~Array()
{
    delete[] data;
}
