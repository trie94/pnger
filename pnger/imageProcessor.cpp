
// void check_color_type() {
//     switch (png_get_color_type(png_ptr, info_ptr)) {
//         case PNG_COLOR_TYPE_RGB:
//             num_color_channel = 3;
//             break;

//         case PNG_COLOR_TYPE_RGBA:
//             num_color_channel = 4;
//             break;

//         default:
//             // abort_("not supported color type.");
//     }
// }

// void grayscale() {
//     check_color_type();
//     for (y = 0; y < height; y++) {
//         png_byte* row = row_pointers[y];
//         for (x = 0; x < width; x++) {
//             png_byte* ptr = &(row[x * num_color_channel]);
//             unsigned char lum =
//                 (unsigned char)(0.2126 * ptr[0] + 0.7152 * ptr[1] +
//                                 0.0722 * ptr[2]);
//             ptr[0] = lum;
//             ptr[1] = lum;
//             ptr[2] = lum;
//         }
//     }
// }

// void invert() {
//     check_color_type();
//     for (y = 0; y < height; y++) {
//         png_byte* row = row_pointers[y];
//         for (x = 0; x < width; x++) {
//             png_byte* ptr = &(row[x * num_color_channel]);
//             ptr[0] = 255 - ptr[0];
//             ptr[1] = 255 - ptr[1];
//             ptr[2] = 255 - ptr[2];
//         }
//     }
// }
