#include "pch.h"
#include "mathvector.h"

TEST(ClassMathVector, can_create_with_init_constructor) {
    double array[5] = { 0, 0.1, 0.2, 233, 5.89 };
    MathVector<double> mv1(array, 5);

    EXPECT_EQ(mv1.get_size(), 5);
    EXPECT_DOUBLE_EQ(mv1[1], 0);
    EXPECT_DOUBLE_EQ(mv1[2], 0.1);
    EXPECT_DOUBLE_EQ(mv1[3], 0.2);
    EXPECT_DOUBLE_EQ(mv1[4], 233);
    EXPECT_DOUBLE_EQ(mv1[5], 5.89);
}

TEST(ClassMathVector, can_create_with_list_constructor) {
    MathVector<double> mv1({ 0, 0.1, 0.2, 233, 5.88, 67 });

    EXPECT_EQ(mv1.get_size(), 6);
    EXPECT_DOUBLE_EQ(mv1[1], 0);
    EXPECT_DOUBLE_EQ(mv1[2], 0.1);
    EXPECT_DOUBLE_EQ(mv1[3], 0.2);
    EXPECT_DOUBLE_EQ(mv1[4], 233);
    EXPECT_DOUBLE_EQ(mv1[5], 5.88);
    EXPECT_DOUBLE_EQ(mv1[6], 67);
}

TEST(ClassMathVector, can_create_with_copy_constructor) {
    MathVector<double> mv1({ 0, 0.1, 0.2, 233, 5.88, 67 });
    MathVector<double> mv2(mv1);
    mv2[1] = 2007.02;

    EXPECT_EQ(mv1.get_size(), 6);
    EXPECT_DOUBLE_EQ(mv1[1], 0);
    EXPECT_DOUBLE_EQ(mv1[2], 0.1);
    EXPECT_DOUBLE_EQ(mv1[3], 0.2);
    EXPECT_DOUBLE_EQ(mv1[4], 233);
    EXPECT_DOUBLE_EQ(mv1[5], 5.88);
    EXPECT_DOUBLE_EQ(mv1[6], 67);

    EXPECT_EQ(mv2.get_size(), 6);
    EXPECT_DOUBLE_EQ(mv2[1], 2007.02);
    EXPECT_DOUBLE_EQ(mv2[2], 0.1);
    EXPECT_DOUBLE_EQ(mv2[3], 0.2);
    EXPECT_DOUBLE_EQ(mv2[4], 233);
    EXPECT_DOUBLE_EQ(mv2[5], 5.88);
    EXPECT_DOUBLE_EQ(mv2[6], 67);
}

TEST(ClassMathVector, can_create_with_constructor_from_base_class) {
    Vector<double> v1({ 0, 0.1, 0.2, 233, 5.88, 69 });
    MathVector<double> mv1(v1);

    EXPECT_EQ(mv1.get_size(), 6);
    EXPECT_DOUBLE_EQ(mv1[1], 0);
    EXPECT_DOUBLE_EQ(mv1[2], 0.1);
    EXPECT_DOUBLE_EQ(mv1[3], 0.2);
    EXPECT_DOUBLE_EQ(mv1[4], 233);
    EXPECT_DOUBLE_EQ(mv1[5], 5.88);
    EXPECT_DOUBLE_EQ(mv1[6], 69);
}

TEST(ClassMathVector, can_do_assigment_with_same_size) {
    MathVector<double> mv1({ 0, 0.1, 0.2, 233, 5.88, 67 });
    MathVector<double> mv2({ 0, 1, 2, 3, 2, 5 });
    mv2 = mv1;
    mv2[1] = 2007.02;

    EXPECT_EQ(mv1.get_size(), 6);
    EXPECT_DOUBLE_EQ(mv1[1], 0);
    EXPECT_DOUBLE_EQ(mv1[2], 0.1);
    EXPECT_DOUBLE_EQ(mv1[3], 0.2);
    EXPECT_DOUBLE_EQ(mv1[4], 233);
    EXPECT_DOUBLE_EQ(mv1[5], 5.88);
    EXPECT_DOUBLE_EQ(mv1[6], 67);

    EXPECT_EQ(mv2.get_size(), 6);
    EXPECT_DOUBLE_EQ(mv2[1], 2007.02);
    EXPECT_DOUBLE_EQ(mv2[2], 0.1);
    EXPECT_DOUBLE_EQ(mv2[3], 0.2);
    EXPECT_DOUBLE_EQ(mv2[4], 233);
    EXPECT_DOUBLE_EQ(mv2[5], 5.88);
    EXPECT_DOUBLE_EQ(mv2[6], 67);
}

