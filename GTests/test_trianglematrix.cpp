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

TEST(ClassTriangleMatrix, can_do_right_scalar_multiplication) {
    TriangleMatrix<double> tm({
        { 1.0, -2.5 },
        { 0.0, 10.5 }
        });
    TriangleMatrix<double> tm_res = tm * -3;

    EXPECT_EQ(tm_res.getN(), 2);
    EXPECT_DOUBLE_EQ(tm_res[1][1], -3.0);
    EXPECT_DOUBLE_EQ(tm_res[1][2], 7.5);
    EXPECT_DOUBLE_EQ(tm_res[2][1], 0.0);
    EXPECT_DOUBLE_EQ(tm_res[2][2], -31.5);
    size_t size = 2;
    for (size_t i = 1; i <= size; ++i) {
        EXPECT_EQ(tm_res[i].get_size(), size - i + 1);
    }

    EXPECT_EQ(tm.getN(), 2);
    EXPECT_DOUBLE_EQ(tm[1][1], 1.0);
    EXPECT_DOUBLE_EQ(tm[1][2], -2.5);
    EXPECT_DOUBLE_EQ(tm[2][1], 0.0);
    EXPECT_DOUBLE_EQ(tm[2][2], 10.5);
    for (size_t i = 1; i <= size; ++i) {
        EXPECT_EQ(tm[i].get_size(), size - i + 1);
    }
}

TEST(ClassTriangleMatrix, can_do_right_scalar_multiplication_by_zero) {
    TriangleMatrix<double> tm({
        { 5.5, -10.0, 3.14 },
        { 0.0,  2.0,  1.0 },
        { 0.0,  0.0,  7.0 }
        });
    TriangleMatrix<double> tm_res = tm * 0;

    EXPECT_EQ(tm.getN(), 3);
    EXPECT_DOUBLE_EQ(tm[1][1], 5.5);
    EXPECT_DOUBLE_EQ(tm[1][2], -10.0);
    EXPECT_DOUBLE_EQ(tm[1][3], 3.14);
    EXPECT_DOUBLE_EQ(tm[2][1], 0.0);
    EXPECT_DOUBLE_EQ(tm[2][2], 2.0);
    EXPECT_DOUBLE_EQ(tm[2][3], 1.0);
    EXPECT_DOUBLE_EQ(tm[3][1], 0.0);
    EXPECT_DOUBLE_EQ(tm[3][2], 0.0);
    EXPECT_DOUBLE_EQ(tm[3][3], 7.0);
    size_t size = 3;
    for (size_t i = 1; i <= size; ++i) {
        EXPECT_EQ(tm[i].get_size(), size - i + 1);
    }

    EXPECT_EQ(tm_res.getN(), 3);
    EXPECT_DOUBLE_EQ(tm_res[1][1], 0.0);
    EXPECT_DOUBLE_EQ(tm_res[1][2], 0.0);
    EXPECT_DOUBLE_EQ(tm_res[1][3], 0.0);
    EXPECT_DOUBLE_EQ(tm_res[2][1], 0.0);
    EXPECT_DOUBLE_EQ(tm_res[2][2], 0.0);
    EXPECT_DOUBLE_EQ(tm_res[2][3], 0.0);
    EXPECT_DOUBLE_EQ(tm_res[3][1], 0.0);
    EXPECT_DOUBLE_EQ(tm_res[3][2], 0.0);
    EXPECT_DOUBLE_EQ(tm_res[3][3], 0.0);
    for (size_t i = 1; i <= size; ++i) {
        EXPECT_EQ(tm_res[i].get_size(), size - i + 1);
    }
}

TEST(ClassTriangleMatrix, can_do_right_scalar_multiplication_to_empty) {
    TriangleMatrix<double> tm;

    TriangleMatrix<double> tm_res = tm * 5;
    EXPECT_EQ(tm.getN(), 0);
    EXPECT_EQ(tm_res.getN(), 0);
}


