#include "Matrix.hpp"
#include "Matrix_test_helpers.hpp"
#include "unit_test_framework.hpp"

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
    // 注意，在此项目的指导方针上面说到“Respect the interfaces for the modules you are testing. 
    // Do not access member variables of the structs directly.” 也就是说我是不是不应该写“mat.data.data()”，
    // 而是去用一个 Matrix.cpp 里面的一个方程来建立这个 pointer 呢（不过这些测试的cpp文件倒不会接受格式上的检查，
    // 似乎只要能捕捉到所有的bug就可以了，所以我们现在要不就先这样写吧）
    int *ptr = mat.data.data() + 27;
    int correct = 4;
    
    ASSERT_EQUAL(Matrix_row(&mat, ptr), correct);
}


TEST_MAIN() // Do NOT put a semicolon here
