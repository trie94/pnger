#include "imageLoader.h"

#include <iostream>
#include "utils.h"
using namespace utils;

ImageInfo ImageLoader::read_png_file(char* file_name) {
    // png file has 8 byte file header signature.
    // http://www.libpng.org/pub/png/spec/1.2/PNG-Rationale.html#R.PNG-file-signature
    int header_size = 8;
    png_byte header[header_size];
    ImageInfo result = ImageInfo();

    // rb stands for read as binary file.
    FILE* file_ptr = fopen(file_name, "rb");
    if (file_ptr == nullptr) {
        abort_("file %s could not be opened for reading.", file_name);
    }
    fread(header, 1, header_size, file_ptr);
    if (png_sig_cmp(header, 0, header_size)) {
        abort_("file %s is not in png format.", file_name);
    }

    png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, nullptr,
                                                 nullptr, nullptr);
    if (png_ptr == nullptr) {
        abort_("png_create_read_struct failed.");
    }
    png_infop info_ptr = png_create_info_struct(png_ptr);
    if (info_ptr == nullptr) {
        abort_("png_create_info_struct failed.");
    }

    if (setjmp(png_jmpbuf(png_ptr))) {
        abort_("[read_png_file] error during init_io");
    }

    png_init_io(png_ptr, file_ptr);
    png_set_sig_bytes(png_ptr, header_size);

    png_read_info(png_ptr, info_ptr);

    int width = png_get_image_width(png_ptr, info_ptr);
    int height = png_get_image_height(png_ptr, info_ptr);
    png_byte color_type = png_get_color_type(png_ptr, info_ptr);
    png_byte bit_depth = png_get_bit_depth(png_ptr, info_ptr);

    int number_of_passes = png_set_interlace_handling(png_ptr);
    png_read_update_info(png_ptr, info_ptr);

    if (setjmp(png_jmpbuf(png_ptr))) {
        abort_("[read_png_file] error during read_image");
    }

    png_byte* buf_ptr =
        (png_byte*)malloc(png_get_rowbytes(png_ptr, info_ptr) * height);
    png_bytep* row_pointers = (png_bytep*)malloc(sizeof(png_bytep) * height);

    for (int y = 0; y < height; y++) {
        row_pointers[y] = buf_ptr + y * png_get_rowbytes(png_ptr, info_ptr);
    }

    png_read_image(png_ptr, row_pointers);
    fclose(file_ptr);

    result.buf_ptr = buf_ptr;
    result.row_pointers = row_pointers;
    result.png_ptr = png_ptr;
    result.info_ptr = info_ptr;
    result.color_type = color_type;
    result.bit_depth = bit_depth;
    result.width = width;
    result.height = height;
    result.number_of_passes = number_of_passes;

    return result;
}