TEST(ClassTriangleMatrix, can_do_left_scalar_multiplication) {
    TriangleMatrix<double> tm({
        { 1.0, -2.5 },
        { 0.0, 10.5 }
        });
    TriangleMatrix<double> tm_res = -3 * tm;

    EXPECT_EQ(tm_res.getN(), 2);
    EXPECT_DOUBLE_EQ(tm_res[1][1], -3.0);
    EXPECT_DOUBLE_EQ(tm_res[1][2], 7.5);
    EXPECT_DOUBLE_EQ(tm_res[2][1], 0.0);
    EXPECT_DOUBLE_EQ(tm_res[2][2], -31.5);
    size_t size = 2;
    for (size_t i = 1; i <= size; ++i) {
        EXPECT_EQ(tm_res[i].get_size(), size - i + 1);
    }

    EXPECT_EQ(tm.getN(), 2);
    EXPECT_DOUBLE_EQ(tm[1][1], 1.0);
    EXPECT_DOUBLE_EQ(tm[1][2], -2.5);
    EXPECT_DOUBLE_EQ(tm[2][1], 0.0);
    EXPECT_DOUBLE_EQ(tm[2][2], 10.5);
    for (size_t i = 1; i <= size; ++i) {
        EXPECT_EQ(tm[i].get_size(), size - i + 1);
    }
}

TEST(ClassTriangleMatrix, can_do_left_scalar_multiplication_by_zero) {
    TriangleMatrix<double> tm({
        { 5.5, -10.0, 3.14 },
        { 0.0,  2.0,  1.0 },
        { 0.0,  0.0,  7.0 }
        });
    TriangleMatrix<double> tm_res = 0 * tm;

    EXPECT_EQ(tm.getN(), 3);
    EXPECT_DOUBLE_EQ(tm[1][1], 5.5);
    EXPECT_DOUBLE_EQ(tm[1][2], -10.0);
    EXPECT_DOUBLE_EQ(tm[1][3], 3.14);
    EXPECT_DOUBLE_EQ(tm[2][1], 0.0);
    EXPECT_DOUBLE_EQ(tm[2][2], 2.0);
    EXPECT_DOUBLE_EQ(tm[2][3], 1.0);
    EXPECT_DOUBLE_EQ(tm[3][1], 0.0);
    EXPECT_DOUBLE_EQ(tm[3][2], 0.0);
    EXPECT_DOUBLE_EQ(tm[3][3], 7.0);
    size_t size = 3;
    for (size_t i = 1; i <= size; ++i) {
        EXPECT_EQ(tm[i].get_size(), size - i + 1);
    }

    EXPECT_EQ(tm_res.getN(), 3);
    EXPECT_DOUBLE_EQ(tm_res[1][1], 0.0);
    EXPECT_DOUBLE_EQ(tm_res[1][2], 0.0);
    EXPECT_DOUBLE_EQ(tm_res[1][3], 0.0);
    EXPECT_DOUBLE_EQ(tm_res[2][1], 0.0);
    EXPECT_DOUBLE_EQ(tm_res[2][2], 0.0);
    EXPECT_DOUBLE_EQ(tm_res[2][3], 0.0);
    EXPECT_DOUBLE_EQ(tm_res[3][1], 0.0);
    EXPECT_DOUBLE_EQ(tm_res[3][2], 0.0);
    EXPECT_DOUBLE_EQ(tm_res[3][3], 0.0);
    for (size_t i = 1; i <= size; ++i) {
        EXPECT_EQ(tm_res[i].get_size(), size - i + 1);
    }
}

TEST(ClassTriangleMatrix, can_do_left_scalar_multiplication_to_empty) {
    TriangleMatrix<double> tm;

    TriangleMatrix<double> tm_res = 5 * tm;
    EXPECT_EQ(tm.getN(), 0);
    EXPECT_EQ(tm_res.getN(), 0);
}

