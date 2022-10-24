#include "gtest/gtest.h"
#include "matrix_calc/matrix.h"
#include "matrix_calc/vector.h"

class TestMatrix : public ::testing::Test {
protected:
    mtx::matrix m22;
    mtx::matrix m23;
    mtx::matrix m32;
    mtx::matrix m33;

    void SetUp() override {
        for (size_t i = 0; i < m22.rows(); ++i) {
            for (size_t j = 0; j < m22.cols(); ++j) {
                m22[i][j] = double(i + j);
            }
        }
        for (size_t i = 0; i < m23.rows(); ++i) {
            for (size_t j = 0; j < m23.cols(); ++j) {
                m23[i][j] = double(i + j);
            }
        }
        for (size_t i = 0; i < m32.rows(); ++i) {
            for (size_t j = 0; j < m32.cols(); ++j) {
                m32[i][j] = double(i + j);
            }
        }
        for (size_t i = 0; i < m33.rows(); ++i) {
            for (size_t j = 0; j < m33.cols(); ++j) {
                m33[i][j] = double(i + j);
            }
        }
    }

    TestMatrix() :
            ::testing::Test(), m22(2, 2), m23(2,3), m32(3,2), m33(3, 3){}
    void TearDown() override {}
};

TEST_F(TestMatrix, size_value_const){
    EXPECT_EQ(m33.rows(), 3);
    EXPECT_EQ(m33.cols(), 3);
    EXPECT_EQ(m23.rows(), 2);
    EXPECT_EQ(m23.cols(), 3);
    EXPECT_EQ(m32.rows(), 3);
    EXPECT_EQ(m32.cols(), 2);

    mtx::matrix m22_4(2,2,4);
    for(size_t i = 0; i < m22_4.rows(); ++i){
        EXPECT_DOUBLE_EQ(m22_4[i][i], 4);
    }
    mtx::matrix m22_def(2,2);
    for(size_t i = 0; i < m22_def.rows(); ++i){
        EXPECT_DOUBLE_EQ(m22_def[i][i], 0);
    }
}

TEST_F(TestMatrix, vector_list_constr){
    mtx::vector v1{0,1,2};
    mtx::vector v2{1,2,3};
    mtx::vector v3{2,3,4};
    mtx::matrix target{v1, v2, v3};

    EXPECT_DOUBLE_EQ(target[0][0], m33[0][0]);
    EXPECT_DOUBLE_EQ(target[0][1], m33[0][1]);
    EXPECT_DOUBLE_EQ(target[0][2], m33[0][2]);
    EXPECT_DOUBLE_EQ(target[1][0], m33[1][0]);
    EXPECT_DOUBLE_EQ(target[1][1], m33[1][1]);
    EXPECT_DOUBLE_EQ(target[1][2], m33[1][2]);
    EXPECT_DOUBLE_EQ(target[2][0], m33[2][0]);
    EXPECT_DOUBLE_EQ(target[2][1], m33[2][1]);
    EXPECT_DOUBLE_EQ(target[2][2], m33[2][2]);

    EXPECT_EQ(target.rows(), m33.rows());
    EXPECT_EQ(target.cols(), m33.cols());

    mtx::vector v4{0,1};
    EXPECT_THROW(mtx::matrix({v3,v4}),std::logic_error);
}


TEST_F(TestMatrix, column_list_constr){
    mtx::column c1{0, 1, 2};
    mtx::column c2{1, 2, 3};
    mtx::column c3{2, 3, 4};
    mtx::matrix target{c1, c2, c3};

    EXPECT_DOUBLE_EQ(target[0][0], m33[0][0]);
    EXPECT_DOUBLE_EQ(target[0][1], m33[0][1]);
    EXPECT_DOUBLE_EQ(target[0][2], m33[0][2]);
    EXPECT_DOUBLE_EQ(target[1][0], m33[1][0]);
    EXPECT_DOUBLE_EQ(target[1][1], m33[1][1]);
    EXPECT_DOUBLE_EQ(target[1][2], m33[1][2]);
    EXPECT_DOUBLE_EQ(target[2][0], m33[2][0]);
    EXPECT_DOUBLE_EQ(target[2][1], m33[2][1]);
    EXPECT_DOUBLE_EQ(target[2][2], m33[2][2]);

    EXPECT_EQ(target.rows(), m33.rows());
    EXPECT_EQ(target.cols(), m33.cols());

    mtx::column c4{0,1};
    EXPECT_THROW(mtx::matrix({c3,c4}),std::logic_error);
}

TEST_F(TestMatrix, list_row){
    mtx::row r1{0, 1, 2};
    mtx::row r2{1, 2, 3};
    mtx::row r3{2, 3, 4};
    mtx::matrix target{r1, r2, r3};

    EXPECT_DOUBLE_EQ(target[0][0], m33[0][0]);
    EXPECT_DOUBLE_EQ(target[0][1], m33[0][1]);
    EXPECT_DOUBLE_EQ(target[0][2], m33[0][2]);
    EXPECT_DOUBLE_EQ(target[1][0], m33[1][0]);
    EXPECT_DOUBLE_EQ(target[1][1], m33[1][1]);
    EXPECT_DOUBLE_EQ(target[1][2], m33[1][2]);
    EXPECT_DOUBLE_EQ(target[2][0], m33[2][0]);
    EXPECT_DOUBLE_EQ(target[2][1], m33[2][1]);
    EXPECT_DOUBLE_EQ(target[2][2], m33[2][2]);

    EXPECT_EQ(target.rows(), m33.rows());
    EXPECT_EQ(target.cols(), m33.cols());

    mtx::row r4{0,1};
    EXPECT_THROW(mtx::matrix({r3,r4}),std::logic_error);
}


