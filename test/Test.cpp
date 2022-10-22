#include "gtest/gtest.h"
#include "matrix_calc/matrix.h"

TEST(MATRIX, matrix_constr){
    EXPECT_EQ(1,1);
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
