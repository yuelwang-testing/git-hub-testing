#include "Matrix.hpp"
#include "Image_test_helpers.hpp"
#include "unit_test_framework.hpp"
#include <iostream>
#include <string>
#include <sstream>
#include <cassert>

using namespace std;

// Here's a free test for you! Model yours after this one.
// Test functions have no interface and thus no RMEs, but
// add a comment like the one here to say what it is testing.
// -----
// Sets various pixels in a 2x2 Image and checks
// that Image_print produces the correct output.
// 此测验测试了 Image_init，Image_set_pixel 和 Image_print
TEST(test_print_basic) {
    Image img;
    const Pixel red = {255, 0, 0};
    const Pixel green = {0, 255, 0};
    const Pixel blue = {0, 0, 255};
    const Pixel white = {255, 255, 255};
    
    Image_init(&img, 2, 2);
    Image_set_pixel(&img, 0, 0, red);
    Image_set_pixel(&img, 0, 1, green);
    Image_set_pixel(&img, 1, 0, blue);
    Image_set_pixel(&img, 1, 1, white);
    
    // Capture our output
    ostringstream s;
    Image_print(&img, s);
    
    // Correct output
    ostringstream correct;
    correct << "P3\n2 2\n255\n";
    correct << "255 0 0 0 255 0 \n";
    correct << "0 0 255 255 255 255 \n";
    ASSERT_EQUAL(s.str(), correct.str());
}

// 这个是 Image_init（阅读文件版本）的第一轮测试
TEST(test_init) {
    Image img;
    string picture = "P3\n3 2\n255\n255 0 0 0 255 0 0 0 255 \n";
    picture += "0 0 255 0 255 0 255 0 0 \n"; //3x2，第一行是红 - 绿 - 蓝，第二行是蓝 - 绿 - 红
    istringstream inSS(picture);
    Image_init(&img, inSS);
    
    ostringstream answer;
    Image_print(&img, answer);
    
    ostringstream correct;
    correct << "P3\n2 2\n255\n";
    correct << "255 0 0 0 255 0 0 0 255 \n";
    correct << "0 0 255 0 255 0 255 0 0 \n";
    ASSERT_EQUAL(answer.str(), correct.str());
}

// Test for function image_width
TEST(test_Image_width){
  Image img;
  Image_init(&img, 3, 2);
  int correct = 3;
  ASSERT_EQUAL(Image_width(&img), correct);
}

// Test for function image_height
TEST(test_Image_height){
  Image img;
  Image_init(&img, 3, 2);
  int correct = 2;
  ASSERT_EQUAL(Image_height(&img), correct);
}
//Test for function Image_get_pixel
TEST(test_Image_get_pixel) {
    Image img;
    string picture = "P3\n3 2\n255\n255 0 0 0 255 0 0 0 255 \n";
    picture += "0 0 255 0 255 0 255 0 0 \n"; //3x2，第一行是红 - 绿 - 蓝，第二行是蓝 - 绿 - 红
    istringstream image(picture);
    Image_init(&img, image);
    
    // Test some pixels
    Pixel p = Image_get_pixel(&img, 0, 0);
    assert(p.r == 255 && p.g == 0 && p.b == 0);
    
    p = Image_get_pixel(&img, 1, 1);
    assert(p.r == 0 && p.g == 255 && p.b == 0);
    
    p = Image_get_pixel(&img, 0, 1);
    assert(p.r == 0 && p.g == 255 && p.b == 0);
    
    p = Image_get_pixel(&img, 1, 0);
    assert(p.r == 0 && p.g == 0 && p.b == 255);
}

TEST(test_Image_fill){
  Image img;
  const Pixel white = {255, 255, 255};
  string picture = "P3\n3 2\n255\n255 0 0 0 255 0 0 0 255 \n";
  picture += "0 0 255 0 255 0 255 0 0 \n"; //3x2，第一行是红 - 绿 - 蓝，第二行是蓝 - 绿 - 红
  istringstream image(picture);
  Image_init(&img, image);   
  Image_fill(&img, white);
 
    ostringstream s;
    Image_print(&img, s);
    
    // Correct output
    ostringstream correct;
    correct << "P3\n3 2\n255\n";
    correct << "255 255 255 255 255 255 \n";
    correct << "255 255 255 255 255 255 \n";
    ASSERT_EQUAL(s.str(), correct.str());
}

TEST_MAIN() // Do NOT put a semicolon here
