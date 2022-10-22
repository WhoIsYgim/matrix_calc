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



    template<size_t M, size_t N = M>
    class matrix_comp{
    public:
       size_t rows(){
         return M;
       }
       size_t cols(){
           return N;
       }

       double& operator()(size_t m, size_t n);

       double* operator[](const size_t& m){
           return buffer[m];
       }

       matrix_comp<1,N> get_row(size_t n);

       matrix_comp<M, 1> get_col(size_t n);
    private:
        double buffer[M][N]{0};
    };

    template<size_t M, size_t N, size_t K>
    matrix_comp<M,K> operator*(matrix_comp<M,N> left, matrix_comp<N, K> right);


    /*
     _________________________
            DEFINITIONS
     _________________________
     */

    template<size_t M, size_t N>
    double &matrix_comp<M, N>::operator()(size_t m, size_t n) {
        if(m >= M || n >= N ){
            throw std::out_of_range("out of range");
        }
        return buffer[m][n];
    }


    template<size_t M, size_t N>
    matrix_comp<1,N> matrix_comp<M, N>::get_row(size_t n){
        if (n > M){
            throw std::out_of_range("out of range");
        }
        matrix_comp<1,N> row;
        for (int i = 0; i < N; ++i){
            row(0,i) = buffer[n][i];
        }
        return row;
    }

    template<size_t M, size_t N>
    matrix_comp<M, 1> matrix_comp<M,N>::get_col(size_t n){
        if(n >= M){
            throw std::out_of_range("out of range");
        }
        matrix_comp<M, 1> col;
        for (int i = 0; i < M; ++i){
            col(i,0) = buffer[i][n];
        }
        return col;
    }

    template<size_t M, size_t N, size_t K>
    matrix_comp<M,K> operator*(matrix_comp<M,N> left, matrix_comp<N, K> right){
        matrix_comp<M, K> product;
        for(int i = 0; i < M; ++i){
            for(int j = 0; j < K; ++j){
                double cur_cell_value = 0;
                for (int k = 0; k < N; ++k){
                    cur_cell_value += left(i,k) * right(k,j);
                }
                product(i,j) = cur_cell_value;
            }
        }

        return product;
    }

    template<size_t M>
    double determinant(matrix_comp<M, M> matrix){
        return 0.0;
    }
}
