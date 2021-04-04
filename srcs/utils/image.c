#include "../../includes/minirt.h"

// static void     transfer(int nb, unsigned char *src)
// {
//     src[0] = (unsigned char)(nb);
//     src[1] = (unsigned char)(nb >> 8);
//     src[2] = (unsigned char)(nb >> 16);
//     src[3] = (unsigned char)(nb >> 24);
// }

// static void     write_header_bmp(int size_f, int fd, int res_width, int res_height)
// {
//     unsigned char bitmap[54];

//     bitmap[0] = 'B';
//     bitmap[1] = 'M';
//     transfer(size_f, bitmap + 2);
//     bitmap[10]
// }