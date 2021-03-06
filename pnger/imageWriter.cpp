//
//  imageWriter.cpp
//  pnger
//
//  Created by Yein Jo on 3/28/21.
//

#include "imageWriter.h"
#include "utils.h"
#include <iostream>
using namespace utils;

ImageWriter::ImageWriter(){
    png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL,
    NULL);

    if (!png_ptr) abort_("[write_png_file] png_create_write_struct failed");

    info_ptr = png_create_info_struct(png_ptr);
    if (!info_ptr) abort_("[write_png_file] png_create_info_struct failed");
}

ImageWriter::~ImageWriter(){
    png_destroy_write_struct(&png_ptr, &info_ptr);
}

 void ImageWriter::write_png_file(const ImageInfo& image_info, char* file_name) {
     /* create file */
     FILE* file_ptr = fopen(file_name, "wb");
     if (!file_ptr) {
         abort_("[write_png_file] file %s could not be opened for writing",
                file_name);
     }
     
     if (setjmp(png_jmpbuf(png_ptr)))
         abort_("[write_png_file] error during init_io");

     png_init_io(png_ptr, file_ptr);

     if (setjmp(png_jmpbuf(png_ptr)))
         abort_("[write_png_file] error during writing header");

     png_set_IHDR(png_ptr, info_ptr, image_info.get_width(), image_info.get_height(), image_info.get_bit_depth(), image_info.get_color_type(),
                  PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_BASE,
                  PNG_FILTER_TYPE_BASE);

     png_write_info(png_ptr, info_ptr);

     /* write bytes */
     if (setjmp(png_jmpbuf(png_ptr)))
         abort_("[write_png_file] error during writing bytes");

     png_write_image(png_ptr, const_cast<png_bytep*>(image_info.get_row_pointers()));

     /* end write */
     if (setjmp(png_jmpbuf(png_ptr)))
         abort_("[write_png_file] error during end of write");

     png_write_end(png_ptr, NULL);

     fclose(file_ptr);
 }
