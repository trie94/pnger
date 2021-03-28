#include "imageProcessor.h"
#include "utils.h"
using namespace utils;

 void ImageProcessor::grayscale(ImageInfo& image_info) {
     for (int y = 0; y < image_info.get_height(); y++) {
         png_byte* row = image_info.get_row_pointers()[y];
         for (int x = 0; x < image_info.get_width(); x++) {
             png_byte* ptr = &(row[x * image_info.get_num_color_channel()]);
             unsigned char lum =
                 (unsigned char)(0.2126 * ptr[0] + 0.7152 * ptr[1] +
                                 0.0722 * ptr[2]);
             ptr[0] = lum;
             ptr[1] = lum;
             ptr[2] = lum;
         }
     }
 }

 void ImageProcessor::invert(ImageInfo& image_info) {
     for (int y = 0; y < image_info.get_height(); y++) {
         png_byte* row = image_info.get_row_pointers()[y];
         for (int x = 0; x < image_info.get_width(); x++) {
             png_byte* ptr = &(row[x * image_info.get_num_color_channel()]);
             ptr[0] = 255 - ptr[0];
             ptr[1] = 255 - ptr[1];
             ptr[2] = 255 - ptr[2];
         }
     }
 }
