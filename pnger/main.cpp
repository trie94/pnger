#include <png.h>

#include <iostream>

#include "imageLoader.h"
#include "imageProcessor.h"
#include "imageWriter.h"
#include "imageInfo.h"
#include "utils.h"
using namespace utils;

int main(int argc, char* argv[]) {
    if (argc != 3) {
        abort_("usage: program_name <file_in> <file_out>");
    }

    ImageLoader image_loader;
    ImageProcessor image_processor;
    ImageWriter image_writer;
    
    ImageInfo image_info = image_loader.read_png_file(argv[1]);
    image_processor.grayscale(image_info);
    image_processor.invert(image_info);
    image_writer.write_png_file(image_info, argv[2]);

    return 0;
}
