#include "pch.h"
#include "trianglematrix.h"

TEST(ClassTriangleMatrix, can_create_with_default_constructor) {
    TriangleMatrix<double> matrix;
    EXPECT_EQ(matrix.getN(), 0);
}

TEST(ClassTriangleMatrix, can_create_with_constructor_by_size) {
    size_t size = 4;
    TriangleMatrix<double> matrix(size);
    EXPECT_EQ(matrix.getN(), size);
    for (size_t i = 1; i <= size; ++i) {
        EXPECT_EQ(matrix[i].get_size(), size - i + 1);
    }
}

TEST(ClassTriangleMatrix, can_create_with_constructor_by_init_list) {
    TriangleMatrix<double> matrix({
        {3, 4, 5},
        {0, 1, 2},
        {0, 0, 9}
        });
    size_t size = 3;
    for (size_t i = 1; i <= size; ++i) {
        EXPECT_EQ(matrix[i].get_size(), size - i + 1);
    }
    EXPECT_EQ(matrix.getN(), 3);
    EXPECT_EQ(matrix[1][1], 3);
    EXPECT_EQ(matrix[1][2], 4);
    EXPECT_EQ(matrix[1][3], 5);
    EXPECT_EQ(matrix[2][1], 0);
    EXPECT_EQ(matrix[2][2], 1);
    EXPECT_EQ(matrix[2][3], 2);
    EXPECT_EQ(matrix[3][1], 0);
    EXPECT_EQ(matrix[3][2], 0);
    EXPECT_EQ(matrix[3][3], 9);
}

TEST(ClassTriangleMatrix, throw_when_init_list_has_elements_below_diagonal) {
    EXPECT_THROW(TriangleMatrix<double> matrix({
        {1, 2, 3},
        {7, 5, 6},
        {0, 0, 9}
        }), std::invalid_argument);
}

TEST(ClassTriangleMatrix, can_create_with_copy_constructor_and_compare) {
    TriangleMatrix<double> matrix({
        {3, 4, 5},
        {0, 1, 2},
        {0, 0, 9}
        });
    TriangleMatrix<double> copy(matrix);
    size_t size = 3;
    for (size_t i = 1; i <= size; ++i) {
        EXPECT_EQ(matrix[i].get_size(), size - i + 1);
        EXPECT_EQ(copy[i].get_size(), size - i + 1);
    }
    EXPECT_TRUE(matrix == copy);
    EXPECT_FALSE(matrix != copy);
}

TEST(ClassTriangleMatrix, can_create_from_ordinary_matrix) {
    Matrix<double> ord_matrix({
        {5, 6, 7},
        {0, 8, 9},
        {0, 0, 1}
        });
    TriangleMatrix<double> tri_matrix(ord_matrix);
    size_t size = 3;
    for (size_t i = 1; i <= size; ++i) {
        EXPECT_EQ(tri_matrix[i].get_size(), size - i + 1);
    }
    EXPECT_EQ(tri_matrix.getN(), 3);
    EXPECT_EQ(tri_matrix[1][1], 5);
    EXPECT_EQ(tri_matrix[2][2], 8);
    EXPECT_EQ(tri_matrix[3][3], 1);
    EXPECT_EQ(tri_matrix[3][1], 0);
}

TEST(ClassTriangleMatrix, can_calculate_determinant) {
    TriangleMatrix<double> matrix({
        {2, 4, 6},
        {0, 5, 1},
        {0, 0, 3}
        });
    EXPECT_DOUBLE_EQ(matrix.getDeterminant(), 30);
    TriangleMatrix<double> empty_matrix;
    EXPECT_DOUBLE_EQ(empty_matrix.getDeterminant(), 0);
}

TEST(ClassTriangleMatrix, can_multiply_triangle_matrices) {
    TriangleMatrix<double> A({
        {1, 2, 3},
        {0, 4, 5},
        {0, 0, 6}
        });
    TriangleMatrix<double> B({
        {7, 8, 9},
        {0, 1, 2},
        {0, 0, 3}
        });
    TriangleMatrix<double> expected({
        {7, 10, 22},
        {0,  4, 23},
        {0,  0, 18}
        });
    TriangleMatrix<double> result = A * B;
    size_t size = 3;
    for (size_t i = 1; i <= size; ++i) {
        EXPECT_EQ(result[i].get_size(), size - i + 1);
    }
    EXPECT_EQ(result, expected);
}

TEST(ClassTriangleMatrix, throws_when_multiply_with_wrong_dimensions) {
    TriangleMatrix<double> A(3);
    TriangleMatrix<double> B(4);
    EXPECT_THROW(A * B, std::logic_error);
}

TEST(ClassTriangleMatrix, can_cout) {
    TriangleMatrix<double> matrix({
        {1, 2, 3},
        {0, 4, 5},
        {0, 0, 6}
        });
    std::stringstream ss;
    ss << matrix;
    std::string expected_output = "[ 1 2 3 ]\n[ 0 4 5 ]\n[ 0 0 6 ]\n";
    EXPECT_EQ(ss.str(), expected_output);
}