TEST(ClassMathVector, can_do_assigment_with_diff_size) {
    MathVector<double> mv1({ 0, 0.1, 0.2, 233, 5.88, 67 });
    MathVector<double> mv2({ 0 });
    mv2 = mv1;
    mv2[1] = 2007.02;

    EXPECT_EQ(mv1.get_size(), 6);
    EXPECT_DOUBLE_EQ(mv1[1], 0);
    EXPECT_DOUBLE_EQ(mv1[2], 0.1);
    EXPECT_DOUBLE_EQ(mv1[3], 0.2);
    EXPECT_DOUBLE_EQ(mv1[4], 233);
    EXPECT_DOUBLE_EQ(mv1[5], 5.88);
    EXPECT_DOUBLE_EQ(mv1[6], 67);

    EXPECT_EQ(mv2.get_size(), 6);
    EXPECT_DOUBLE_EQ(mv2[1], 2007.02);
    EXPECT_DOUBLE_EQ(mv2[2], 0.1);
    EXPECT_DOUBLE_EQ(mv2[3], 0.2);
    EXPECT_DOUBLE_EQ(mv2[4], 233);
    EXPECT_DOUBLE_EQ(mv2[5], 5.88);
    EXPECT_DOUBLE_EQ(mv2[6], 67);
}

TEST(ClassMathVector, can_do_good_add_assigment) {
    MathVector<double> mv1({ 0, 0.1, 0.2, 233, 5.88, 67 });
    MathVector<double> mv2({ 0.1, 0.1, 1, -33, -0.4, -12 });
    MathVector<double> mv3({ 0.1, 0.1, 0.11, 0, -0.48, -3 });
    mv1 += mv2 += mv3;

    EXPECT_EQ(mv1.get_size(), 6);
    EXPECT_DOUBLE_EQ(mv1[1], 0.2);
    EXPECT_DOUBLE_EQ(mv1[2], 0.3);
    EXPECT_DOUBLE_EQ(mv1[3], 1.31);
    EXPECT_DOUBLE_EQ(mv1[4], 200);
    EXPECT_DOUBLE_EQ(mv1[5], 5);
    EXPECT_DOUBLE_EQ(mv1[6], 52);

    EXPECT_EQ(mv2.get_size(), 6);
    EXPECT_DOUBLE_EQ(mv2[1], 0.2);
    EXPECT_DOUBLE_EQ(mv2[2], 0.2);
    EXPECT_DOUBLE_EQ(mv2[3], 1.11);
    EXPECT_DOUBLE_EQ(mv2[4], -33);
    EXPECT_DOUBLE_EQ(mv2[5], -0.88);
    EXPECT_DOUBLE_EQ(mv2[6], -15);

    EXPECT_EQ(mv3.get_size(), 6);
    EXPECT_DOUBLE_EQ(mv3[1], 0.1);
    EXPECT_DOUBLE_EQ(mv3[2], 0.1);
    EXPECT_DOUBLE_EQ(mv3[3], 0.11);
    EXPECT_DOUBLE_EQ(mv3[4], 0);
    EXPECT_DOUBLE_EQ(mv3[5], -0.48);
    EXPECT_DOUBLE_EQ(mv3[6], -3);
}

