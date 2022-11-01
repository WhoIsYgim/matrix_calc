#ifndef MATRIX_CALCULATOR_ROW_H
#define MATRIX_CALCULATOR_ROW_H

#include "matrix_calc/vector.h"


namespace mtx{
    class column;

    class row: public IVector{
    public:
        row(std::initializer_list<double> list);
        row(std::size_t n, double value = 0);
        row(const row &other);
        row(row &&other) noexcept;
        ~row() override = default;

        row reverse();
        column inverse();
        row& operator+=(const row& rhs);
    };

    row operator+(const row& lhs, const row& rhs);
    row operator*(const row& lhs, double rhs);
    row operator*(double lhs, const row& rhs);

    double operator*(const row& lhs, const column& rhs);
}
#endif //MATRIX_CALCULATOR_ROW_H
