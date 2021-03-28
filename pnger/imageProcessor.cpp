#include "imageProcessor.h"
#include "utils.h"
using namespace utils;

 int ImageProcessor::get_num_color_channel(png_structp png_ptr, png_infop info_ptr) {
     switch (png_get_color_type(png_ptr, info_ptr)) {
         case PNG_COLOR_TYPE_RGB:
             return 3;

         case PNG_COLOR_TYPE_RGBA:
             return 4;

         default:
              abort_("not supported color type.");
     }
     return 0;
 }

 void ImageProcessor::grayscale(ImageInfo image_info) {
     int num_color_channel = get_num_color_channel(image_info.png_ptr, image_info.info_ptr);
     for (int y = 0; y < image_info.height; y++) {
         png_byte* row = image_info.row_pointers[y];
         for (int x = 0; x < image_info.width; x++) {
             png_byte* ptr = &(row[x * num_color_channel]);
             unsigned char lum =
                 (unsigned char)(0.2126 * ptr[0] + 0.7152 * ptr[1] +
                                 0.0722 * ptr[2]);
             ptr[0] = lum;
             ptr[1] = lum;
             ptr[2] = lum;
         }
     }
 }

 void ImageProcessor::invert(ImageInfo image_info) {
     int num_color_channel = get_num_color_channel(image_info.png_ptr, image_info.info_ptr);
     for (int y = 0; y < image_info.height; y++) {
         png_byte* row = image_info.row_pointers[y];
         for (int x = 0; x < image_info.width; x++) {
             png_byte* ptr = &(row[x * num_color_channel]);
             ptr[0] = 255 - ptr[0];
             ptr[1] = 255 - ptr[1];
             ptr[2] = 255 - ptr[2];
         }
     }
 }
