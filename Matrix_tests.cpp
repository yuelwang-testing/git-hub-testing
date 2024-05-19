#include "Matrix.hpp"
#include "Matrix_test_helpers.hpp"
#include "unit_test_framework.hpp"
#include <sstream>

using namespace std;

// Here's a free test for you! Model yours after this one.
// Test functions have no interface and thus no RMEs, but
// add a comment like the one here to say what it is testing.
// -----
// Fills a 3x5 Matrix with a value and checks
// that Matrix_at returns that value for each element.
// 这个用来测验"Matrix_init"，"Matrix_fill"和非常数版本（不是const）的"Matrix_at"（"Matrix_at"是第一轮测试）
TEST(test_init_fill_and_at) {
    Matrix mat;
    const int width = 3;
    const int height = 5;
    const int value = 42;
    Matrix_init(&mat, 3, 5);
    Matrix_fill(&mat, value);
    
    for(int r = 0; r < height; ++r) {
        for(int c = 0; c < width; ++c) {
            ASSERT_EQUAL(*Matrix_at(&mat, r, c), value);
        }
    }
}

// 这个是第二轮的非常数版本的"Matrix_at"的测试
TEST(test_nonconstant_at_2) {
    Matrix mat;
    const int width = 6;
    const int height = 5;
    const int value = -2;
    Matrix_init(&mat, 6, 5);
    Matrix_fill(&mat, value);
    
    for(int r = 0; r < height; ++r) {
        for(int c = 0; c < width; ++c) {
            ASSERT_EQUAL(*Matrix_at(&mat, r, c), value);
        }
    }
}

// 这个是测试常数版本的"Matrix_at"的测试
// 抱歉，好像不太知道该怎么测试常数版本，我先暂时把这个测试关掉
/*
TEST(test_constant_at) {
    Matrix mat;
    const int width = 6;
    const int height = 5;
    const int value = -2;
    Matrix_init(&mat, 6, 5);
    Matrix_fill(&mat, value);
    
    for(int r = 0; r < height; ++r) {
        for(int c = 0; c < width; ++c) {
            ASSERT_EQUAL(*Matrix_at(&mat, r, c), value);
        }
    }
}
 */

// 这个是测试"Matrix_row"的
TEST(test_row) {
    Matrix mat;
    Matrix_init(&mat, 6, 5);
    int *ptr = Matrix_at(&mat, 4, 3);
    int correct = 4;
    
    ASSERT_EQUAL(Matrix_row(&mat, ptr), correct);
}


// 这个是"Matrix_column"的第一轮测试
TEST(test_column_1) {
    Matrix mat;
    Matrix_init(&mat, 6, 5);
    int *ptr = Matrix_at(&mat, 4, 3);
    int correct = 3;
    
    ASSERT_EQUAL(Matrix_column(&mat, ptr), correct);
}

// 这个是"Matrix_column"的第二轮测试
TEST(test_column_2) {
    Matrix mat;
    Matrix_init(&mat, 2, 1);
    int *ptr = Matrix_at(&mat, 0, 1);
    int correct = 1;
    
    ASSERT_EQUAL(Matrix_column(&mat, ptr), correct);
}


// 这个是测试"Matrix_width"的
TEST(test_width) {
    Matrix mat;
    Matrix_init(&mat, 6, 5);
    int correct = 6;
    
    ASSERT_EQUAL(Matrix_width(&mat), correct);
}

// 这个是测试"Matrix_height"的
TEST(test_height) {
    Matrix mat;
    Matrix_init(&mat, 6, 5);
    int correct = 5;
    
    ASSERT_EQUAL(Matrix_height(&mat), correct);
}

// 这个是"Matrix_print"的第一轮测试
TEST(test_print_1) {
    Matrix mat;
    Matrix_init(&mat, 2, 2);
    *Matrix_at(&mat, 0, 1) = 2;
    *Matrix_at(&mat, 1, 0) = -5;
    *Matrix_at(&mat, 1, 1) = 78;
    ostringstream expected;
    expected << "2 2\n"
    << "0 2 \n"
    << "-5 78 \n";
    ostringstream actual;
    Matrix_print(&mat, actual);
    ASSERT_EQUAL(expected.str(), actual.str());
}

