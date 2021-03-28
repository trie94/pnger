//
//  utils.cpp
//  pnger
//
//  Created by Yein Jo on 3/27/21.
//

#include <stdio.h>
#include <iostream>
namespace utils{
void abort_(const char* s, ...) {
    va_list args;
    va_start(args, s);
    vfprintf(stderr, s, args);
    fprintf(stderr, "\n");
    va_end(args);
    abort();
}

}