TEST(ClassTriangleMatrix, can_do_scalar_multiplication_assignment) {
    TriangleMatrix<double> tm({
        { 2.0, -4.0 },
        { 0.0,  3.0 }
        });
    tm *= 3.0;

    EXPECT_EQ(tm.getN(), 2);
    EXPECT_DOUBLE_EQ(tm[1][1], 6.0);
    EXPECT_DOUBLE_EQ(tm[1][2], -12.0);
    EXPECT_DOUBLE_EQ(tm[2][1], 0.0);
    EXPECT_DOUBLE_EQ(tm[2][2], 9.0);
    size_t size = 2;
    for (size_t i = 1; i <= size; ++i) {
        EXPECT_EQ(tm[i].get_size(), size - i + 1);
    }
}

TEST(ClassTriangleMatrix, can_do_matrix_multiplication_assignment) {
    TriangleMatrix<double> A({
        { 1.0, 2.0 },
        { 0.0, 3.0 }
        });
    TriangleMatrix<double> B({
        { 4.0, 5.0 },
        { 0.0, 2.0 }
        });
    A *= B;

    EXPECT_EQ(A.getN(), 2);
    EXPECT_DOUBLE_EQ(A[1][1], 4.0);
    EXPECT_DOUBLE_EQ(A[1][2], 9.0);
    EXPECT_DOUBLE_EQ(A[2][1], 0.0);
    EXPECT_DOUBLE_EQ(A[2][2], 6.0);
    size_t size = 2;
    for (size_t i = 1; i <= size; ++i) {
        EXPECT_EQ(A[i].get_size(), size - i + 1);
    }

    EXPECT_EQ(B.getN(), 2);
    EXPECT_DOUBLE_EQ(B[1][1], 4.0);
    EXPECT_DOUBLE_EQ(B[1][2], 5.0);
    EXPECT_DOUBLE_EQ(B[2][1], 0.0);
    EXPECT_DOUBLE_EQ(B[2][2], 2.0);
    for (size_t i = 1; i <= size; ++i) {
        EXPECT_EQ(B[i].get_size(), size - i + 1);
    }
}

TEST(ClassTriangleMatrix, can_do_multiplication_assignment_to_empty) {
    TriangleMatrix<double> tm_empty1;
    TriangleMatrix<double> tm_empty2;
    tm_empty1 *= 5.0;
    tm_empty1 *= tm_empty2;

    EXPECT_EQ(tm_empty1.getN(), 0);
    EXPECT_EQ(tm_empty2.getN(), 0);
}

TEST(ClassTriangleMatrix, can_do_right_scalar_division) {
    TriangleMatrix<double> tm({
        { 4.0, -8.0 },
        { 0.0, 12.0 }
        });
    TriangleMatrix<double> tm_res = tm / 4.0;

    EXPECT_EQ(tm_res.getN(), 2);
    EXPECT_DOUBLE_EQ(tm_res[1][1], 1.0);
    EXPECT_DOUBLE_EQ(tm_res[1][2], -2.0);
    EXPECT_DOUBLE_EQ(tm_res[2][1], 0.0);
    EXPECT_DOUBLE_EQ(tm_res[2][2], 3.0);
    size_t size = 2;
    for (size_t i = 1; i <= size; ++i) {
        EXPECT_EQ(tm_res[i].get_size(), size - i + 1);
    }
}

TEST(ClassTriangleMatrix, can_do_scalar_division_assignment) {
    TriangleMatrix<double> tm({
        { 9.0, -18.0 },
        { 0.0,  27.0 }
        });
    tm /= 9.0;

    EXPECT_EQ(tm.getN(), 2);
    EXPECT_DOUBLE_EQ(tm[1][1], 1.0);
    EXPECT_DOUBLE_EQ(tm[1][2], -2.0);
    EXPECT_DOUBLE_EQ(tm[2][1], 0.0);
    EXPECT_DOUBLE_EQ(tm[2][2], 3.0);
    size_t size = 2;
    for (size_t i = 1; i <= size; ++i) {
        EXPECT_EQ(tm[i].get_size(), size - i + 1);
    }
}

