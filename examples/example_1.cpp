#include <iostream>

#include "matrix_calc/matrix.h"
#include "matrix_calc/vector.h"

int main(){


    mtx::vector vec_1(10, 2);

    for(int i = 0; i < vec_1.size(); ++i){
        std::cout << vec_1[i] << " ";
    }

    std::cout << std::endl;
    mtx::vector vec_2(10, 3);

    for(int i = 0; i < vec_2.size(); ++i){
        std::cout << vec_2[i] << " ";
    }

    std::cout << std::endl;
    vec_1 += vec_2;
    for(int i = 0; i < vec_1.size(); ++i){
        std::cout << vec_1[i] << " ";
    }

    mtx::vector vec_3 = vec_1 + 3*vec_2;
    std::cout << std::endl;
    for(int i = 0; i < vec_3.size(); ++i){
        std::cout << vec_3[i] << " ";
    }

    std::cout << std::endl;

    mtx::vector vec_4{1,2,3,4,5,6};

    for(int i = 0; i < vec_4.size(); ++i){
        std::cout << vec_4[i] << " ";
    }

    std::cout << std::endl;

    mtx::matrix mt_1({vec_1, vec_2, vec_3});

    for(int i = 0; i < mt_1.rows(); ++i){
        for(int j = 0; j < mt_1.cols(); ++j){
            std::cout << mt_1[i][j] << " ";
        }
        std::cout << std::endl;
    }

    std::cout << std::endl;
    std::cout << std::endl;

    mt_1[0][0] = 12.0;

    for(int i = 0; i < mt_1.rows(); ++i){
        for(int j = 0; j < mt_1.cols(); ++j){
            std::cout << mt_1[i][j] << " ";
        }
        std::cout << std::endl;
    }

    std::cout << std::endl;


    mtx::row r_1{1,2,3,4};

    return 0;
}