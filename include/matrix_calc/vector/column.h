#ifndef MATRIX_CALCULATOR_COLUMN_H
#define MATRIX_CALCULATOR_COLUMN_H
#include "matrix_calc/vector.h"


namespace mtx{
    class row;

    class column: public IVector {
    public:
        column(std::initializer_list<double> list);
        column(std::size_t n, double value = 0);
        column(const column &other);
        column(column &&other) noexcept;
        ~column() override = default;

        column reverse();
        row inverse();

        column& operator+=(const column& rhs);
    };

    column operator+(const column& lhs, const column& rhs);
    column operator*(const column& lhs, double rhs);
    column operator*(double lhs, const column& rhs);

    double operator*(const row& lhs, const column& rhs);
}
#endif //MATRIX_CALCULATOR_COLUMN_H