TEST(ClassMathVector, can_throw_bad_add_assigment) {
    MathVector<double> mv1({ 0, 0.1, 0.2, 233, 5.88, 67 });
    MathVector<double> mv2({ 0.1, 0.1, 1, -33, -0.4 });

    EXPECT_THROW(mv1 += mv2, std::logic_error);

    EXPECT_EQ(mv1.get_size(), 6);
    EXPECT_DOUBLE_EQ(mv1[1], 0);
    EXPECT_DOUBLE_EQ(mv1[2], 0.1);
    EXPECT_DOUBLE_EQ(mv1[3], 0.2);
    EXPECT_DOUBLE_EQ(mv1[4], 233);
    EXPECT_DOUBLE_EQ(mv1[5], 5.88);
    EXPECT_DOUBLE_EQ(mv1[6], 67);

    EXPECT_EQ(mv2.get_size(), 5);
    EXPECT_DOUBLE_EQ(mv2[1], 0.1);
    EXPECT_DOUBLE_EQ(mv2[2], 0.1);
    EXPECT_DOUBLE_EQ(mv2[3], 1);
    EXPECT_DOUBLE_EQ(mv2[4], -33);
    EXPECT_DOUBLE_EQ(mv2[5], -0.4);
}

TEST(ClassMathVector, can_do_good_sub_assigment) {
    MathVector<double> mv1({ 0, 0.1, 0.2, 233, 5.48, 67 });
    MathVector<double> mv2({ -0.1, -0.1, -1, 33, 1, 18 });
    MathVector<double> mv3({ -0.1, -0.1, -0.11, 0, 0.52, 3 });
    mv1 -= mv2 -= mv3;

    EXPECT_EQ(mv1.get_size(), 6);
    EXPECT_DOUBLE_EQ(mv1[1], 0);
    EXPECT_DOUBLE_EQ(mv1[2], 0.1);
    EXPECT_DOUBLE_EQ(mv1[3], 1.09);
    EXPECT_DOUBLE_EQ(mv1[4], 200);
    EXPECT_DOUBLE_EQ(mv1[5], 5);
    EXPECT_DOUBLE_EQ(mv1[6], 52);

    EXPECT_EQ(mv2.get_size(), 6);
    EXPECT_DOUBLE_EQ(mv2[1], 0);
    EXPECT_DOUBLE_EQ(mv2[2], 0);
    EXPECT_DOUBLE_EQ(mv2[3], -0.89);
    EXPECT_DOUBLE_EQ(mv2[4], 33);
    EXPECT_DOUBLE_EQ(mv2[5], 0.48);
    EXPECT_DOUBLE_EQ(mv2[6], 15);

    EXPECT_EQ(mv3.get_size(), 6);
    EXPECT_DOUBLE_EQ(mv3[1], -0.1);
    EXPECT_DOUBLE_EQ(mv3[2], -0.1);
    EXPECT_DOUBLE_EQ(mv3[3], -0.11);
    EXPECT_DOUBLE_EQ(mv3[4], 0);
    EXPECT_DOUBLE_EQ(mv3[5], 0.52);
    EXPECT_DOUBLE_EQ(mv3[6], 3);
}

TEST(ClassMathVector, can_throw_bad_sub_assigment) {
    MathVector<double> mv1({ 0, 0.1, 0.2, 233, 5.48, 67 });
    MathVector<double> mv2({ -0.1, -0.1, -1, 33, 1 });

    EXPECT_THROW(mv1 -= mv2, std::logic_error);

    EXPECT_EQ(mv1.get_size(), 6);
    EXPECT_DOUBLE_EQ(mv1[1], 0);
    EXPECT_DOUBLE_EQ(mv1[2], 0.1);
    EXPECT_DOUBLE_EQ(mv1[3], 0.2);
    EXPECT_DOUBLE_EQ(mv1[4], 233);
    EXPECT_DOUBLE_EQ(mv1[5], 5.48);
    EXPECT_DOUBLE_EQ(mv1[6], 67);

    EXPECT_EQ(mv2.get_size(), 5);
    EXPECT_DOUBLE_EQ(mv2[1], -0.1);
    EXPECT_DOUBLE_EQ(mv2[2], -0.1);
    EXPECT_DOUBLE_EQ(mv2[3], -1);
    EXPECT_DOUBLE_EQ(mv2[4], 33);
    EXPECT_DOUBLE_EQ(mv2[5], 1);
}

