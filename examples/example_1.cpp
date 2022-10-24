#include "matrix_calc/matrix.h"

int main(){


    mtx::vector v{1,2,3};
    v.append(4);

    mtx::row r{2};
    r.append(4);

    for(size_t i = 0; i < r.size(); ++i){
       std::cout << r[i] << " ";
    }


    return 0;
}