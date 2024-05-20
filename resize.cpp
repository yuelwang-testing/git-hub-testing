#include <iostream>
#include <fstream>
#include <sstream>
#include "Image.hpp"
#include "processing.hpp"

using namespace std;


int main(int argc, char* argv[]) {
    if (argc != 4 && argc != 5) {
        cout << "Usage: resize.exe IN_FILENAME OUT_FILENAME WIDTH [HEIGHT]\n"
     << "WIDTH and HEIGHT must be less than or equal to original" << endl;
    }

    string input_filename = argv[1];
    string output_filename = argv[2];
    int new_width = stoi(argv[3]);
    int new_height = -1;

    if (argc == 5) {
        new_height = stoi(argv[4]);
    }
    ifstream infile(input_filename);
      if (!infile.is_open()) {
    cout << "Unable to open " << input_filename << endl;
    exit(EXIT_FAILURE);
  }
    ofstream outfile(output_filename);
       if (!outfile.is_open()) {
    cout << "Unable to open " << output_filename << endl;
    exit(EXIT_FAILURE);
  }

    Image img;
    Image_init(&img, infile);
    
    if (new_width <= 0 || new_width > Image_width(&img) ||
        (new_height != -1 && (new_height <= 0 || new_height > Image_height(&img)))) {
        cout << "Usage: resize.exe IN_FILENAME OUT_FILENAME WIDTH [HEIGHT]\n"
     << "WIDTH and HEIGHT must be less than or equal to original" << endl;
    }

    if (new_height == -1) {
        seam_carve_width(&img, new_width);
    } else {
        seam_carve(&img, new_width, new_height);
    }

    Image_print(&img, outfile);
    
    return 0;
}
