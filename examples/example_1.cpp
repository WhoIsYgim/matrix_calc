#include "matrix_calc/matrix.h"

int main(){

    mtx::matrix_ct<2,3> m1(3);
    mtx::matrix_ct<3,2> m2(4);
    auto m3 = m1*m2;
    for(int i = 0; i < m3.rows(); ++i){
        for(int j = 0; j < m3.cols(); ++j){
            std::cout << m3[i][j] << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}