TEST(ClassMathVector, can_do_good_add) {
    MathVector<double> mv1({ 0, 0.1, 0.2, 233, 5.88, 67 });
    MathVector<double> mv2({ 0.1, 0.1, 1, -33, -0.4, -12 });
    MathVector<double> mv3({ 0, 0, 1, 28, 0, 0 });
    MathVector<double> mv_res = mv1 + mv2 + mv3;

    EXPECT_EQ(mv_res.get_size(), 6);
    EXPECT_DOUBLE_EQ(mv_res[1], 0.1);
    EXPECT_DOUBLE_EQ(mv_res[2], 0.2);
    EXPECT_DOUBLE_EQ(mv_res[3], 2.2);
    EXPECT_DOUBLE_EQ(mv_res[4], 228);
    EXPECT_DOUBLE_EQ(mv_res[5], 5.48);
    EXPECT_DOUBLE_EQ(mv_res[6], 55);

    EXPECT_EQ(mv1.get_size(), 6);
    EXPECT_DOUBLE_EQ(mv1[1], 0);
    EXPECT_DOUBLE_EQ(mv1[2], 0.1);
    EXPECT_DOUBLE_EQ(mv1[3], 0.2);
    EXPECT_DOUBLE_EQ(mv1[4], 233);
    EXPECT_DOUBLE_EQ(mv1[5], 5.88);
    EXPECT_DOUBLE_EQ(mv1[6], 67);

    EXPECT_EQ(mv2.get_size(), 6);
    EXPECT_DOUBLE_EQ(mv2[1], 0.1);
    EXPECT_DOUBLE_EQ(mv2[2], 0.1);
    EXPECT_DOUBLE_EQ(mv2[3], 1);
    EXPECT_DOUBLE_EQ(mv2[4], -33);
    EXPECT_DOUBLE_EQ(mv2[5], -0.4);
    EXPECT_DOUBLE_EQ(mv2[6], -12);

    EXPECT_EQ(mv3.get_size(), 6);
    EXPECT_DOUBLE_EQ(mv3[1], 0);
    EXPECT_DOUBLE_EQ(mv3[2], 0);
    EXPECT_DOUBLE_EQ(mv3[3], 1);
    EXPECT_DOUBLE_EQ(mv3[4], 28);
    EXPECT_DOUBLE_EQ(mv3[5], 0);
    EXPECT_DOUBLE_EQ(mv3[6], 0);
}

TEST(ClassMathVector, can_throw_bad_add) {
    MathVector<double> mv1({ 0, 0.1, 0.2, 233, 5.88, 67 });
    MathVector<double> mv2({ 0.1, 0.1, 1, -33, -12 });

    EXPECT_THROW(mv1 + mv2, std::logic_error);

    EXPECT_EQ(mv1.get_size(), 6);
    EXPECT_DOUBLE_EQ(mv1[1], 0);
    EXPECT_DOUBLE_EQ(mv1[2], 0.1);
    EXPECT_DOUBLE_EQ(mv1[3], 0.2);
    EXPECT_DOUBLE_EQ(mv1[4], 233);
    EXPECT_DOUBLE_EQ(mv1[5], 5.88);
    EXPECT_DOUBLE_EQ(mv1[6], 67);

    EXPECT_EQ(mv2.get_size(), 5);
    EXPECT_DOUBLE_EQ(mv2[1], 0.1);
    EXPECT_DOUBLE_EQ(mv2[2], 0.1);
    EXPECT_DOUBLE_EQ(mv2[3], 1);
    EXPECT_DOUBLE_EQ(mv2[4], -33);
    EXPECT_DOUBLE_EQ(mv2[5], -12);
}

