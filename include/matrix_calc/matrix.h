#pragma once
#include <cstddef>
#include <iostream>

namespace mtx {
    template<size_t M, size_t N = M>
    class matrix{
    public:
       //matrix();
       size_t rows = M;
       size_t cols = N;

       double& operator()(size_t m, size_t n){
           return buffer[m][n];
       }

       matrix<1,N> get_row(size_t n){
           if (n > M){
               throw std::out_of_range("out of range");
           }
           matrix<1,N> row;
           for (int i = 0; i < N; ++i){
               row(0,i) = buffer[n][i];
           }
           return row;
       }

       matrix<M, 1> get_col(size_t n){
           if(n > N){
               throw std::out_of_range("out of range");
           }
           matrix<M, 1> col;
           for (int i = 0; i < N; ++i){
               col(i,0) = buffer[i][n];
           }
           return col;
       }
    private:
        double buffer[M][N];
    };

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


}


