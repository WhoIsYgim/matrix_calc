#pragma once
#include <initializer_list>
#include <cstddef>


namespace mtx {
    class IVector{
    public:
        IVector(std::initializer_list<double> list);
        IVector(std::size_t n, double value = 0);
        IVector(const IVector& other);
        IVector(IVector&& other) noexcept;
        virtual ~IVector();

        // slice-methods
        IVector& slice(size_t start, size_t stop, int step = 1);
        void append(double rhs);

        double& at(std::size_t n);
        double& operator[](size_t n) const;
        IVector& operator*=(double rhs);

        std::size_t size() const;
    protected:
        std::size_t size_;
        std::size_t capacity;
        double *buffer;

        void realloc();
    };

    class vector: public IVector{
    public:
        vector(std::initializer_list<double> list);
        vector(std::size_t n, double value = 0);
        vector(const vector &other);
        vector(vector &&other) noexcept;
        ~vector() override = default;

        vector reverse();
        vector& operator+=(const vector& rhs);
    };

    vector operator+(const vector& lhs, const vector& rhs);
    vector operator*(const vector& lhs, double rhs);
    vector operator*(double lhs, const vector& rhs);

}
