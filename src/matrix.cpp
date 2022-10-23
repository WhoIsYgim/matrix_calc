#include <stdexcept>
#include <cmath>

#include "matrix_calc/matrix.h"
#include "matrix_calc/vector.h"
#include "matrix_calc/vector/row.h"
#include "matrix_calc/vector/column.h"

namespace mtx{

    matrix::matrix(std::initializer_list<vector> list)
    :cols_(list.begin()->size()), rows_(list.size())
    {

        buffer = new double* [rows_];
        for(size_t  i = 0; i < rows_; ++i) {
            buffer[i] = new double[cols_];
        }

        std::size_t rw = 0;
        for(const auto& it: list){
            if(it.size() != list.begin()->size()){
                throw std::logic_error("constructing matrix form vectors of different sizes.");
            }
            for(size_t  i = 0; i < cols_; ++i){
                buffer[rw][i] = it[i];
            }
            ++rw;
        }
    }

    matrix::matrix(std::initializer_list<column> list)
    : cols_(list.size()), rows_(list.begin()->size())
    {
        buffer = new double* [rows_];
        for(size_t  i = 0; i < rows_; ++i) {
            buffer[i] = new double[cols_];
        }
        std::size_t cl = 0;
        for(const auto& it: list){
            if(it.size() != list.begin()->size()){
                throw std::logic_error("constructing matrix form columns of different sizes.");
            }
            for(size_t  i = 0; i < rows_; ++i){
                buffer[i][cl] = it[i];
            }
            ++cl;
        }
    }

    matrix::matrix(std::initializer_list<row> list)
    : cols_(list.begin()->size()), rows_(list.size())
    {
        buffer = new double* [rows_];
        for(size_t  i = 0; i < rows_; ++i) {
            buffer[i] = new double[cols_];
        }

        std::size_t rw = 0;
        for(const auto& it: list){
            if(it.size() != list.begin()->size()){
                throw std::logic_error("constructing matrix form rows of different sizes.");
            }
            for(size_t  i = 0; i < cols_; ++i){
                buffer[rw][i] = it[i];
            }
            ++rw;
        }
    }

    matrix::matrix(std::size_t m, std::size_t n, double value)
    : cols_(n), rows_(m)
    {
        buffer = new double* [rows_];
        for(size_t  i = 0; i < rows_; ++i){
            buffer[i] = new double[cols_];
            for(size_t  j = 0; j < cols_; ++j){
                buffer[i][j] = value;
            }
        }
    }

    matrix::matrix(const matrix &other)
    : cols_(other.cols_), rows_(other.rows_)
    {
        buffer = new double*[rows_];
        for(size_t i = 0; i < rows_; ++i){
            buffer[i] = new double[cols_];
            for(size_t  j = 0; j < cols_; ++j){
                buffer[i][j] = other.buffer[i][j];
            }
        }
    }

    matrix::matrix(matrix &&other) noexcept
    : cols_(other.cols_), rows_(other.rows_), buffer(other.buffer)
    {
        other.buffer = nullptr;
        other.rows_ = 0;
        other.cols_ = 0;
    }

    matrix::~matrix(){
        for(size_t  i = 0; i < rows_; ++i) {
            delete[] buffer[i];
        }
        delete[] buffer;
    }

    row matrix::get_row(std::size_t m) {
        if(m >= rows_){
            throw std::out_of_range("range_check: m >= this->rows()");
        }
        row out(cols_);
        for(size_t  i = 0; i < cols_; ++i){
            out[i] = buffer[m][i];
        }
        return out;
    }

    column matrix::get_col(std::size_t n) {
        if(n >= cols_){
            throw std::out_of_range("range_check: n >= this->cols()");
        }
        column out(rows_);
        for (size_t  i = 0; i < rows_; ++i){
            out[i] = buffer[i][n];
        }
        return out;
    }

    vector matrix::main_diagonal() {
        if(rows_ != cols_){
            throw std::logic_error("extracting a diagonal from a non-square matrix");
        }
        vector out(rows_);
        for(size_t  i = 0; i < rows_; ++i){
            out[i] = buffer[i][i];
        }
        return out;
    }

