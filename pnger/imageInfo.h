
#ifndef IMAGEINFO_H
#define IMAGEINFO_H
#include <png.h>

struct ImageInfo {
    png_byte* buf_ptr = nullptr;
    png_bytep* row_pointers = nullptr;
    png_structp png_ptr = nullptr;
    png_infop info_ptr = nullptr;
    png_byte color_type = 0;
    png_byte bit_depth = 0;

    int width = 0, height = 0;
    int number_of_passes = 0;
    int num_color_channel = 0;
};
#endif
