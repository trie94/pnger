#ifndef IMAGEPROCESSOR_H
#define IMAGEPROCESSOR_H
#include <png.h>
#include "imageInfo.h"

class ImageProcessor {
public:
    void grayscale(ImageInfo& image_info);
    void invert(ImageInfo& image_info);
};
#endif
