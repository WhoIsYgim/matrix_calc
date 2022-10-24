#pragma once
#include <cstddef>
#include <iostream>
#include <vector>

#include "matrix_calc/vector.h"
#include "matrix_calc/vector/row.h"
#include "matrix_calc/vector/column.h"

namespace mtx {
    class matrix{
    public:
        matrix(std::initializer_list<vector> list);
        matrix(std::initializer_list<column> list);
        matrix(std::initializer_list<row> list);
        matrix(std::size_t m, std::size_t n, double value = 0.0);
        matrix(const matrix& other);
        matrix(matrix&& other) noexcept;
        ~matrix();

        row get_row(std::size_t m);
        column get_col(std::size_t n);
        vector main_diagonal();
        vector secondary_diagonal();

        matrix transposed();
        matrix inverse();
        double determinant();
        void append(const row& rhs);
        void append(const column& rhs);

        double* operator[](std::size_t m) const;
        matrix& operator= (const matrix& other);
        matrix& operator= (matrix&& other) noexcept;
        matrix& operator+=(const matrix& rhs);
        matrix& operator*=(const matrix& rhs);
        matrix& operator*=(double rhs);

        std::size_t cols() const;
        std::size_t rows() const;
    private:
        std::size_t cols_;
        std::size_t rows_;
        std::size_t cols_cap;
        std::size_t rows_cap;
        double** buffer;


        void realloc(std::size_t _rows, std::size_t _cols);
    };

    matrix operator+(const matrix& lhs, const matrix& rhs);
    matrix operator*(const matrix& lhs, const matrix& rhs);
    matrix operator*(const matrix& lhs, double rhs);
    matrix operator*(double lhs, const matrix& rhs);

    matrix operator*(const column& lhs, const row& rhs);
    column operator*(const matrix& lhs, const column& rhs);
    row    operator*(const row& lhs, const matrix& rhs);
    double operator*(const row& lhs, const column& rhs);

    /*
      ________________________________
      COMPILE-TIME MATRIX DECLARATION
      ________________________________
     */

    template<size_t M, size_t N = M>
    class matrix_ct{
    public:
        matrix_ct(double value = 0);
        matrix_ct(const matrix_ct<M, N>& other);

        double* operator[](std::size_t m) const;
        matrix_ct& operator= (const matrix_ct& other);
        matrix_ct& operator+=(const matrix_ct& rhs);
        matrix_ct& operator*=(double rhs);

        size_t rows();
        size_t cols();

    private:
        matrix buffer;
    };

    /*
     _________________________________________________________
            DEFINITIONS for Compile-time matrix's methods
     _________________________________________________________
     */

    template<size_t M, size_t N>
    matrix_ct<M, N>::matrix_ct(double value)
    :buffer(M, N, value)
    {}

    template<size_t M, size_t N>
    matrix_ct<M, N>::matrix_ct(const matrix_ct<M, N> &other)
    :buffer(other.buffer)
    {}


    template<size_t M, size_t N>
    double *matrix_ct<M, N>::operator[](std::size_t m) const {
        return buffer[m];
    }

    template<size_t M, size_t N>
    matrix_ct<M,N> &matrix_ct<M, N>::operator=(const matrix_ct<M,N> &other) {
        if(&other == this){
            return *this;
        }
        buffer = other.buffer;
        return *this;
    }

    template<size_t M, size_t N>
    matrix_ct<M,N> &matrix_ct<M, N>::operator+=(const matrix_ct<M,N> &rhs) {
        buffer += rhs.buffer;
        return *this;
    }

    template<size_t M, size_t N>
    matrix_ct<M, N> &matrix_ct<M, N>::operator*=(double rhs) {
        buffer *= rhs;
        return *this;
    }

    template<size_t M, size_t N, size_t K>
    matrix_ct<M,K> operator*(matrix_ct<M,N> left, matrix_ct<N, K> right){
        matrix_ct<M,K> out;
        for(size_t i = 0; i < M; ++i) {
            for (size_t j = 0; j < K; ++j) {
                double cell = 0.0;
                for (size_t k = 0; k < N; ++k) {
                    cell += left[i][k] * right[k][j];
                }
                out[i][j] = cell;
            }
        }
        return out;
    }

    template<size_t M, size_t N>
    matrix_ct<M,N> operator+(matrix_ct<M,N> left, matrix_ct<M,N> right){
        matrix_ct<M,N> out;
        for(size_t i = 0; i < M; ++i) {
            for (size_t j = 0; j < N; ++j) {
                out[i][j] = left[i][j] + right[i][j];
            }
        }
        return out;
    }

    template<size_t M, size_t N>
    size_t matrix_ct<M, N>::rows() {
        return M;
    }

    template<size_t M, size_t N>
    size_t matrix_ct<M, N>::cols() {
        return N;
    }

}