TEST(ClassMathVector, can_do_good_substract) {
    MathVector<double> mv1({ 0, 0.1, 0.2, 233, 5.48, 67 });
    MathVector<double> mv2({ -0.1, -0.05, -1, 33, 1, 18 });
    MathVector<double> mv3({ 0, -0.05, 0, -137, 0, 0 });
    MathVector<double> mv_res = mv1 - mv2 - mv3;

    EXPECT_EQ(mv_res.get_size(), 6);
    EXPECT_DOUBLE_EQ(mv_res[1], 0.1);
    EXPECT_DOUBLE_EQ(mv_res[2], 0.2);
    EXPECT_DOUBLE_EQ(mv_res[3], 1.2);
    EXPECT_DOUBLE_EQ(mv_res[4], 337);
    EXPECT_DOUBLE_EQ(mv_res[5], 4.48);
    EXPECT_DOUBLE_EQ(mv_res[6], 49);

    EXPECT_EQ(mv1.get_size(), 6);
    EXPECT_DOUBLE_EQ(mv1[1], 0);
    EXPECT_DOUBLE_EQ(mv1[2], 0.1);
    EXPECT_DOUBLE_EQ(mv1[3], 0.2);
    EXPECT_DOUBLE_EQ(mv1[4], 233);
    EXPECT_DOUBLE_EQ(mv1[5], 5.48);
    EXPECT_DOUBLE_EQ(mv1[6], 67);

    EXPECT_EQ(mv2.get_size(), 6);
    EXPECT_DOUBLE_EQ(mv2[1], -0.1);
    EXPECT_DOUBLE_EQ(mv2[2], -0.05);
    EXPECT_DOUBLE_EQ(mv2[3], -1);
    EXPECT_DOUBLE_EQ(mv2[4], 33);
    EXPECT_DOUBLE_EQ(mv2[5], 1);
    EXPECT_DOUBLE_EQ(mv2[6], 18);

    EXPECT_EQ(mv3.get_size(), 6);
    EXPECT_DOUBLE_EQ(mv3[1], 0);
    EXPECT_DOUBLE_EQ(mv3[2], -0.05);
    EXPECT_DOUBLE_EQ(mv3[3], 0);
    EXPECT_DOUBLE_EQ(mv3[4], -137);
    EXPECT_DOUBLE_EQ(mv3[5], 0);
    EXPECT_DOUBLE_EQ(mv3[6], 0);
}

TEST(ClassMathVector, can_throw_bad_substract) {
    MathVector<double> mv1({ 0, 0.1, 0.2, 233, 5.48, 67 });
    MathVector<double> mv2({ -0.1, -0.1, -1, 33, 1 });

    EXPECT_THROW(mv1 - mv2, std::logic_error);

    EXPECT_EQ(mv1.get_size(), 6);
    EXPECT_DOUBLE_EQ(mv1[1], 0);
    EXPECT_DOUBLE_EQ(mv1[2], 0.1);
    EXPECT_DOUBLE_EQ(mv1[3], 0.2);
    EXPECT_DOUBLE_EQ(mv1[4], 233);
    EXPECT_DOUBLE_EQ(mv1[5], 5.48);
    EXPECT_DOUBLE_EQ(mv1[6], 67);

    EXPECT_EQ(mv2.get_size(), 5);
    EXPECT_DOUBLE_EQ(mv2[1], -0.1);
    EXPECT_DOUBLE_EQ(mv2[2], -0.1);
    EXPECT_DOUBLE_EQ(mv2[3], -1);
    EXPECT_DOUBLE_EQ(mv2[4], 33);
    EXPECT_DOUBLE_EQ(mv2[5], 1);
}

TEST(ClassMathVector, can_check_eq_true_uneq_false_same) {
    MathVector<double> mv1({ 0, 1.5, -2.34, 100 });
    MathVector<double> mv2({ 0, 1.5, -2.34, 100 });

    EXPECT_TRUE(mv1 == mv2);
    EXPECT_FALSE(mv1 != mv2);

    EXPECT_EQ(mv1.get_size(), 4);
    EXPECT_DOUBLE_EQ(mv1[1], 0.0);
    EXPECT_DOUBLE_EQ(mv1[2], 1.5);
    EXPECT_DOUBLE_EQ(mv1[3], -2.34);
    EXPECT_DOUBLE_EQ(mv1[4], 100.0);

    EXPECT_EQ(mv2.get_size(), 4);
    EXPECT_DOUBLE_EQ(mv2[1], 0);
    EXPECT_DOUBLE_EQ(mv2[2], 1.5);
    EXPECT_DOUBLE_EQ(mv2[3], -2.34);
    EXPECT_DOUBLE_EQ(mv2[4], 100);
}

