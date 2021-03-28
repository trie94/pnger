#ifndef IMAGEPROCESSOR_H
#define IMAGEPROCESSOR_H
#include <png.h>

class imageProcessor {
   private:
    /* data */
   public:
    imageProcessor(/* args */);
    ~imageProcessor();
    void check_color_type();
    void grayscale();
    void invert();
};

imageProcessor::imageProcessor(/* args */) {}

imageProcessor::~imageProcessor() {}

#endif