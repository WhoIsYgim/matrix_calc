#include <stdexcept>

#include "matrix_calc/vector/row.h"
#include "matrix_calc/vector/column.h"

namespace mtx{

    column::column(std::initializer_list<double> list)
    : IVector(list)
    {}

    column::column(std::size_t n, double value)
    : IVector(n, value)
    {}

    column::column(const column &other) = default;

    column::column(column &&other) noexcept
    : IVector(other)
    {}

    column column::reverse() {
        column out(size_);
        for(auto i = 0; i < size_; ++i){
            out[i] = buffer[size_-1-i];
        }
        return out;
    }

    row column::inverse() {
        row out(size_);
        for(auto i = 0; i < size_; ++i){
            out[i] = buffer[i];
        }
        return out;
    }

    column &column::operator+=(const column &rhs) {
        if(size_ != rhs.size_){
            throw std::logic_error("adding columns of different sizes.");
        }
        for(auto i =0; i < size_; ++i){
            buffer[i] += rhs[i];
        }
        return *this;
    }

    column operator+(const column& lhs, const column& rhs){
        if(lhs.size()!= rhs.size()){
            throw std::logic_error("adding columns of different sizes.");
        }
        column out(lhs);
        out+=rhs;
        return out;
    }
    column operator*(const column& lhs, double rhs){
        column out(lhs);
        out*=rhs;
        return out;
    }
    column operator*(double lhs, const column& rhs){
        column out(rhs);
        out*=lhs;
        return out;
    }
}