#include "pch.h"
#include "matrix.h"

TEST(ClassMatrix, can_create_with_default_constructor) {
    Matrix<double> matrix;
    EXPECT_EQ(matrix.getM(), 0);
    EXPECT_EQ(matrix.getN(), 0);
}

TEST(ClassMatrix, can_create_with_constructor_by_size) {
    Matrix<double> matrix(3, 2);
    EXPECT_EQ(matrix.getN(), 3);
    EXPECT_EQ(matrix.getM(), 2);
    for (size_t i = 1; i <= 3; ++i) {
        EXPECT_EQ(matrix[i].get_size(), 2);
    }
}

TEST(ClassMatrix, can_create_with_constructor_by_init_list) {
    std::initializer_list<std::initializer_list<double>> list = { {1,1,1},{2,2,2},{3,3,3} };
    Matrix<double> matrix(list);
    EXPECT_EQ(matrix.getN(), 3);
    EXPECT_EQ(matrix.getM(), 3);
    for (size_t i = 1; i <= 3; ++i) {
        EXPECT_EQ(matrix[i][1], i);
        EXPECT_EQ(matrix[i][2], i);
        EXPECT_EQ(matrix[i][3], i);
    }
}

TEST(ClassMatrix, can_create_with_copy_constructor) {
    Matrix<double> matrix({ {1,2,3} });
    Matrix<double> copy(matrix);
    EXPECT_TRUE(matrix == copy);
}

TEST(ClassMatrix, can_add) {
    Matrix<double> matrix1({ {1,2,3} ,{1,2,3} });
    Matrix<double> matrix2({ {4,5,6},{4,5,6} });
    Matrix<double> matrix3({ {5,7,9} ,{5,7,9} });
    Matrix<double> matrix4 = matrix1 + matrix2;
    EXPECT_EQ(matrix3, matrix4);
}

TEST(ClassMatrix, can_substract) {
    Matrix<double> matrix1({ {5,7,9} ,{5,7,9} });
    Matrix<double> matrix2({ {4,5,6},{4,5,6} });
    Matrix<double> matrix3({ {1,2,3} ,{1,2,3} });
    Matrix<double> matrix4 = matrix1 - matrix2;
    EXPECT_EQ(matrix3, matrix4);
}

TEST(ClassMatrix, can_do_good_operations) {
    Matrix<double> matrix1({ {1,2,3} ,{1,2,3} });
    Matrix<double> matrix2({ {4,5,6},{4,5,6} });
    Matrix<double> matrix3(matrix1);
    Matrix<double> matrix4({ {5,7,9} ,{5,7,9} });
    matrix1 += matrix2;
    EXPECT_EQ(matrix1, matrix4);
    matrix1 -= matrix2;
    EXPECT_EQ(matrix1, matrix3);
    Matrix<double> matrix5(matrix1);
    matrix1 += matrix1;
    matrix5 *= 2;
    EXPECT_EQ(matrix1, matrix5);
}

TEST(ClassMatrix, can_multiply) {
    Matrix<double> matrix1({ {1,2,3} ,{4,5,6} });
    Matrix<double> matrix2({ {7,8} ,{9,10} ,{11,12} });
    EXPECT_EQ(matrix1.getN(), matrix2.getM());
    Matrix<double> matrix3({ {58,64} ,{139,154} });
    EXPECT_TRUE(matrix1 * matrix2 == matrix3);

    Matrix<double> matrix4({ {1,2,3} ,{4,5,6} });
    Matrix<double> matrix5({ {7,8,9} ,{1,2,3} });
    EXPECT_NE(matrix4.getN(), matrix5.getM());
    EXPECT_THROW(matrix4 * matrix5, std::logic_error);
}

TEST(ClassMatrix, can_throw_when_wrong_dimensions) {
    Matrix<double> matrix1({ {1,2,3} ,{1,2,3} ,{1,2,3} });
    Matrix<double> matrix2({ {4,5,6},{4,5,6} });
    EXPECT_THROW(matrix1 + matrix2, std::logic_error);
    EXPECT_THROW(matrix1 - matrix2, std::logic_error);
    EXPECT_THROW(matrix1 * matrix2, std::logic_error);
    EXPECT_THROW(matrix1 += matrix2, std::logic_error);
    EXPECT_THROW(matrix1 -= matrix2, std::logic_error);
}

TEST(ClassMatrix, can_do_transposition) {
    Matrix<double> matrix1({ {1,2,3} ,{4,5,6} ,{7,8,9} });
    Matrix<double> matrix2({ {1,4,7} ,{2,5,8} ,{3,6,9} });
    EXPECT_NE(matrix1, matrix2);
    matrix1 = matrix1.Transposition();
    EXPECT_EQ(matrix1, matrix2);
}

TEST(ClassMatrix, can_cout) {
    Matrix<double> matrix({ {1,2,3} ,{4,5,6},{7,8,9} });
    std::stringstream ss;
    ss << matrix;
    EXPECT_EQ(ss.str(), "{ 1, 2, 3 }\n{ 4, 5, 6 }\n{ 7, 8, 9 }\n");
}