TEST_F(TestMatrix, copy_constr){
    mtx::matrix target(m33);

    EXPECT_EQ(target.rows(), m33.rows());
    EXPECT_EQ(target.cols(), m33.cols());

    for(size_t i = 0; i < target.rows(); ++i){
        for(size_t j = 0; j < target.cols(); ++j){
            EXPECT_DOUBLE_EQ(target[i][j], m33[i][j]);
        }
    }
}

TEST_F(TestMatrix, move_constr){
    mtx::matrix pivot(m33);
    mtx::matrix target(std::move(pivot));

    EXPECT_EQ(target.rows(), m33.rows());
    EXPECT_EQ(target.cols(), m33.cols());

    for(size_t i = 0; i < target.rows(); ++i){
        for(size_t j = 0; j < target.cols(); ++j){
            EXPECT_DOUBLE_EQ(target[i][j], m33[i][j]);
        }
    }

    EXPECT_EQ(pivot.cols(), 0);
    EXPECT_EQ(pivot.rows(), 0);
    EXPECT_THROW(pivot[0], std::out_of_range);
}

TEST_F(TestMatrix, get_row){
    mtx::row t_row{0,1,2};

    mtx::row target = m33.get_row(0);

    EXPECT_EQ(target.size(), t_row.size());
    EXPECT_DOUBLE_EQ(target[0], t_row[0]);
    EXPECT_DOUBLE_EQ(target[1], t_row[1]);
    EXPECT_DOUBLE_EQ(target[2], t_row[2]);

    EXPECT_THROW(m33.get_row(3), std::out_of_range);
}

TEST_F(TestMatrix, get_col){
    mtx::column t_col{0,1};
    mtx::column target = m23.get_col(0);
    EXPECT_DOUBLE_EQ(target[0], t_col[0]);
    EXPECT_DOUBLE_EQ(target[1], t_col[1]);

    EXPECT_THROW(m23.get_col(3), std::out_of_range);
}

TEST_F(TestMatrix, main_diag){
    auto target = m33.main_diagonal();
    EXPECT_DOUBLE_EQ(target[0], 0);
    EXPECT_DOUBLE_EQ(target[1], 2);
    EXPECT_DOUBLE_EQ(target[2], 4);

    EXPECT_THROW(m23.main_diagonal(), std::logic_error);
}

TEST_F(TestMatrix, second_diag){
    auto target = m33.secondary_diagonal();
    EXPECT_DOUBLE_EQ(target[0], 2);
    EXPECT_DOUBLE_EQ(target[1], 2);
    EXPECT_DOUBLE_EQ(target[2], 2);

    EXPECT_THROW(m23.secondary_diagonal(), std::logic_error);
}

TEST_F(TestMatrix, transpose){
    auto target1 = m33.transposed();
    auto target2 = target1.transposed();

    EXPECT_EQ(target1.rows(), m33.cols());
    EXPECT_EQ(target1.cols(), m33.rows());
    EXPECT_EQ(target2.rows(), m33.rows());
    EXPECT_EQ(target2.cols(), m33.cols());
    for(size_t i = 0; i < m33.rows(); ++i){
        for(size_t j = 0; j < m33.cols(); ++j){
            EXPECT_DOUBLE_EQ(target1[j][i], m33[i][j]);
            EXPECT_DOUBLE_EQ(target2[i][j], m33[i][j]);
        }
    }
    auto target3 = m23.transposed();
    auto target4 = target3.transposed();

    EXPECT_EQ(target3.rows(), m23.cols());
    EXPECT_EQ(target3.cols(), m23.rows());
    EXPECT_EQ(target4.rows(), m23.rows());
    EXPECT_EQ(target4.cols(), m23.cols());

    for(size_t i = 0; i < m23.rows(); ++i){
        for(size_t j = 0; j < m23.cols(); ++j){
            EXPECT_DOUBLE_EQ(target3[j][i], m23[i][j]);
            EXPECT_DOUBLE_EQ(target4[i][j], m23[i][j]);
        }
    }
}

TEST_F(TestMatrix, determinant){
    EXPECT_DOUBLE_EQ(m33.determinant(), 0);
    m33[2][2] = 8;
    EXPECT_DOUBLE_EQ(m33.determinant(), -4);
    m33[0][0] = 10;
    EXPECT_DOUBLE_EQ(m33.determinant(), 66);
    m33[1][2] = 42.69;
    EXPECT_DOUBLE_EQ(m33.determinant(), -1045.32);

    EXPECT_THROW(m23.determinant(), std::logic_error);
}

TEST_F(TestMatrix, inverse){
    m33[2][2] = 8;
    auto target = m33.inverse();
    EXPECT_DOUBLE_EQ(target[0][0], -1.75);
    EXPECT_DOUBLE_EQ(target[0][1],  0.5);
    EXPECT_DOUBLE_EQ(target[0][2],  0.25);
    EXPECT_DOUBLE_EQ(target[1][0],  0.5);
    EXPECT_DOUBLE_EQ(target[1][1],  1.0);
    EXPECT_DOUBLE_EQ(target[1][2], -0.5);
    EXPECT_DOUBLE_EQ(target[2][0],  0.25);
    EXPECT_DOUBLE_EQ(target[2][1], -0.5);
    EXPECT_DOUBLE_EQ(target[2][2],  0.25);

    EXPECT_THROW(m23.inverse(), std::logic_error);
}