TEST(ClassMathVector, check_eq_false_uneq_true_same_size) {
    MathVector<double> mv1({ 0, 1.5, -2.35, 100 });
    MathVector<double> mv2({ 0, 1.5, -2.35, 100.00001 });

    EXPECT_EQ(mv1 == mv2, false);
    EXPECT_EQ(mv1 != mv2, true);

    EXPECT_EQ(mv1.get_size(), 4);
    EXPECT_DOUBLE_EQ(mv1[1], 0);
    EXPECT_DOUBLE_EQ(mv1[2], 1.5);
    EXPECT_DOUBLE_EQ(mv1[3], -2.35);
    EXPECT_DOUBLE_EQ(mv1[4], 100);

    EXPECT_EQ(mv2.get_size(), 4);
    EXPECT_DOUBLE_EQ(mv2[1], 0);
    EXPECT_DOUBLE_EQ(mv2[2], 1.5);
    EXPECT_DOUBLE_EQ(mv2[3], -2.35);
    EXPECT_DOUBLE_EQ(mv2[4], 100.00001);
}

TEST(ClassMathVector, check_eq_false_uneq_true_diff_size) {
    MathVector<double> mv1({ 0.0, 1.5, -2.34, 100.0 });
    MathVector<double> mv2({ 0.0, 1.5, -2.34 });

    EXPECT_FALSE(mv1 == mv2);
    EXPECT_TRUE(mv1 != mv2);

    EXPECT_EQ(mv1.get_size(), 4);
    EXPECT_DOUBLE_EQ(mv1[1], 0.0);
    EXPECT_DOUBLE_EQ(mv1[2], 1.5);
    EXPECT_DOUBLE_EQ(mv1[3], -2.34);
    EXPECT_DOUBLE_EQ(mv1[4], 100.0);

    EXPECT_EQ(mv2.get_size(), 3);
    EXPECT_DOUBLE_EQ(mv2[1], 0.0);
    EXPECT_DOUBLE_EQ(mv2[2], 1.5);
    EXPECT_DOUBLE_EQ(mv2[3], -2.34);
}

TEST(ClassMathVector, can_check_eq_true_uneq_false_empty) {
    MathVector<double> mv1;
    MathVector<double> mv2;

    EXPECT_TRUE(mv1 == mv2);
    EXPECT_FALSE(mv1 != mv2);

    EXPECT_EQ(mv1.get_size(), 0);
    EXPECT_EQ(mv2.get_size(), 0);
}

TEST(ClassMathVector, check_eq_true_uneq_false_itself) {
    MathVector<double> mv1({ 0.0, 1.5, -2.34, 100.0 });

    EXPECT_TRUE(mv1 == mv1);
    EXPECT_FALSE(mv1 != mv1);

    EXPECT_EQ(mv1.get_size(), 4);
    EXPECT_DOUBLE_EQ(mv1[1], 0.0);
    EXPECT_DOUBLE_EQ(mv1[2], 1.5);
    EXPECT_DOUBLE_EQ(mv1[3], -2.34);
    EXPECT_DOUBLE_EQ(mv1[4], 100.0);
}

TEST(ClassMathVector, can_do_scalar_multiplication_assignment) {
    MathVector<double> mv({ 1, -2.5, 0, 10.5 });
    mv *= 2;

    EXPECT_EQ(mv.get_size(), 4);
    EXPECT_DOUBLE_EQ(mv[1], 2);
    EXPECT_DOUBLE_EQ(mv[2], -5);
    EXPECT_DOUBLE_EQ(mv[3], 0);
    EXPECT_DOUBLE_EQ(mv[4], 21);
}

TEST(ClassMathVector, can_do_scalar_multiplication) {
    MathVector<double> mv({ 1, -2.5, 0, 10.5 });
    MathVector<double> mv_res = mv * -3;

    EXPECT_EQ(mv_res.get_size(), 4);
    EXPECT_DOUBLE_EQ(mv_res[1], -3);
    EXPECT_DOUBLE_EQ(mv_res[2], 7.5);
    EXPECT_DOUBLE_EQ(mv_res[3], 0);
    EXPECT_DOUBLE_EQ(mv_res[4], -31.5);

    EXPECT_EQ(mv.get_size(), 4);
    EXPECT_DOUBLE_EQ(mv[1], 1);
    EXPECT_DOUBLE_EQ(mv[2], -2.5);
    EXPECT_DOUBLE_EQ(mv[3], 0);
    EXPECT_DOUBLE_EQ(mv[4], 10.5);
}

