#include "gtest/gtest.h"
#include "matrix_calc/matrix.h"
#include "matrix_calc/vector.h"

mtx::matrix set_up(size_t m, size_t n){
    mtx::matrix test_matrix(m, n);
    for(size_t i = 0; i < test_matrix.rows(); ++i){
        for(size_t j = 0; j < test_matrix.cols(); ++j){
            test_matrix[i][j] = double(i+j);
        }
    }
    return test_matrix;
}

TEST(MATRIX_CONSTRUCTOR, list_vector){
    auto t_matrix = set_up(2,3);
    mtx::vector v1{0,1,2};
    mtx::vector v2{1,2,3};
    mtx::matrix target{v1, v2};

    EXPECT_EQ(target[0][1], t_matrix[0][1]);
    EXPECT_EQ(target[1][1], t_matrix[1][1]);
    EXPECT_EQ(target.rows(), 2);
    EXPECT_EQ(target.cols(), 3);
}

TEST(MATRIX_CONSTRUCTOR, list_vector_invalid){
    mtx::vector v1{0,1,2,4};
    mtx::vector v2{1,2,3};

    EXPECT_THROW(mtx::matrix({v1,v2}),std::logic_error);
}

TEST(MATRIX_CONSTRUCTOR, list_column){
    auto t_matrix = set_up(2,3);
    mtx::column c1{0,1};
    mtx::column c2{1,2};
    mtx::column c3{2,3};
    mtx::matrix target{c1, c2, c3};

    EXPECT_EQ(target[0][1], t_matrix[0][1]);
    EXPECT_EQ(target[1][1], t_matrix[1][1]);
    EXPECT_EQ(target.rows(), 2);
    EXPECT_EQ(target.cols(), 3);
}

TEST(MATRIX_CONSTRUCTOR, list_row){
    auto t_matrix = set_up(2,3);
    mtx::row r1{0,1,2};
    mtx::row r2{1,2,3};
    mtx::matrix target{r1, r2};

    EXPECT_EQ(target[0][1], t_matrix[0][1]);
    EXPECT_EQ(target[1][1], t_matrix[1][1]);
    EXPECT_EQ(target.rows(), 2);
    EXPECT_EQ(target.cols(), 3);
}

TEST(MATRIX_CONSTRUCTOR, size_value_0){
    mtx::matrix target(3,4);
    EXPECT_EQ(target.rows(), 3);
    EXPECT_EQ(target.cols(), 4);
    EXPECT_EQ(target[0][0], 0);
    EXPECT_EQ(target[2][3], 0);
}

TEST(MATRIX_CONSTRUCTOR, size_value_5){
    mtx::matrix target(3,4,5);
    EXPECT_EQ(target.rows(), 3);
    EXPECT_EQ(target.cols(), 4);
    EXPECT_EQ(target[0][0], 5);
    EXPECT_EQ(target[2][3], 5);
}

TEST(MATRIX_CONSTRUCTOR, copy){
    auto t_matrix = set_up(2,3);
    mtx::matrix target(t_matrix);
    EXPECT_EQ(target.rows(), t_matrix.rows());
    EXPECT_EQ(target.cols(), t_matrix.cols());
    EXPECT_EQ(target[0][0], t_matrix[0][0]);
    EXPECT_EQ(target[1][1], t_matrix[1][1]);
}

TEST(MATRIX_CONSTRUCTOR, move){
    auto t_matrix = set_up(2,3);
    auto pivot(t_matrix);
    mtx::matrix target(std::move(t_matrix));
    EXPECT_EQ(target.rows(), pivot.rows());
    EXPECT_EQ(target.cols(), pivot.cols());
    EXPECT_EQ(target[0][0], pivot[0][0]);
    EXPECT_EQ(target[1][1], pivot[1][1]);
    EXPECT_EQ(t_matrix.cols(), 0);
    EXPECT_EQ(t_matrix.rows(), 0);
    EXPECT_THROW(t_matrix[0], std::out_of_range);
}

TEST(GET_ROW, get_row_valid){
    auto t_matrix = set_up(2,3);
    mtx::row t_row{0,1,2};
    mtx::row target = t_matrix.get_row(0);
    EXPECT_EQ(target[0], t_row[0]);
    EXPECT_EQ(target[1], t_row[1]);
    EXPECT_EQ(target[2], t_row[2]);
}


TEST(GET_COL, get_row_non_valid) {
    auto t_matrix = set_up(2, 3);
    EXPECT_THROW(t_matrix.get_row(3), std::out_of_range);
}

