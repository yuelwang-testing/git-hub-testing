#include <cassert>
#include "Matrix.hpp"

using namespace std;

// REQUIRES: mat points to a Matrix
//           0 < width && 0 < height
// MODIFIES: *mat
// EFFECTS:  Initializes *mat as a Matrix with the given width and height,
//           with all elements initialized to 0.
void Matrix_init(Matrix* mat, int width, int height) {
assert(mat != nullptr && 0 < width && 0 < height);
mat-> width =width;
mat-> height =height;
mat->data.resize(width * height);
}

// REQUIRES: mat points to a valid Matrix
// MODIFIES: os
// EFFECTS:  First, prints the width and height for the Matrix to os:
//             WIDTH [space] HEIGHT [newline]
//           Then prints the rows of the Matrix to os with one row per line.
//           Each element is followed by a space and each row is followed
//           by a newline. This means there will be an "extra" space at
//           the end of each line.
void Matrix_print(const Matrix* mat, std::ostream& os) {
    assert(mat != nullptr);
    os << mat-> width << " " << mat-> height << endl;
    for(size_t i =0; i < mat->height; ++i){
        for(size_t j =0; j < mat->width; ++j){
            os << *Matrix_at(mat, i, j) << " ";
        }
        os << endl;
    }
}

// REQUIRES: mat points to a valid Matrix
// EFFECTS:  Returns the width of the Matrix.
int Matrix_width(const Matrix* mat) {
  assert(mat != nullptr);
  return mat->width;
}

// REQUIRES: mat points to a valid Matrix
// EFFECTS:  Returns the height of the Matrix.
int Matrix_height(const Matrix* mat) {
  assert(mat != nullptr);
  return mat->height;
}

// REQUIRES: mat points to a valid Matrix
//           ptr points to an element in the Matrix
// EFFECTS:  Returns the row of the element pointed to by ptr.
int Matrix_row(const Matrix* mat, const int* ptr) {
    assert(mat != nullptr && ptr != nullptr);
    int offset = ptr - (&mat->data[0]);
    int row = offset / mat->width;
    return row;
}

// REQUIRES: mat points to a valid Matrix
//           ptr point to an element in the Matrix
// EFFECTS:  Returns the column of the element pointed to by ptr.
int Matrix_column(const Matrix* mat, const int* ptr) {
    assert(mat != nullptr && ptr != nullptr);
    int offset = ptr - (&mat->data[0]);
    int col = offset % mat->width;
    return col;
}

// REQUIRES: mat points to a valid Matrix
//           0 <= row && row < Matrix_height(mat)
//           0 <= column && column < Matrix_width(mat)
//
// MODIFIES: (The returned pointer may be used to modify an
//            element in the Matrix.)
// EFFECTS:  Returns a pointer to the element in the Matrix
//           at the given row and column.
int* Matrix_at(Matrix* mat, int row, int column) {
    assert(mat != nullptr && 0 <= row && row < mat->height && 0 <= column && column < mat->width);
    int index = row * mat->width + column;
    return &mat->data[index];
}

// REQUIRES: mat points to a valid Matrix
//           0 <= row && row < Matrix_height(mat)
//           0 <= column && column < Matrix_width(mat)
//
// EFFECTS:  Returns a pointer-to-const to the element in
//           the Matrix at the given row and column.
const int* Matrix_at(const Matrix* mat, int row, int column) {
    assert(mat != nullptr && 0 <= row && row < mat->height && 0 <= column && column < mat->width);
    int index = row * mat->width + column;
    const int * ptr = &mat->data[index];
    return ptr;
}

// REQUIRES: mat points to a valid Matrix
// MODIFIES: *mat
// EFFECTS:  Sets each element of the Matrix to the given value.
void Matrix_fill(Matrix* mat, int value) {
    assert(mat != nullptr);
    for(size_t i =0; i< mat->width * mat->height; ++i){
        mat->data[i] = value;
    }
}

// REQUIRES: mat points to a valid Matrix
// MODIFIES: *mat
// EFFECTS:  Sets each element on the border of the Matrix to
//           the given value. These are all elements in the first/last
//           row or the first/last column.
void Matrix_fill_border(Matrix* mat, int value) {
    assert(mat != nullptr);
    for(size_t col =0; col < mat->width; ++col){
        mat->data[col] = value;
    }
    for(size_t col =0; col < mat->width; ++col){
        mat->data[(mat->height-1)* mat->width + col] = value;
    }
    for(size_t row =0; row < mat->height; ++row){
        mat->data[row * mat->width] = value;
    }
    for(size_t row =0; row < mat->height; ++row){
        mat->data[row * mat->width +(mat->width -1)] = value;
    }
}


// REQUIRES: mat points to a valid Matrix
// EFFECTS:  Returns the value of the maximum element in the Matrix
int Matrix_max(const Matrix* mat) {
  assert(mat != nullptr);
  int max = mat->data[0];
    for(size_t i =0; i < mat->height; ++i){
        for(size_t j =0; j < mat->width; ++j){
            if(*Matrix_at(mat, i, j) > max){
                max = *Matrix_at(mat, i, j);
            }
        }
    }
    return max;
}

// REQUIRES: mat points to a valid Matrix
//           0 <= row && row < Matrix_height(mat)
//           0 <= column_start && column_end <= Matrix_width(mat)
//           column_start < column_end
// EFFECTS:  Returns the column of the element with the minimal value
//           in a particular region. The region is defined as elements
//           in the given row and between column_start (inclusive) and
//           column_end (exclusive).
//           If multiple elements are minimal, returns the column of
//           the leftmost one.
int Matrix_column_of_min_value_in_row(const Matrix* mat, int row,
                                      int column_start, int column_end) {
    assert(mat != nullptr);
    assert(0 <= row && row < mat->height);
    assert(0 <= column_start && column_end <= mat->width);
    assert(column_start < column_end);
    
    int min = mat->data[row* mat->width+column_start];
    int increment = -1;
    int column = column_start;
    for(size_t col =column_start; col < column_end; ++col){
        increment++;
        if(mat->data[row* mat->width + col]< min){
            min = mat->data[row* mat->width + col];
            column = column_start;
            column = column + increment;
        }
    }
    return column;
}

// REQUIRES: mat points to a valid Matrix
//           0 <= row && row < Matrix_height(mat)
//           0 <= column_start && column_end <= Matrix_width(mat)
//           column_start < column_end
// EFFECTS:  Returns the minimal value in a particular region. The region
//           is defined as elements in the given row and between
//           column_start (inclusive) and column_end (exclusive).
int Matrix_min_value_in_row(const Matrix* mat, int row,
                            int column_start, int column_end) {
  assert(mat != nullptr);
  assert(0 <= row && row < mat->height);
  assert(0 <= column_start && column_end <= mat->width);
  assert(column_start < column_end);
  int min = mat->data[row* mat->width+column_start];
  for(size_t col =column_start; col < column_end; ++col){
      if(mat->data[row* mat->width + col]< min){
        min = mat->data[row* mat->width + col];
    }
  }
  return min;
}