// 这个是"Matrix_print"的第二轮测试
TEST(test_print_2) {
    Matrix mat;
    Matrix_init(&mat, 2, 3);
    *Matrix_at(&mat, 0, 0) = 6;
    *Matrix_at(&mat, 0, 1) = 9;
    *Matrix_at(&mat, 1, 0) = -3;
    *Matrix_at(&mat, 1, 1) = 7;
    *Matrix_at(&mat, 2, 0) = 0;
    *Matrix_at(&mat, 2, 1) = 17;
    ostringstream expected;
    expected << "2 3\n"
    << "6 9 \n"
    << "-3 7 \n"
    << "0 17 \n";
    ostringstream actual;
    Matrix_print(&mat, actual);
    ASSERT_EQUAL(expected.str(), actual.str());
}

// 这个是"Matrix_fill_border"的第一轮测试
TEST(test_fill_border_1) {
    Matrix mat;
    Matrix_init(&mat, 3, 4);
    Matrix_fill_border(&mat, 5);
    int correct = 5;
    ASSERT_EQUAL(*Matrix_at(&mat, 0, 2), correct);
    ASSERT_EQUAL(*Matrix_at(&mat, 2, 0), correct);
    ASSERT_EQUAL(*Matrix_at(&mat, 3, 1), 5);
}

// 这个是"Matrix_fill_border"的第二轮测试
TEST(test_fill_border_2) {
    Matrix mat;
    Matrix_init(&mat, 5, 4);
    Matrix_fill_border(&mat, -239);
    int correct = -239;
    ASSERT_EQUAL(*Matrix_at(&mat, 0, 2), correct);
    ASSERT_EQUAL(*Matrix_at(&mat, 2, 4), correct);
    ASSERT_EQUAL(*Matrix_at(&mat, 3, 1), -239);
}

// 这个是"Matrix_max"的第一轮测试
TEST(test_max_1) {
    Matrix mat;
    Matrix_init(&mat, 3, 2);
    *Matrix_at(&mat, 0, 0) = 6;
    *Matrix_at(&mat, 0, 1) = 9;
    *Matrix_at(&mat, 0, 2) = -3;
    *Matrix_at(&mat, 1, 0) = 7;
    *Matrix_at(&mat, 1, 1) = 0;
    *Matrix_at(&mat, 1, 2) = 17;
    int correct = 17;
    ASSERT_EQUAL(Matrix_max(&mat), correct);
}

// 这个是"Matrix_max"的第二轮测试
TEST(test_max_2) {
    Matrix mat;
    Matrix_init(&mat, 2, 3);
    *Matrix_at(&mat, 0, 0) = -6;
    *Matrix_at(&mat, 0, 1) = -9;
    *Matrix_at(&mat, 1, 0) = -3;
    *Matrix_at(&mat, 1, 1) = -7;
    *Matrix_at(&mat, 2, 0) = -10;
    *Matrix_at(&mat, 2, 1) = -17;
    int correct = -3;
    ASSERT_EQUAL(Matrix_max(&mat), correct);
}

// 这个是"Matrix_colum_of_min"的第一轮测试
TEST(test_column_of_min_1) {
    Matrix mat;
    Matrix_init(&mat, 3, 2);
    *Matrix_at(&mat, 0, 0) = -6;
    *Matrix_at(&mat, 0, 1) = -9;
    *Matrix_at(&mat, 0, 2) = -3;
    *Matrix_at(&mat, 1, 0) = -7;
    *Matrix_at(&mat, 1, 1) = -10;
    *Matrix_at(&mat, 1, 2) = -17;
    int correct = 1;
    ASSERT_EQUAL(Matrix_column_of_min_value_in_row(&mat, 0, 0, 3), correct);
}

// 这个是"Matrix_colum_of_min"的第二轮测试
TEST(test_column_of_min_2) {
    Matrix mat;
    Matrix_init(&mat, 3, 2);
    *Matrix_at(&mat, 0, 0) = -6;
    *Matrix_at(&mat, 0, 1) = -9;
    *Matrix_at(&mat, 0, 2) = -3;
    *Matrix_at(&mat, 1, 0) = -7;
    *Matrix_at(&mat, 1, 1) = -10;
    *Matrix_at(&mat, 1, 2) = -17;
    int correct = 2;
    ASSERT_EQUAL(Matrix_column_of_min_value_in_row(&mat, 1, 0, 3), correct);
}

