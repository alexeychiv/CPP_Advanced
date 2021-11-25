#pragma once

#include <ostream>
#include <set>
#include <optional>


class Matrix
{
    private:
        int* data;
        
        const size_t SIZE_X;
        const size_t SIZE_Y;
        
        struct Pos
        {
            size_t x;
            size_t y;
            
            Pos(const size_t index, const size_t SIZE_X)
                :
                    x(index % SIZE_X),
                    y(index / SIZE_X)
            {}
        };
        
        size_t getIndex(size_t x, size_t y) const {return y * SIZE_X + x;}
        Pos getPos(size_t index) const {return Pos(index, SIZE_X);}
        
        int countDeterminantLaplasRec(
            const std::set<size_t>& availableX,
            const size_t currentY
        );
        
    public:
        Matrix(const int* data, const size_t SIZE_X, const size_t SIZE_Y);
        ~Matrix();
        
        std::optional<int> determinantLaplas();
        std::optional<int> determinantGauss();
        
        friend std::ostream& operator<<(std::ostream& ostream, const Matrix& matrix);
};
