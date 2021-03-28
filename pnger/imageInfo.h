
#ifndef IMAGEINFO_H
#define IMAGEINFO_H
#include <png.h>

struct ImageInfo {
    ImageInfo(png_structp png_ptr, png_infop info_ptr, png_byte color_type, png_byte bit_depth, int width, int height, int number_of_passes);
    ImageInfo(const ImageInfo& other)=delete;
    ImageInfo(ImageInfo&& other);
    ~ImageInfo();
    ImageInfo& operator=(const ImageInfo& other)=delete;
public:
    const png_byte* get_buf_ptr() const { return buf_ptr; }
    png_byte* get_buf_ptr() { return buf_ptr; }
    const png_bytep* get_row_pointers() const { return row_pointers; }
    png_bytep* get_row_pointers() { return row_pointers; }
    int get_num_color_channel() const { return num_color_channel; }
    png_byte get_color_type() const { return color_type; }
    png_byte get_bit_depth() const { return bit_depth; }
    int get_width() const { return width; }
    int get_height() const { return height; }
    int get_number_of_passes() const { return number_of_passes; }
private:
    png_byte* buf_ptr = nullptr;
    png_bytep* row_pointers = nullptr;
    int num_color_channel = 0;
    
    png_byte color_type = 0;
    png_byte bit_depth = 0;
    int width = 0, height = 0;
    int number_of_passes = 0;
};
#endif