TEST(ClassTriangleMatrix, division_throws_when_zero) {
    TriangleMatrix<double> tm({ { 1.0, 2.0 }, { 0.0, 3.0 } });

    EXPECT_THROW(tm / 0.0, std::invalid_argument);
    EXPECT_THROW(tm /= 0.0, std::invalid_argument);
}

TEST(ClassTriangleMatrix, can_divide_empty) {
    TriangleMatrix<double> tm;
    TriangleMatrix<double> tm_res = tm / 2.0;
    tm /= 2.0;

    EXPECT_EQ(tm.getN(), 0);
    EXPECT_EQ(tm_res.getN(), 0);
}

TEST(ClassTriangleMatrix, can_add_and_subtract_matrices) {
    TriangleMatrix<double> A({
        { 1.0, -2.5 },
        { 0.0, 10.5 }
        });
    TriangleMatrix<double> B({
        { 2.0,  1.5 },
        { 0.0,  5.0 }
        });
    TriangleMatrix<double> expected_add({
        { 3.0, -1.0 },
        { 0.0, 15.5 }
        });
    TriangleMatrix<double> res_add = A + B;

    EXPECT_EQ(res_add, expected_add);
    EXPECT_DOUBLE_EQ(res_add[2][1], 0.0);

    TriangleMatrix<double> expected_sub({
        {-1.0, -4.0 },
        { 0.0,  5.5 }
        });
    TriangleMatrix<double> res_sub = A - B;

    EXPECT_EQ(res_sub, expected_sub);
    EXPECT_DOUBLE_EQ(res_sub[2][1], 0.0);

    size_t size = 2;
    for (size_t i = 1; i <= size; ++i) {
        EXPECT_EQ(res_add[i].get_size(), size - i + 1);
        EXPECT_EQ(res_sub[i].get_size(), size - i + 1);
    }
}

TEST(ClassTriangleMatrix, can_do_addition_assignment_and_subtraction_assignment) {
    TriangleMatrix<double> A({
        { 5.0,  2.0 },
        { 0.0, -3.0 }
        });
    TriangleMatrix<double> B({
        { 1.0,  3.0 },
        { 0.0,  4.0 }
        });
    A += B;
    TriangleMatrix<double> expected_inplace_add({
        { 6.0,  5.0 },
        { 0.0,  1.0 }
        });

    EXPECT_EQ(A, expected_inplace_add);

    A -= B;
    TriangleMatrix<double> expected_inplace_sub({
        { 5.0,  2.0 },
        { 0.0, -3.0 }
        });

    EXPECT_EQ(A, expected_inplace_sub);

    size_t size = 2;
    for (size_t i = 1; i <= size; ++i) {
        EXPECT_EQ(A[i].get_size(), size - i + 1);
    }
}

TEST(ClassTriangleMatrix, add_and_subtract_throws_when_wrong_dimensions) {
    TriangleMatrix<double> A(2);
    TriangleMatrix<double> B(3);

    EXPECT_THROW(A + B, std::logic_error);
    EXPECT_THROW(A - B, std::logic_error);
    EXPECT_THROW(A += B, std::logic_error);
    EXPECT_THROW(A -= B, std::logic_error);
}

TEST(ClassTriangleMatrix, can_add_and_subtract_empty) {
    TriangleMatrix<double> A;
    TriangleMatrix<double> B;
    TriangleMatrix<double> res_add = A + B;
    TriangleMatrix<double> res_sub = A - B;
    A += B;
    A -= B;

    EXPECT_EQ(A.getN(), 0);
    EXPECT_EQ(res_add.getN(), 0);
    EXPECT_EQ(res_sub.getN(), 0);
}
