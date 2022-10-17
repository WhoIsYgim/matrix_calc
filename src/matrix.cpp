#include "matrix.h"

namespace mtx{
  //  template<size_t M, size_t N>
//    matrix<1,N> matrix<M, N>::get_row(size_t n){
//        matrix<1,N> row;
//        for (int i = 0; i < N; ++i){
//            row(0,i) = buffer[n][i];
//        }
//        return row;
//    }

//    template<size_t M, size_t N>
//    double &matrix<M, N>::operator()(size_t m, size_t n) {
//        return buffer[m][n];
//    }
//
//    template<size_t M, size_t N, size_t K>
//    matrix<M,K>& operator*(matrix<M,N> left, matrix<N, K> right){
//        matrix<M, K> product;
//        for(int i = 0; i < M; ++i){
//            for(int j = 0; j < K; ++j){
//                double cur_cell_value = 0;
//                for (int k = 0; k < N; ++k){
//                    cur_cell_value += left(i,k) * right(k,j);
//                }
//                product(i,j) = cur_cell_value;
//            }
//        }
//        return product;
//    }


}



