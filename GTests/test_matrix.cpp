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

TEST(ClassMatrix, can_do_add_and_sub_assignment_operations) {
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

TEST(ClassMatrix, can_multiply_matrices_good) {
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

TEST(ClassMatrix, can_throw_when_operate_with_wrong_dimensions) {
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
TEST(ClassMatrix, can_do_right_scalar_multiplication) {
    Matrix<double> m({
        { 1.0, -2.5 },
        { 0.0, 10.5 }
        });
    Matrix<double> m_res = m * -3;

    EXPECT_EQ(m_res.getN(), 2);
    EXPECT_EQ(m_res.getM(), 2);
    EXPECT_DOUBLE_EQ(m_res[1][1], -3.0);
    EXPECT_DOUBLE_EQ(m_res[1][2], 7.5);
    EXPECT_DOUBLE_EQ(m_res[2][1], 0.0);
    EXPECT_DOUBLE_EQ(m_res[2][2], -31.5);

    EXPECT_EQ(m.getN(), 2);
    EXPECT_EQ(m.getM(), 2);
    EXPECT_DOUBLE_EQ(m[1][1], 1.0);
    EXPECT_DOUBLE_EQ(m[1][2], -2.5);
    EXPECT_DOUBLE_EQ(m[2][1], 0.0);
    EXPECT_DOUBLE_EQ(m[2][2], 10.5);
}

TEST(ClassMatrix, can_do_right_scalar_multiplication_by_zero) {
    Matrix<double> m({
        { 5.5, -10.0 },
        { 3.14, 2.0 }
        });
    Matrix<double> m_res = m * 0;

    EXPECT_EQ(m.getN(), 2);
    EXPECT_EQ(m.getM(), 2);
    EXPECT_DOUBLE_EQ(m[1][1], 5.5);
    EXPECT_DOUBLE_EQ(m[1][2], -10.0);
    EXPECT_DOUBLE_EQ(m[2][1], 3.14);
    EXPECT_DOUBLE_EQ(m[2][2], 2.0);

    EXPECT_EQ(m_res.getN(), 2);
    EXPECT_EQ(m_res.getM(), 2);
    EXPECT_DOUBLE_EQ(m_res[1][1], 0.0);
    EXPECT_DOUBLE_EQ(m_res[1][2], 0.0);
    EXPECT_DOUBLE_EQ(m_res[2][1], 0.0);
    EXPECT_DOUBLE_EQ(m_res[2][2], 0.0);
}

TEST(ClassMatrix, can_do_right_scalar_multiplication_to_empty) {
    Matrix<double> m;

    Matrix<double> m_res = m * 5;
    EXPECT_EQ(m.getN(), 0);
    EXPECT_EQ(m.getM(), 0);
    EXPECT_EQ(m_res.getN(), 0);
    EXPECT_EQ(m_res.getM(), 0);
}

TEST(ClassMatrix, can_do_left_scalar_multiplication) {
    Matrix<double> m({
        { 1.0, -2.5 },
        { 0.0, 10.5 }
        });
    Matrix<double> m_res = -3 * m;

    EXPECT_EQ(m_res.getN(), 2);
    EXPECT_EQ(m_res.getM(), 2);
    EXPECT_DOUBLE_EQ(m_res[1][1], -3.0);
    EXPECT_DOUBLE_EQ(m_res[1][2], 7.5);
    EXPECT_DOUBLE_EQ(m_res[2][1], 0.0);
    EXPECT_DOUBLE_EQ(m_res[2][2], -31.5);

    EXPECT_EQ(m.getN(), 2);
    EXPECT_EQ(m.getM(), 2);
    EXPECT_DOUBLE_EQ(m[1][1], 1.0);
    EXPECT_DOUBLE_EQ(m[1][2], -2.5);
    EXPECT_DOUBLE_EQ(m[2][1], 0.0);
    EXPECT_DOUBLE_EQ(m[2][2], 10.5);
}

TEST(ClassMatrix, can_do_left_scalar_multiplication_by_zero) {
    Matrix<double> m({
        { 5.5, -10.0 },
        { 3.14, 2.0 }
        });
    Matrix<double> m_res = 0 * m;

    EXPECT_EQ(m.getN(), 2);
    EXPECT_EQ(m.getM(), 2);
    EXPECT_DOUBLE_EQ(m[1][1], 5.5);
    EXPECT_DOUBLE_EQ(m[1][2], -10.0);
    EXPECT_DOUBLE_EQ(m[2][1], 3.14);
    EXPECT_DOUBLE_EQ(m[2][2], 2.0);

    EXPECT_EQ(m_res.getN(), 2);
    EXPECT_EQ(m_res.getM(), 2);
    EXPECT_DOUBLE_EQ(m_res[1][1], 0.0);
    EXPECT_DOUBLE_EQ(m_res[1][2], 0.0);
    EXPECT_DOUBLE_EQ(m_res[2][1], 0.0);
    EXPECT_DOUBLE_EQ(m_res[2][2], 0.0);
}

TEST(ClassMatrix, can_do_left_scalar_multiplication_to_empty) {
    Matrix<double> m;
    Matrix<double> m_res = 5 * m;

    EXPECT_EQ(m.getN(), 0);
    EXPECT_EQ(m.getM(), 0);
    EXPECT_EQ(m_res.getN(), 0);
    EXPECT_EQ(m_res.getM(), 0);
}

TEST(ClassMatrix, can_do_scalar_multiplication_assignment) {
    Matrix<double> m({
        { 1.0, -2.5 },
        { 3.0,  4.0 }
        });
    Matrix<double> expected({
        { 2.0, -5.0 },
        { 6.0,  8.0 }
        });
    m *= 2.0;

    EXPECT_EQ(m, expected);
}

TEST(ClassMatrix, can_do_matrix_multiplication_assignment) {
    Matrix<double> A({
        { 1.0, 2.0 },
        { 3.0, 4.0 }
        });
    Matrix<double> B({
        { 2.0, 0.0 },
        { 1.0, 3.0 }
        });
    Matrix<double> expected({
        {  4.0,  6.0 },
        { 10.0, 12.0 }
        });
    A *= B;

    EXPECT_EQ(A, expected);
    EXPECT_EQ(B.getN(), 2);
    EXPECT_EQ(B.getM(), 2);
    EXPECT_DOUBLE_EQ(B[1][1], 2);
    EXPECT_DOUBLE_EQ(B[1][2], 0);
    EXPECT_DOUBLE_EQ(B[2][1], 1);
    EXPECT_DOUBLE_EQ(B[2][2], 3);
}

TEST(ClassMatrix, can_do_right_scalar_division) {
    Matrix<double> m({
        { 3.0, -6.0 },
        { 0.0, 12.0 }
        });
    Matrix<double> m_res = m / 3.0;

    EXPECT_EQ(m_res.getN(), 2);
    EXPECT_EQ(m_res.getM(), 2);
    EXPECT_DOUBLE_EQ(m_res[1][1], 1.0);
    EXPECT_DOUBLE_EQ(m_res[1][2], -2.0);
    EXPECT_DOUBLE_EQ(m_res[2][1], 0.0);
    EXPECT_DOUBLE_EQ(m_res[2][2], 4.0);

    EXPECT_EQ(m.getN(), 2);
    EXPECT_DOUBLE_EQ(m[1][1], 3.0);
}

TEST(ClassMatrix, can_do_scalar_division_assignment) {
    Matrix<double> m({
        { 5.0, -10.0 },
        { 15.0, 20.0 }
        });
    m /= 5.0;

    EXPECT_EQ(m.getN(), 2);
    EXPECT_EQ(m.getM(), 2);
    EXPECT_DOUBLE_EQ(m[1][1], 1.0);
    EXPECT_DOUBLE_EQ(m[1][2], -2.0);
    EXPECT_DOUBLE_EQ(m[2][1], 3.0);
    EXPECT_DOUBLE_EQ(m[2][2], 4.0);
}

TEST(ClassMatrix, division_throws_when_zero) {
    Matrix<double> m({ { 1.0, 2.0 } });

    EXPECT_THROW(m / 0.0, std::invalid_argument);
    EXPECT_THROW(m /= 0.0, std::invalid_argument);
}

TEST(ClassMatrix, can_divide_empty) {
    Matrix<double> m;
    Matrix<double> m_res = m / 2.0;
    m /= 2.0;

    EXPECT_EQ(m.getN(), 0);
    EXPECT_EQ(m_res.getN(), 0);
}
