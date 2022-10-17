
#include "matrix.h"
#include <iostream>
int main(){
    mtx::matrix<3,4> m1;
    for (int i = 0; i < 3; ++i){
        for(int j = 0; j < 4; ++j){
            m1(i, j) = i+j;
        }
    }
    mtx::matrix<4, 5> m2;
    for (int i = 0; i < m2.rows; ++i){
        for(int j = 0; j < m2.cols; ++j){
            m2(i, j) = i+j;
        }
    }

    auto m3 = m1*m2;



    for (int i = 0; i < m3.rows; ++i){
        for(int j = 0; j < m3.cols; ++j){
            std::cout << m3(i, j) << " ";
        }
        std::cout << std::endl;
    }

    std::cout<<std::endl;

    auto m4 = m3.get_row(2);
    for (int i = 0; i < m4.rows; ++i){
        for(int j = 0; j < m4.cols; ++j){
            std::cout << m4(i, j) << " ";
        }
        std::cout << std::endl;
    }

    std::cout<<std::endl;

    auto m5 = m3.get_col(2);

    for (int i = 0; i < m5.rows; ++i){
        for(int j = 0; j < m5.cols; ++j){
            std::cout << m5(i, j) << " ";
        }
        std::cout << std::endl;
    }


    std::cout<< std::endl;

    auto m6 = m5*m4;
    for (int i = 0; i < m6.rows; ++i){
        for(int j = 0; j < m6.cols; ++j){
            std::cout << m6(i, j) << " ";
        }
        std::cout << std::endl;
    }

    std::cout<<std::endl;
    mtx::matrix<5,1> m8;
    for (int i = 0; i < m8.rows; ++i){
        for(int j = 0; j < m8.cols; ++j){
            m8(i, j) = i+j;
        }
    }

    auto m7 = m4*m8;
    for (int i = 0; i < m7.rows; ++i){
        for(int j = 0; j < m7.cols; ++j){
            std::cout << m7(i, j) << " ";
        }
        std::cout << std::endl;
    }

    mtx::matrix<10> a;
    mtx::determinant(a);

    for (int i = 0; i < a.rows; ++i){
        for(int j = 0; j < a.cols; ++j){
            std::cout << a(i, j) << " ";
        }
        std::cout << std::endl;
    }
    return 0;
}