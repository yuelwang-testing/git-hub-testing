#include <cassert>
#include "Image.hpp"

using namespace std;
// REQUIRES: img points to an Image
//           0 < width && 0 < height
// MODIFIES: *img
// EFFECTS:  Initializes the Image with the given width and height, with
//           all pixels initialized to RGB values of 0.
void Image_init(Image* img, int width, int height) {
  assert(img != nullptr && 0 < width && 0 < height);
  img-> width = width;
  img-> height = height;
  Matrix_init(&img->red_channel, width, height);
  Matrix_init(&img->green_channel, width, height);
  Matrix_init(&img->blue_channel, width, height);
  Matrix_fill(&img->red_channel, 0);
  Matrix_fill(&img->green_channel, 0);
  Matrix_fill(&img->blue_channel, 0);
}

// REQUIRES: img points to an Image
//           is contains an image in PPM format without comments
//           (any kind of whitespace is ok)
// MODIFIES: *img, is
// EFFECTS:  Initializes the Image by reading in an image in PPM format
//           from the given input stream.
// NOTE:     See the project spec for a discussion of PPM format.
void Image_init(Image* img, std::istream& is) {
    assert(img != nullptr);
    string junk = "";
    is >> junk;
    assert(junk == "P3");
    int max_value;
    is >> img->height >> img->width >> max_value;
    
    int r;
    int g;
    int b;
    Pixel color;
    for (size_t i =0; i<img->height; ++i){
        for(size_t j =0; j<img->width; ++j){
            is >> r >> g >> b;
            Image_set_pixel(img, i, j, color);
        }
    }
}

// REQUIRES: img points to a valid Image
// MODIFIES: os
// EFFECTS:  Writes the image to the given output stream in PPM format.
//           You must use the kind of whitespace specified here.
//           First, prints out the header for the image like this:
//             P3 [newline]
//             WIDTH [space] HEIGHT [newline]
//             255 [newline]
//           Next, prints out the rows of the image, each followed by a
//           newline. Each pixel in a row is printed as three ints
//           for its red, green, and blue components, in that order. Each
//           int is followed by a space. This means that there will be an
//           "extra" space at the end of each line. See the project spec
//           for an example.
void Image_print(const Image* img, std::ostream& os) {
   assert(img != nullptr);
   os << "P3" << endl << img->width << " " << img->height << endl << MAX_INTENSITY << endl;
   for (size_t i =0; i<img->height; ++i){
    for(size_t j =0; j<img->width; ++j){
      Pixel p = Image_get_pixel(img, i, j);
      os << p.r << " " << p.g << " " << p.b << " ";
    }
    os << endl;
   }
}

// REQUIRES: img points to a valid Image
// EFFECTS:  Returns the width of the Image.
int Image_width(const Image* img) {
  assert(img != nullptr);
  return img->width;
}

// REQUIRES: img points to a valid Image
// EFFECTS:  Returns the height of the Image.
int Image_height(const Image* img) {
  assert(img != nullptr);
  return img->height;
}

// REQUIRES: img points to a valid Image
//           0 <= row && row < Image_height(img)
//           0 <= column && column < Image_width(img)
// EFFECTS:  Returns the pixel in the Image at the given row and column.
Pixel Image_get_pixel(const Image* img, int row, int column) {
  assert(img != nullptr);
  assert(0 <= row && row < Image_height(img));
  assert(0 <= column && column < Image_width(img));
  Pixel p;
  p.r = *Matrix_at(&img->red_channel, row, column);
  p.g = *Matrix_at(&img->green_channel, row, column);
  p.b = *Matrix_at(&img->blue_channel, row, column);
  return p;
}

// REQUIRES: img points to a valid Image
//           0 <= row && row < Image_height(img)
//           0 <= column && column < Image_width(img)
// MODIFIES: *img
// EFFECTS:  Sets the pixel in the Image at the given row and column
//           to the given color.
void Image_set_pixel(Image* img, int row, int column, Pixel color) {
  assert(img != nullptr);
  assert(0 <= row && row < Image_height(img));
  assert(0 <= column && column < Image_width(img));

  *Matrix_at(&img->red_channel, row, column) = color.r;
  *Matrix_at(&img->green_channel, row, column) = color.g;
  *Matrix_at(&img->blue_channel, row, column) = color.b;
}

// REQUIRES: img points to a valid Image
// MODIFIES: *img
// EFFECTS:  Sets each pixel in the image to the given color.
void Image_fill(Image* img, Pixel color) {
  assert(img != nullptr);
  Matrix_fill(&img->red_channel, color.r);
  Matrix_fill(&img->green_channel, color.g);
  Matrix_fill(&img->blue_channel, color.b);
}

