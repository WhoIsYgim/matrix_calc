#include "gtest/gtest.h"

#include "matrix_calc/vector.h"
#include "matrix_calc/vector/row.h"
#include "matrix_calc/vector/column.h"
#include "matrix_calc/matrix.h"

class TestVectors : public ::testing::Test {
protected:
    mtx::vector v3;
    mtx::column c3;
    mtx::row r3;
    mtx::vector v2;
    mtx::column c2;
    mtx::row r2;

    void SetUp() override{
        for(size_t i = 0; i < v3.size(); ++i){
            v3[i] = double (i);
            c3[i] = double (i);
            r3[i] = double (i);
        }
    }
    TestVectors():
            v3(3), c3(3), r3(3),
            v2(2), c2(2), r2(2)
    {}
    void TearDown() override{}
};


TEST_F(TestVectors, size_val_constr){
    mtx::vector v_t(3,5);
    EXPECT_EQ(v_t.size(), 3);
    EXPECT_DOUBLE_EQ(v_t[0], 5);

    mtx::column c_t(3, 5);
    EXPECT_EQ(c_t.size(), 3);
    EXPECT_DOUBLE_EQ(c_t[0], 5);

    mtx::row r_t(3);
    EXPECT_EQ(r_t.size(), 3);
    EXPECT_DOUBLE_EQ(r_t[0], 0);
}

TEST_F(TestVectors, copy_constr){
    auto v_t(v3);
    auto c_t(c3);
    auto r_t(r3);
    for(size_t i = 0; i < v_t.size(); ++i){
        EXPECT_DOUBLE_EQ(v_t[i], v3[i]);
        EXPECT_DOUBLE_EQ(c_t[i], c3[i]);
        EXPECT_DOUBLE_EQ(r_t[i], r3[i]);
    }
}

TEST_F(TestVectors, list_constr){
    mtx::vector v_t{0, 1, 2};
    mtx::column c_t{0, 1, 2};
    mtx::row r_t{0, 1, 2};
    for(size_t i = 0; i < v_t.size(); ++i){
        EXPECT_DOUBLE_EQ(v_t[i], v3[i]);
        EXPECT_DOUBLE_EQ(c_t[i], c3[i]);
        EXPECT_DOUBLE_EQ(r_t[i], r3[i]);
    }
}

TEST_F(TestVectors, move_constr){
    mtx::vector pivot_v(v3);
    mtx::column pivot_c(c3);
    mtx::row pivot_r(r3);

    mtx::vector v_t(std::move(pivot_v));
    auto c_t(std::move(pivot_c));
    auto r_t(std::move(pivot_r));

    for(size_t i = 0; i < v_t.size(); ++i){
        EXPECT_DOUBLE_EQ(v_t[i], v3[i]);
        EXPECT_DOUBLE_EQ(c_t[i], c3[i]);
        EXPECT_DOUBLE_EQ(r_t[i], r3[i]);
    }

    EXPECT_THROW(pivot_v.at(0), std::out_of_range);
    EXPECT_THROW(pivot_c.at(0), std::out_of_range);
    EXPECT_THROW(pivot_r.at(0), std::out_of_range);
}

TEST_F(TestVectors, append){
    mtx::vector v_t(v3);
    mtx::column c_t(c3);
    mtx::row r_t(r3);

    v_t.append(3);
    c_t.append(3);
    r_t.append(3);

    EXPECT_EQ(v_t.size(), 4);
    EXPECT_EQ(v_t[3], 3);
    EXPECT_EQ(c_t.size(), 4);
    EXPECT_EQ(c_t[3], 3);
    EXPECT_EQ(r_t.size(), 4);
    EXPECT_EQ(r_t[3], 3);
}
TEST_F(TestVectors, reverse){
    mtx::vector v_t = v3.reverse();
    mtx::column c_t = c3.reverse();
    mtx::row r_t = r3.reverse();

    for(size_t i = 0; i < v_t.size(); ++i){
        EXPECT_DOUBLE_EQ(v_t[i], v3[v_t.size()-i-1]);
        EXPECT_DOUBLE_EQ(c_t[i], c3[c_t.size()-i-1]);
        EXPECT_DOUBLE_EQ(r_t[i], r3[r_t.size()-i-1]);
    }
}

TEST_F(TestVectors, inverse){
    mtx::column c_t = r3.inverse();
    mtx::row r_t = c3.inverse();

    EXPECT_EQ(c_t.size(), r3.size());
    EXPECT_EQ(r_t.size(), c3.size());

    for(size_t i = 0; i < c_t.size(); ++i){
        EXPECT_DOUBLE_EQ(c_t[i], r3[i]);
        EXPECT_DOUBLE_EQ(r_t[i], c3[i]);
    }

}
TEST_F(TestVectors, plus){
    mtx::vector v_t(v3);
    mtx::column c_t(c3);
    mtx::row r_t(r3);

    v_t += v3;
    c_t += c3;
    r_t += r3;

    for(size_t i = 0; i < v_t.size(); ++i){
        EXPECT_DOUBLE_EQ(v_t[i], 2*v3[i]);
        EXPECT_DOUBLE_EQ(c_t[i], 2*c3[i]);
        EXPECT_DOUBLE_EQ(r_t[i], 2*r3[i]);
    }

    EXPECT_THROW(v_t+=v2, std::logic_error);
    EXPECT_THROW(c_t+=c2, std::logic_error);
    EXPECT_THROW(r_t+=r2, std::logic_error);
}
TEST_F(TestVectors, multiply_double){
    mtx::vector v_t(v3);
    mtx::column c_t(c3);
    mtx::row r_t(r3);

    v_t *= 2;
    c_t *= 2;
    r_t *= 2;

    for(size_t i = 0; i < v_t.size(); ++i){
        EXPECT_DOUBLE_EQ(v_t[i], 2*v3[i]);
        EXPECT_DOUBLE_EQ(c_t[i], 2*c3[i]);
        EXPECT_DOUBLE_EQ(r_t[i], 2*r3[i]);
    }
}
TEST_F(TestVectors, muliply_other){
    double d_t = r3*c3;
    EXPECT_DOUBLE_EQ(d_t, 5);

    EXPECT_THROW(r3*c2, std::logic_error);

    mtx::matrix m_t = c3*r3;
    EXPECT_EQ(m_t.rows(), c3.size());
    EXPECT_EQ(m_t.cols(), r3.size());

    for(size_t i = 0; i < m_t.rows(); ++i){
        for(size_t j = 0; j < m_t.cols(); ++j){
            EXPECT_DOUBLE_EQ(m_t[i][j], c3[i]*r3[j]);
        }
    }

    EXPECT_THROW(r2*c3, std::logic_error);
}
