#include <stdexcept>

#include "matrix_calc/vector/row.h"
#include "matrix_calc/vector/column.h"

namespace mtx{
    row::row(std::initializer_list<double> list)
    : IVector(list)
    {}

    row::row(std::size_t n, double value)
    : IVector(n, value)
    {}

    row::row(const row &other) = default;

    row::row(row &&other) noexcept
    : IVector(other)
    {}

    row row::reverse() {
        row out(size_);
        for(auto i = 0; i < size_; ++i){
            out[i] = buffer[size_-1-i];
        }
        return out;
    }

    column row::inverse() {
        column out(size_);
        for(auto i = 0; i < size_; ++i){
            out[i] = buffer[i];
        }
        return out;
    }

    row &row::operator+=(const row &rhs) {
        if(size_ != rhs.size_){
            throw std::logic_error("adding rows of different sizes.");
        }
        for(auto i =0; i < size_; ++i){
            buffer[i] += rhs[i];
        }
        return *this;
    }

    row operator+(const row& lhs, const row& rhs){
        if(lhs.size() != rhs.size()){
            throw std::logic_error("adding rows of different sizes.");
        }
        row out(lhs);
        out+=rhs;
        return out;
    }

    row operator*(const row& lhs, double rhs){
        row out(lhs);
        out*=rhs;
        return out;
    }

    row operator*(double lhs, const row& rhs){
        row out(rhs);
        out*=lhs;
        return out;
    }
}