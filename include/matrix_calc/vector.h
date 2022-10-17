#pragma once
#include <cstddef>

#include "matrix.h"

namespace mtx {
    template<size_t N>
    class vector {

    private:
        matrix<1,N> buffer;
    };
}
