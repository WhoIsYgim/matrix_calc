#pragma once
#include <cstddef>

#include "matrix_calc/vector.h"
#include "matrix_calc/vector/row.h"
#include "matrix_calc/vector/column.h"

namespace mtx {
    class matrix {
    public:
        matrix(std::initializer_list<vector> list);
        matrix(std::initializer_list<column> list);
        matrix(std::initializer_list<row> list);
        matrix(std::size_t m, std::size_t n, double value = 0.0);
        matrix(const matrix &other);
        matrix(matrix &&other) noexcept;
        ~matrix();

        row get_row(std::size_t m);
        column get_col(std::size_t n);

        vector main_diagonal();
        vector secondary_diagonal();

        matrix transposed();
        matrix inverse();
        double determinant();

        void append(const row &rhs);
        void append(const column &rhs);

        double *operator[](std::size_t m) const;
        matrix &operator=(const matrix &other);
        matrix &operator=(matrix &&other) noexcept;
        matrix &operator+=(const matrix &rhs);
        matrix &operator*=(const matrix &rhs);
        matrix &operator*=(double rhs);

        std::size_t cols() const;
        std::size_t rows() const;
    private:
        std::size_t cols_;
        std::size_t rows_;
        std::size_t cols_cap;
        std::size_t rows_cap;
        double **buffer;


        void realloc(std::size_t _rows, std::size_t _cols);
    };

    matrix operator+(const matrix &lhs, const matrix &rhs);
    matrix operator*(const matrix &lhs, const matrix &rhs);
    matrix operator*(const matrix &lhs, double rhs);
    matrix operator*(double lhs, const matrix &rhs);
    matrix operator*(const column &lhs, const row &rhs);
    column operator*(const matrix &lhs, const column &rhs);
    row operator*(const row &lhs, const matrix &rhs);
    double operator*(const row &lhs, const column &rhs);
}