    vector matrix::secondary_diagonal() {
        if(rows_ != cols_){
            throw std::logic_error("extracting a diagonal from a non-square matrix");
        }
        vector out(rows_);
        for(size_t  i = 0; i < rows_; ++i){
            out[i] = buffer[rows_ - i][i];
        }
        return out;
    }

    matrix matrix::inverse() {
        if(rows_ != cols_){
            throw std::logic_error("transposing a non-square matrix");
        }
        if(determinant() == 0){
            throw std::runtime_error("determinant is 0.");
        }

        matrix temp(*this);
        double norm_cols = 0;
        double norm_rows = 0;
        for(size_t  i = 0; i < rows_; ++i){
            double row = 0;
            double col = 0;
            for(size_t  j = 0; j < rows_; ++j){
                row += std::abs(temp[i][j]);
                col += std::abs(temp[j][i]);
            }
            norm_cols = std::max(col, norm_cols);
            norm_rows = std::max(row, norm_rows);
        }
        temp = temp.transposed();
        temp *= (1/(norm_rows*norm_cols));

        matrix E(rows_,rows_);
        for(size_t  i = 0; i < rows_; ++i){
            E[i][i] = 2;
        }

        matrix out(temp);
        double eps = 1.0e-15;
        while (std::abs(
                (*this*out).determinant() -1 ) >= eps){
            matrix prev (out);
            out = *this*prev;
            out *= -1;
            out += E;
            out = prev*out;
        }
        return out;
    }

    matrix matrix::transposed() {
        matrix out(cols_, rows_);
        for(size_t  i = 0; i < rows_; ++i){
            for(size_t  j = 0; j < cols_; ++j){
                out[j][i] = buffer[i][j];
            }
        }
        return out;
    }

    double matrix::determinant() {
        if(rows_ != cols_){
            throw std::logic_error("calculating the discriminant of a non-square matrix");
        }
        matrix temp(*this);

        double det = 1;
        for(size_t  i = 0; i < rows_; ++i){
            std::size_t pivot_idx = i;
            double pivot = buffer[i][i];
            for(size_t  j = i+1; j < rows_; ++j){
                if(std::abs(temp[j][i]) > pivot){
                    pivot = std::abs(temp[j][i]);
                    pivot_idx = j;
                }
            }
            if(pivot == 0){
                return 0;
            }
            if(pivot_idx != i){
                std::swap(temp.buffer[pivot_idx], temp.buffer[i]);
                det *= -1;
            }
            for(size_t  j = i+1; j < rows_; ++j){
                if(temp[j][i] != 0){
                    double factor = temp[j][i]/ temp[i][i] ;
                    for(size_t  k = i; k < rows_; ++k){
                        temp[j][k] -= temp[i][k] * factor;
                    }
                }
            }
        }
        for(size_t  i = 0; i < rows_; ++i) {
            det *= temp[i][i];
        }
        return det;
    }

    double* matrix::operator[](std::size_t m) const{
        if(m >= rows_){
            throw std::out_of_range("range_check: m >= this->rows()");
        }
        return buffer[m];
    }

    matrix &matrix::operator=(const matrix &other) {
        if(&other == this){
            return *this;
        }
        realloc(other.rows_, other.cols_);
        for(size_t  i = 0; i < rows_; ++i){
            for(size_t  j = 0; j < cols_; ++j){
                buffer[i][j] = other[i][j];
            }
        }
        return *this;
    }
    matrix &matrix::operator=(matrix &&other) noexcept {
        if(&other == this){
            return *this;
        }
        for(size_t  i = 0; i < rows_; ++i){
            delete[] buffer[i];
        }
        delete[] buffer;

        buffer = other.buffer;
        rows_ = other.rows_;
        cols_ = other.cols_;

        other.buffer = nullptr;
        other.rows_ = 0;
        other.cols_ = 0;

        return *this;
    }

    matrix &matrix::operator+=(const matrix &rhs) {
        if((rows_ != rhs.rows_) || (cols_ != rhs.cols_)){
            throw std::logic_error("addition of matrices of different sizes.");
        }
        for(size_t  i = 0; i < rows_; ++i){
            for(size_t  j = 0; j < cols_; ++j){
                buffer[i][j] += rhs.buffer[i][j];
            }
        }
        return *this;
    }