TEST(GET_ROW, get_col_valid){
    auto t_matrix = set_up(2,3);
    mtx::column t_col{0,1};
    mtx::column target = t_matrix.get_col(0);
    EXPECT_EQ(target[0], t_col[0]);
    EXPECT_EQ(target[1], t_col[1]);
}


TEST(GET_COL, get_col_non_valid) {
    auto t_matrix = set_up(2, 3);
    EXPECT_THROW(t_matrix.get_col(3), std::out_of_range);
}

TEST(MAIN_DIAG, square_matrix){
    auto t_matrix = set_up(3,3);
    auto target = t_matrix.main_diagonal();
    EXPECT_EQ(target [0], 0);
    EXPECT_EQ(target [1], 2);
    EXPECT_EQ(target [2], 4);

}

TEST(MAIN_DIAG, non_square_matrix){
    auto t_matrix = set_up(2,3);
    EXPECT_THROW(t_matrix.main_diagonal(), std::logic_error);
}

TEST(SECOND_DIAG, square_matrix){
    auto t_matrix = set_up(3,3);
    auto target = t_matrix.secondary_diagonal();
    EXPECT_EQ(target [0], 2);
    EXPECT_EQ(target [1], 2);
    EXPECT_EQ(target [2], 2);
}

TEST(SECOND_DIAG, non_square_matrix){
    mtx::matrix t_matrix(2,3);
    EXPECT_THROW(t_matrix.secondary_diagonal(), std::logic_error);
}

TEST(TRANSPOSE, square_matrix){
    auto t_matrix = set_up(3,3);
    auto target1 = t_matrix.transposed();
    auto target2 = target1.transposed();

    EXPECT_EQ(target1[1][2], t_matrix[2][1]);
    EXPECT_EQ(target2[1][2], t_matrix[1][2]);
    EXPECT_EQ(target1.rows(), t_matrix.cols());
    EXPECT_EQ(target1.cols(), t_matrix.rows());
}


TEST(TRANSPOSE, non_square_matrix){
    auto t_matrix = set_up(3,4);
    auto target1 = t_matrix.transposed();
    auto target2 = target1.transposed();

    EXPECT_EQ(target1[1][2], t_matrix[2][1]);
    EXPECT_EQ(target2[1][2], t_matrix[1][2]);
    EXPECT_EQ(target1.rows(), t_matrix.cols());
    EXPECT_EQ(target1.cols(), t_matrix.rows());
}


TEST(DETERMINANT, square_2) {
    auto t_matrix = set_up(3, 3);

    EXPECT_EQ(t_matrix.determinant(), 0);
    t_matrix[2][2] = 8;
    EXPECT_EQ(t_matrix.determinant(), -4);
}
TEST(DETERMINANT, square_4){
    auto t_matrix = set_up(4,4);
    EXPECT_TRUE(t_matrix.determinant() < 1.0e-10);
    t_matrix[0][3] =9;
    t_matrix[1][2] =83.0;
    EXPECT_TRUE(t_matrix.determinant()-480 < 1.0e-10);
}


TEST(DETERMINANT, non_square){
    auto t_matrix = set_up(2,3);
    EXPECT_THROW(t_matrix.determinant(), std::logic_error);
}

TEST(INVERSE, square){
    mtx::vector v1{2,3,2};
    mtx::vector v2{3,4,6};
    mtx::vector v3{6,7,8};

    mtx::matrix t_matrix{v1,v2,v3};
    auto target = t_matrix.inverse();

    EXPECT_TRUE( abs(target[0][0] + 1) < 1.0e-10);
    EXPECT_TRUE( abs(target[0][1] + 1) < 1.0e-10);
    EXPECT_TRUE( abs(target[0][2] - 1) < 1.0e-10);
    EXPECT_TRUE( abs(target[2][0]+0.3)  < 1.0e-10);
    EXPECT_TRUE( abs(target[2][1]-0.4)  < 1.0e-10);

    target = target.inverse();

    EXPECT_TRUE( abs(target[0][0] - t_matrix[0][0])< 1.0e-10);
    EXPECT_TRUE( abs(target[0][1] - t_matrix[0][1])< 1.0e-10);
    EXPECT_TRUE( abs(target[0][2] - t_matrix[0][2])< 1.0e-10);
    EXPECT_TRUE( abs(target[2][0] - t_matrix[2][0])< 1.0e-10);
    EXPECT_TRUE( abs(target[2][1] - t_matrix[2][1])< 1.0e-10);
}

TEST(INVERSE, non_square){
    mtx::vector v1{2,3};
    mtx::vector v2{3,4};
    mtx::vector v3{6,7};

    mtx::matrix t_matrix{v1,v2,v3};
    EXPECT_THROW(t_matrix.inverse(), std::logic_error);
}