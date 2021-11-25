#include "Matrix.h"

#include <cstring>
#include <vector>
#include <cmath>
#include <iomanip>
#include <algorithm>


Matrix::Matrix(const int* data, const size_t SIZE_X, const size_t SIZE_Y)
    :
        data(nullptr),
        SIZE_X(SIZE_X),
        SIZE_Y(SIZE_Y)
{
    this->data = new int[SIZE_X * SIZE_Y];
    memcpy(this->data, data, SIZE_X * SIZE_Y * sizeof(int));
}

Matrix::~Matrix()
{
    delete[] data;
}

int Matrix::countDeterminantLaplasRec(
    const std::set<size_t>& availableX,
    const size_t currentY
)
{
    if (availableX.size() == 1)
        return data[getIndex(*availableX.begin(), currentY)];
    
    int det = 0;
    bool isPlus = true;
    
    for (const auto& it : availableX)
    {
        int sign = isPlus ? 1 : -1;
        isPlus = !isPlus;
        std::set<size_t> newAvailableX = availableX;
        newAvailableX.erase(it);
        
        det += sign * data[getIndex(it, currentY)] * countDeterminantLaplasRec(newAvailableX, currentY + 1);
    }
    
    return det;
}

std::optional<int> Matrix::determinantLaplas()
{
    if (SIZE_X != SIZE_Y)
        return std::nullopt;
    
    std::set<size_t> availableX;
    
    for (size_t i = 0; i < SIZE_X; ++i)
        availableX.emplace(i);
    
    return countDeterminantLaplasRec(availableX, 0);
}

std::optional<int> Matrix::determinantGauss()
{
    if (SIZE_X != SIZE_Y)
        return std::nullopt;
    
    std::vector<double> matrix {data, data + SIZE_X * SIZE_Y};
    
    bool isPlus = true;
    
    for (size_t start = 0; start < SIZE_Y; ++start)
    {
        if (matrix[getIndex(start, start)] == 0)
        {
            for (size_t y = start + 1; y < SIZE_Y; ++y)
                if (matrix[getIndex(start, y)] !=0)
                {
                    isPlus = !isPlus;
                    for (size_t x = start; x < SIZE_X; ++x)
                        std::swap(matrix[getIndex(x, start)], matrix[getIndex(x, y)]);
                }
            
            if (matrix[getIndex(start, start)] == 0)
                return 0;
        }
        
        for (size_t y = start + 1; y < SIZE_Y; ++y)
        {
            double mult = matrix[getIndex(start, y)] / matrix[getIndex(start, start)];
            for (size_t x = start; x < SIZE_X; ++x)
                matrix[getIndex(x, y)] -= mult * matrix[getIndex(x, start)];
        }
    }
    
    if (matrix[getIndex(SIZE_X - 1, SIZE_Y - 1)] == 0)
        return 0;
    
    double det {isPlus ? 1 : -1};
    for (size_t diagonal = 0; diagonal < SIZE_X; ++diagonal)
        det *= matrix[getIndex(diagonal, diagonal)];
    
    return (int)std::lround(det);
}

std::ostream& operator<<(std::ostream& ostream, const Matrix& matrix)
{
    for (size_t y = 0; y < matrix.SIZE_Y; ++y)
    {
        for (size_t x = 0; x < matrix.SIZE_X; ++x)
            ostream << std::setw(3) << matrix.data[matrix.getIndex(x, y)] << " ";
        ostream << std::endl;
    }
    return ostream;
}