    matrix &matrix::operator*=(const matrix &rhs) {
        if(cols_ != rhs.rows_){
            throw std::logic_error("multiplication of incompatible matrices");
        }
        matrix temp(*this);
        realloc(rows_, rhs.cols_);
        for(size_t i = 0; i < rows_; ++i) {
            for (size_t  j = 0; j < cols_; ++j) {
                double cell = 0.0;
                for (size_t  k = 0; k < rhs.rows_; ++k) {
                    cell += temp[i][k] * rhs[k][j];
                }
                buffer[i][j] = cell;
            }
        }
        return *this;
    }

    matrix &matrix::operator*=(double rhs) {
        for(size_t  i = 0; i < rows_; ++i){
            for(size_t  j = 0; j < cols_; ++j){
                buffer[i][j]*=rhs;
            }
        }
        return *this;
    }

    std::size_t matrix::cols() const {
        return cols_;
    }

    std::size_t matrix::rows() const {
        return rows_;
    }

    void matrix::realloc(std::size_t _rows, std::size_t _cols) {
        if(rows_ == _rows && cols_ == _cols){
            return;
        }
        for(size_t  i = 0; i < rows_; ++i) {
            delete[] buffer[i];
        }
        delete[] buffer;

        rows_ = _rows;
        buffer = new double*[rows_];
        cols_ = _cols;
        for(size_t  i = 0; i < rows_; ++i){
            buffer[i] = new double [cols_];
        }
    }


    matrix operator+(const matrix& lhs, const matrix& rhs){
        if((lhs.rows() != rhs.rows()) || (lhs.cols() != rhs.cols())){
            throw std::logic_error("addition of matrices of different sizes.");
        }
        matrix sum(lhs);
        sum+=rhs;
        return sum;
    }
    matrix operator*(const matrix& lhs, const matrix& rhs){
        if(lhs.cols() != rhs.rows()){
            throw std::logic_error("multiplication of incompatible matrices");
        }
        matrix prod(lhs);
        prod*=rhs;
        return prod;
    }
    matrix operator*(const matrix& lhs, double rhs){
        matrix prod(lhs);
        prod*=rhs;
        return prod;
    }
    matrix operator*(double lhs, const matrix& rhs){
        matrix prod(rhs);
        prod*=lhs;
        return prod;
    }

    column operator*(const matrix& lhs, const column& rhs){
        if(lhs.cols() != rhs.size()){
            throw std::logic_error("multiplication of incompatible matrix and column.");
        }
        column out(lhs.rows());
        for(size_t  i = 0; i < out.size(); ++i){
            double cell = 0.0;
            for(size_t  j = 0; j < rhs.size(); ++j){
                cell += lhs[i][j] * rhs[j];
            }
            out[i] = cell;
        }
        return out;
    }

    row operator*(const row& lhs, const matrix& rhs){
        if(lhs.size() != rhs.rows()){
            throw std::logic_error("multiplication of incompatible row and matrix.");
        }
        row out(rhs.cols());
        for(size_t  i = 0; i < out.size(); ++i){
            double cell = 0.0;
            for(size_t  j = 0; j < lhs.size(); ++j){
                cell += lhs[j] * rhs[j][i];
            }
            out[i] = cell;
        }
        return out;
    }

    matrix operator*(const column& lhs, const row& rhs){
        if(lhs.size() != rhs.size()){
            throw std::logic_error("multiplication of incompatible column and row.");
        }
        matrix out(lhs.size(), rhs.size());
        for(size_t  i = 0; i < out.rows(); ++i){
            for(size_t  j = 0; j < out.cols(); ++j){
                out[i][j] = lhs[i] * rhs[j];
            }
        }
        return out;
    }

    double operator*(const row& lhs, const column& rhs){
        if(lhs.size() != rhs.size()){
            throw std::logic_error("multiplying incompatible row and column.");
        }
        double out = 0.0;
        for(size_t  i = 0; i < lhs.size(); ++i){
            out += lhs[i]*rhs[i];
        }
        return out;
    }
}
