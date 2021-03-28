//
//  imageInfo.cpp
//  pnger
//
//  Created by Yein Jo on 3/28/21.
//

#include <stdio.h>
#include "imageInfo.h"
#include "utils.h"
#include <memory>

namespace {
    int compute_num_color_channel(png_structp png_ptr, png_infop info_ptr) {
        switch (png_get_color_type(png_ptr, info_ptr)) {
            case PNG_COLOR_TYPE_RGB:
                return 3;

            case PNG_COLOR_TYPE_RGBA:
                return 4;

            default:
                 utils::abort_("not supported color type.");
        }
        return 0;
    }
}


ImageInfo::ImageInfo(png_structp png_ptr, png_infop info_ptr, png_byte color_type, png_byte bit_depth, int width, int height, int number_of_passes):color_type(color_type), bit_depth(bit_depth), width(width), height(height), number_of_passes(number_of_passes){
    buf_ptr =
        (png_byte*)malloc(png_get_rowbytes(png_ptr, info_ptr) * height);
    row_pointers = (png_bytep*)malloc(sizeof(png_bytep) * height);
    for (int y = 0; y < height; y++) {
        row_pointers[y] = buf_ptr + y * png_get_rowbytes(png_ptr, info_ptr);
    }
    num_color_channel = compute_num_color_channel(png_ptr, info_ptr);
}

ImageInfo::~ImageInfo(){
    free(row_pointers);
    free(buf_ptr);
}

ImageInfo::ImageInfo(ImageInfo&& other) {
    buf_ptr = other.buf_ptr;
    row_pointers = other.row_pointers;
    color_type = other.color_type;
    bit_depth = other.bit_depth;
    width = other.width;
    height = other.height;
    number_of_passes = other.number_of_passes;
    num_color_channel = other.num_color_channel;
}
