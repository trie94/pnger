#ifndef IMAGEPROCESSOR_H
#define IMAGEPROCESSOR_H
#include <png.h>
#include "imageInfo.h"

class ImageProcessor {
private:
    int get_num_color_channel(png_structp png_ptr, png_infop info_ptr);
public:
    void grayscale(ImageInfo image_info);
    void invert(ImageInfo image_info);
};
#endif
