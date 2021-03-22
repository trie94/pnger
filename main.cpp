#include <png.h>

#include <iostream>

png_structp png_ptr;
png_infop info_ptr;

int x, y;
int width, height;
png_byte color_type;
png_byte bit_depth;
int number_of_passes;
png_byte* buf_ptr;
png_bytep* row_pointers;
int num_color_channel;

void abort_(const char* s, ...) {
    va_list args;
    va_start(args, s);
    vfprintf(stderr, s, args);
    fprintf(stderr, "\n");
    va_end(args);
    abort();
}

void read_png_file(char* file_name) {
    // png file has 8 byte file header signature.
    // http://www.libpng.org/pub/png/spec/1.2/PNG-Rationale.html#R.PNG-file-signature
    int header_size = 8;
    png_byte header[header_size];

    // rb stands for read as binary file.
    FILE* file_ptr = fopen(file_name, "rb");
    if (file_ptr == nullptr) {
        abort_("file %s could not be opened for reading.", file_name);
    }
    fread(header, 1, header_size, file_ptr);
    if (png_sig_cmp(header, 0, header_size)) {
        abort_("file %s is not in png format.", file_name);
    }

    png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr,
                                     nullptr);
    if (png_ptr == nullptr) {
        abort_("png_create_read_struct failed.");
    }
    info_ptr = png_create_info_struct(png_ptr);
    if (info_ptr == nullptr) {
        abort_("png_create_info_struct failed.");
    }

    if (setjmp(png_jmpbuf(png_ptr))) {
        abort_("[read_png_file] error during init_io");
    }

    png_init_io(png_ptr, file_ptr);
    png_set_sig_bytes(png_ptr, header_size);

    png_read_info(png_ptr, info_ptr);

    width = png_get_image_width(png_ptr, info_ptr);
    height = png_get_image_height(png_ptr, info_ptr);
    color_type = png_get_color_type(png_ptr, info_ptr);
    bit_depth = png_get_bit_depth(png_ptr, info_ptr);

    number_of_passes = png_set_interlace_handling(png_ptr);
    png_read_update_info(png_ptr, info_ptr);

    if (setjmp(png_jmpbuf(png_ptr))) {
        abort_("[read_png_file] error during read_image");
    }

    buf_ptr = (png_byte*)malloc(png_get_rowbytes(png_ptr, info_ptr) * height);
    row_pointers = (png_bytep*)malloc(sizeof(png_bytep) * height);

    for (y = 0; y < height; y++) {
        row_pointers[y] = buf_ptr + y * png_get_rowbytes(png_ptr, info_ptr);
    }

    png_read_image(png_ptr, row_pointers);
    fclose(file_ptr);
}

void write_png_file(char* file_name) {
    /* create file */
    FILE* file_ptr = fopen(file_name, "wb");
    if (!file_ptr) {
        abort_("[write_png_file] file %s could not be opened for writing",
               file_name);
    }

    png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

    if (!png_ptr) abort_("[write_png_file] png_create_write_struct failed");

    info_ptr = png_create_info_struct(png_ptr);
    if (!info_ptr) abort_("[write_png_file] png_create_info_struct failed");

    if (setjmp(png_jmpbuf(png_ptr)))
        abort_("[write_png_file] error during init_io");

    png_init_io(png_ptr, file_ptr);

    if (setjmp(png_jmpbuf(png_ptr)))
        abort_("[write_png_file] error during writing header");

    png_set_IHDR(png_ptr, info_ptr, width, height, bit_depth, color_type,
                 PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_BASE,
                 PNG_FILTER_TYPE_BASE);

    png_write_info(png_ptr, info_ptr);

    /* write bytes */
    if (setjmp(png_jmpbuf(png_ptr)))
        abort_("[write_png_file] error during writing bytes");

    png_write_image(png_ptr, row_pointers);

    /* end write */
    if (setjmp(png_jmpbuf(png_ptr)))
        abort_("[write_png_file] error during end of write");

    png_write_end(png_ptr, NULL);

    /* cleanup heap allocation */
    free(row_pointers);
    free(buf_ptr);
    png_destroy_write_struct(&png_ptr, &info_ptr);

    fclose(file_ptr);
}

void check_color_type() {
    switch (png_get_color_type(png_ptr, info_ptr)) {
        case PNG_COLOR_TYPE_RGB:
            num_color_channel = 3;
            break;

        case PNG_COLOR_TYPE_RGBA:
            num_color_channel = 4;
            break;

        default:
            abort_("not supported color type.");
    }
}

void grayscale() {
    check_color_type();
    for (y = 0; y < height; y++) {
        png_byte* row = row_pointers[y];
        for (x = 0; x < width; x++) {
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

void invert() {
    check_color_type();
    for (y = 0; y < height; y++) {
        png_byte* row = row_pointers[y];
        for (x = 0; x < width; x++) {
            png_byte* ptr = &(row[x * num_color_channel]);
            ptr[0] = 255 - ptr[0];
            ptr[1] = 255 - ptr[1];
            ptr[2] = 255 - ptr[2];
        }
    }
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        abort_("usage: program_name <file_in> <file_out>");
    }
    read_png_file(argv[1]);

    grayscale();
    invert();

    // we need read struct for do image processing.
    png_destroy_read_struct(&png_ptr, &info_ptr, nullptr);
    write_png_file(argv[2]);

    return 0;
}