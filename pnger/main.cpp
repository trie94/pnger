#include <png.h>

#include <iostream>

#include "imageLoader.h"
#include "utils.h"
using namespace utils;

// void write_png_file(char* file_name) {
//     /* create file */
//     FILE* file_ptr = fopen(file_name, "wb");
//     if (!file_ptr) {
//         abort_("[write_png_file] file %s could not be opened for writing",
//                file_name);
//     }

//     png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL,
//     NULL);

//     if (!png_ptr) abort_("[write_png_file] png_create_write_struct failed");

//     info_ptr = png_create_info_struct(png_ptr);
//     if (!info_ptr) abort_("[write_png_file] png_create_info_struct failed");

//     if (setjmp(png_jmpbuf(png_ptr)))
//         abort_("[write_png_file] error during init_io");

//     png_init_io(png_ptr, file_ptr);

//     if (setjmp(png_jmpbuf(png_ptr)))
//         abort_("[write_png_file] error during writing header");

//     png_set_IHDR(png_ptr, info_ptr, width, height, bit_depth, color_type,
//                  PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_BASE,
//                  PNG_FILTER_TYPE_BASE);

//     png_write_info(png_ptr, info_ptr);

//     /* write bytes */
//     if (setjmp(png_jmpbuf(png_ptr)))
//         abort_("[write_png_file] error during writing bytes");

//     png_write_image(png_ptr, row_pointers);

//     /* end write */
//     if (setjmp(png_jmpbuf(png_ptr)))
//         abort_("[write_png_file] error during end of write");

//     png_write_end(png_ptr, NULL);

//     /* cleanup heap allocation */
//     free(row_pointers);
//     free(buf_ptr);
//     png_destroy_write_struct(&png_ptr, &info_ptr);

//     fclose(file_ptr);
// }

int main(int argc, char* argv[]) {
    if (argc != 3) {
        abort_("usage: program_name <file_in> <file_out>");
    }

    ImageLoader imageLoader;
    imageLoader.read_png_file(argv[1]);
    // read_png_file(argv[1]);

    // grayscale();
    // invert();

    // // we need read struct for do image processing.
    // png_destroy_read_struct(&png_ptr, &info_ptr, nullptr);
    // write_png_file(argv[2]);

    return 0;
}