// Test for function Matrix_column_of_min_value_in_row
TEST(test_Matrix_column_of_min_value_in_row){
    Matrix mat;
    const int width = 4;
    const int height = 4;
    Matrix_init(&mat, width, height);
    *Matrix_at(&mat, 0, 0) = 3;
    *Matrix_at(&mat, 0, 1) = 6;
    *Matrix_at(&mat, 0, 2) = 7;
    *Matrix_at(&mat, 0, 3) = 1;
    *Matrix_at(&mat, 1, 0) = 1;
    *Matrix_at(&mat, 1, 1) = 6;
    *Matrix_at(&mat, 1, 2) = 3;
    *Matrix_at(&mat, 1, 3) = 0;
    *Matrix_at(&mat, 2, 0) = 0;
    *Matrix_at(&mat, 2, 1) = 7;
    *Matrix_at(&mat, 2, 2) = 8;
    *Matrix_at(&mat, 2, 3) = 9;
    *Matrix_at(&mat, 3, 0) = 10;
    *Matrix_at(&mat, 3, 1) = 2;
    *Matrix_at(&mat, 3, 2) = 0;
    *Matrix_at(&mat, 3, 3) = 8;
    int correct =3;
    ASSERT_EQUAL(Matrix_column_of_min_value_in_row(&mat,1,0,4), correct);
}

// Test for function Matrix_min_value_in_row
// find the min
TEST(test_Matrix_min_value_in_row_1){
    Matrix mat;
    const int width = 3;
    const int height = 3;
    Matrix_init(&mat, width, height);
    *Matrix_at(&mat, 0, 0) = 3;
    *Matrix_at(&mat, 0, 1) = 1;
    *Matrix_at(&mat, 0, 2) = 7;
    *Matrix_at(&mat, 1, 0) = 8;
    *Matrix_at(&mat, 1, 1) = 0;
    *Matrix_at(&mat, 1, 2) = 6;
    *Matrix_at(&mat, 2, 0) = 3;
    *Matrix_at(&mat, 2, 1) = 3;
    *Matrix_at(&mat, 2, 2) = 5;
    int correct =0;
    ASSERT_EQUAL(Matrix_min_value_in_row(&mat,1,0,3), correct);
}

// Test for function Matrix_min_value_in_row
// find the min when there is a smaller value outside of the given row
TEST(test_Matrix_min_value_in_row_2){
    Matrix mat;
    const int width = 3;
    const int height = 3;
    Matrix_init(&mat, width, height);
    *Matrix_at(&mat, 0, 0) = 3;
    *Matrix_at(&mat, 0, 1) = 0;
    *Matrix_at(&mat, 0, 2) = 7;
    *Matrix_at(&mat, 1, 0) = 8;
    *Matrix_at(&mat, 1, 1) = 1;
    *Matrix_at(&mat, 1, 2) = 6;
    *Matrix_at(&mat, 2, 0) = 3;
    *Matrix_at(&mat, 2, 1) = 0;
    *Matrix_at(&mat, 2, 2) = 5;
    int correct =1;
    ASSERT_EQUAL(Matrix_min_value_in_row(&mat,1,0,3), correct);
}

// Test for function Matrix_min_value_in_row
// find the min when there is a bigger scope with a smaller 
// value outside of the given row and column
TEST(test_Matrix_min_value_in_row_3){
    Matrix mat;
    const int width = 4;
    const int height = 4;
    Matrix_init(&mat, width, height);
    *Matrix_at(&mat, 0, 0) = 3;
    *Matrix_at(&mat, 0, 1) = 1;
    *Matrix_at(&mat, 0, 2) = 7;
    *Matrix_at(&mat, 0, 3) = 0;
    *Matrix_at(&mat, 1, 0) = 1;
    *Matrix_at(&mat, 1, 1) = 6;
    *Matrix_at(&mat, 1, 2) = 3;
    *Matrix_at(&mat, 1, 3) = 0;
    *Matrix_at(&mat, 2, 0) = 5;
    *Matrix_at(&mat, 2, 1) = 7;
    *Matrix_at(&mat, 2, 2) = 8;
    *Matrix_at(&mat, 2, 3) = 9;
    *Matrix_at(&mat, 3, 0) = 10;
    *Matrix_at(&mat, 3, 1) = 2;
    *Matrix_at(&mat, 3, 2) = 0;
    *Matrix_at(&mat, 3, 3) = 8;
    int correct =3;
    ASSERT_EQUAL(Matrix_min_value_in_row(&mat,1,1,3), correct);
}

TEST_MAIN() // Do NOT put a semicolon here
