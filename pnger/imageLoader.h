#ifndef IMAGELOADER_H
#define IMAGELOADER_H
#include <png.h>

#include "imageInfo.h"

class ImageLoader {
   public:
    ImageInfo read_png_file(char* file_name);
};

#endif