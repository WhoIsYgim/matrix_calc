#include <stdexcept>

#include "matrix_calc/vector.h"

namespace mtx{
    vector::vector(std::initializer_list<double> list)
    : IVector(list)
    {}

    vector::vector(std::size_t n, double value)
    : IVector(n, value)
    {}

    vector::vector(const vector &other) = default;

    vector::vector(vector &&other) noexcept
    : IVector(other)
    {}

    vector vector::reverse() {
        vector out(size_);
        for(auto i = 0; i < size_; ++i){
            out[i] = buffer[size_-1-i];
        }
        return out;
    }

    vector &vector::operator+=(const vector &rhs) {
        if(size_ != rhs.size_){
            throw std::logic_error("adding vectors of different sizes.");
        }
        for(auto i =0; i < size_; ++i){
            buffer[i] += rhs[i];
        }
        return *this;
    }


    vector operator+(const vector& lhs, const vector& rhs){
        if(lhs.size() != rhs.size()){
            throw std::logic_error("adding vectors of different sizes.");
        }
        vector out(lhs);
        out+=rhs;
        return out;
    }

    vector operator*(const vector& lhs, double rhs){
        vector out(lhs);
        out*=rhs;
        return out;
    }

    vector operator*(double lhs, const vector& rhs){
        vector out(rhs);
        out*=lhs;
        return out;
    }

    /*
             IVector impl
     */

    IVector::IVector(std::initializer_list<double> list)
    : size_(list.size())
    {
        buffer = new double[size_];
        std::size_t i = 0;
        for(auto item: list){
            buffer[i] = item;
            ++i;
        }
    }

    IVector::IVector(std::size_t n, double value)
    :  size_(n)
    {
        buffer = new double[size_];
        for(auto i = 0; i < size_; ++i){
            buffer[i] = value;
        }
    }

    IVector::IVector(const IVector &other)
    : size_(other.size_)
    {
        buffer = new double[size_];
        for (auto i = 0; i < size_; ++i){
            buffer[i] = other.buffer[i];
        }
    }

    IVector::IVector(IVector &&other) noexcept
    : size_(other.size_), buffer(other.buffer)
    {
        other.size_ = 0;
        other.buffer = nullptr;
    }

    IVector::~IVector() {
        delete[] buffer;
    }

    double &IVector::at(std::size_t n) {
        if(n >= size_){
            throw std::out_of_range("range_check: n >= this->size()");
        }
        return buffer[n];
    }

    double &IVector::operator[](size_t n) const{
        return buffer[n];
    }

    std::size_t IVector::size() const {
        return size_;
    }


    IVector &IVector::operator*=(double rhs) {
        for(auto i = 0; i < size_; ++i){
            buffer[i] *=rhs;
        }
        return *this;
    }
}

