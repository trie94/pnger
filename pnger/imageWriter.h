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
public:
    void write_png_file(ImageInfo image_info, char* file_name);
};

#endif /* imageWriter_h */
