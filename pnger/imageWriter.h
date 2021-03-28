//
//  imageWriter.h
//  pnger
//
//  Created by Yein Jo on 3/28/21.
//

#ifndef IMAGEWRITER_H
#define IMAGEWRITER_H
#include "imageInfo.h"
class ImageWriter {
private:
    png_structp png_ptr;
    png_infop info_ptr;
public:
    ImageWriter();
    ImageWriter(const ImageWriter& other)=delete;
    ~ImageWriter();
    ImageWriter& operator=(const ImageWriter& other)=delete;
    void write_png_file(const ImageInfo& image_info, char* file_name);
};

#endif /* imageWriter_h */
