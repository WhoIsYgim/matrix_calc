#pragma once
#include <cstddef>
#include <iostream>

namespace mtx {
    template<size_t M, size_t N = M>
    class matrix{
    public:
       const size_t rows = M;
       const size_t cols = N;

       double& operator()(size_t m, size_t n);

       matrix<1,N> get_row(size_t n);

       matrix<M, 1> get_col(size_t n);
    private:
        double buffer[M][N]{0};
    };

    template<size_t M, size_t N, size_t K>
    matrix<M,K> operator*(matrix<M,N> left, matrix<N, K> right);


    /*
     _________________________
            DEFINITIONS
     _________________________
     */

    template<size_t M, size_t N>
    double &matrix<M, N>::operator()(size_t m, size_t n) {
        if(m >= M || n >= N ){
            throw std::out_of_range("out of range");
        }
        return buffer[m][n];
    }


    template<size_t M, size_t N>
    matrix<1,N> matrix<M, N>::get_row(size_t n){
        if (n > M){
            throw std::out_of_range("out of range");
        }
        matrix<1,N> row;
        for (int i = 0; i < N; ++i){
            row(0,i) = buffer[n][i];
        }
        return row;
    }

    template<size_t M, size_t N>
    matrix<M, 1> matrix<M,N>::get_col(size_t n){
        if(n >= M){
            throw std::out_of_range("out of range");
        }
        matrix<M, 1> col;
        for (int i = 0; i < M; ++i){
            col(i,0) = buffer[i][n];
        }
        return col;
    }

    template<size_t M, size_t N, size_t K>
    matrix<M,K> operator*(matrix<M,N> left, matrix<N, K> right){
        matrix<M, K> product;
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
    double determinant(matrix<M, M> matrix){
        return 0.0;
    }
}