TEST(ClassMathVector, can_do_scalar_multiplication_by_zero) {
    MathVector<double> mv({ 5.5, -10.0, 3.14 });
    mv *= 0;

    EXPECT_EQ(mv.get_size(), 3);
    EXPECT_DOUBLE_EQ(mv[1], 0);
    EXPECT_DOUBLE_EQ(mv[2], 0);
    EXPECT_DOUBLE_EQ(mv[3], 0);
}

TEST(ClassMathVector, can_do_scalar_multiplication_to_empty) {
    MathVector<double> mv;
    EXPECT_NO_THROW(mv *= 5);
    EXPECT_EQ(mv.get_size(), 0);

    MathVector<double> mv_res = mv * 5;
    EXPECT_EQ(mv_res.get_size(), 0);
}

TEST(ClassMathVector, can_do_scalar_division_assignment) {
    MathVector<double> mv({ 2.0, -5, 0, 21 });
    mv /= 2;

    EXPECT_EQ(mv.get_size(), 4);
    EXPECT_DOUBLE_EQ(mv[1], 1);
    EXPECT_DOUBLE_EQ(mv[2], -2.5);
    EXPECT_DOUBLE_EQ(mv[3], 0);
    EXPECT_DOUBLE_EQ(mv[4], 10.5);
}

TEST(ClassMathVector, can_do_scalar_division) {
    const MathVector<double> mv({ 3, -7.5, 0, 31.5 });
    MathVector<double> mv_res = mv / 3;

    EXPECT_EQ(mv_res.get_size(), 4);
    EXPECT_DOUBLE_EQ(mv_res[1], 1);
    EXPECT_DOUBLE_EQ(mv_res[2], -2.5);
    EXPECT_DOUBLE_EQ(mv_res[3], 0);
    EXPECT_DOUBLE_EQ(mv_res[4], 10.5);

    EXPECT_EQ(mv.get_size(), 4);
    EXPECT_DOUBLE_EQ(mv[1], 3);
    EXPECT_DOUBLE_EQ(mv[2], -7.5);
    EXPECT_DOUBLE_EQ(mv[3], 0);
    EXPECT_DOUBLE_EQ(mv[4], 31.5);
}

TEST(ClassMathVector, can_do_scalar_division_of_zero_vector) {
    MathVector<double> mv({ 0, 0, 0 });
    mv /= 5.5;

    EXPECT_EQ(mv.get_size(), 3);
    EXPECT_DOUBLE_EQ(mv[1], 0);
    EXPECT_DOUBLE_EQ(mv[2], 0);
    EXPECT_DOUBLE_EQ(mv[3], 0);
}

TEST(ClassMathVector, can_do_scalar_division_to_empty) {
    MathVector<double> mv;

    EXPECT_NO_THROW(mv /= 2);
    EXPECT_EQ(mv.get_size(), 0);

    MathVector<double> mv_res = mv / 2;
    EXPECT_EQ(mv_res.get_size(), 0);
}

TEST(ClassMathVector, can_throw_scalar_division_by_zero) {
    MathVector<double> mv({ 1, 2, 3 });

    EXPECT_THROW(mv /= 0, std::logic_error);
    EXPECT_THROW(mv / 0, std::logic_error);

    EXPECT_EQ(mv.get_size(), 3);
    EXPECT_DOUBLE_EQ(mv[1], 1);
    EXPECT_DOUBLE_EQ(mv[2], 2);
    EXPECT_DOUBLE_EQ(mv[3], 3);
}

TEST(ClassMathVector, can_cout) {
    double array[5] = { 0, 0.1, 0.2, 233, 5.89 };
    MathVector<double> mv1(array, 5);
    std::stringstream ss;
    ss << mv1;
    EXPECT_EQ(ss.str(), "{ 0, 0.1, 0.2, 233, 5.89 }");
}

TEST(ClassMathVector, can_cin) {
    std::stringstream ss("5 0.0 0.1 0.2 233.0 5.89");
    MathVector<double> mv1;
    ss >> mv1;
    EXPECT_DOUBLE_EQ(0.0, mv1[1]);
    EXPECT_DOUBLE_EQ(0.1, mv1[2]);
    EXPECT_DOUBLE_EQ(0.2, mv1[3]);
    EXPECT_DOUBLE_EQ(233.0, mv1[4]);
    EXPECT_DOUBLE_EQ(5.89, mv1[5]);
    EXPECT_EQ(5, mv1.get_size());
}