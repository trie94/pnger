#ifndef IMAGELOADER_H
#define IMAGELOADER_H
#include <png.h>
#include "imageInfo.h"

class ImageLoader {
private:
    png_structp png_ptr = nullptr;
    png_infop info_ptr = nullptr;
   public:
    ImageLoader();
    ImageLoader(const ImageLoader& other)=delete;
    ~ImageLoader();
    ImageLoader& operator=(const ImageLoader& other)=delete;
    ImageInfo read_png_file(char* file_name);
};

#endif
