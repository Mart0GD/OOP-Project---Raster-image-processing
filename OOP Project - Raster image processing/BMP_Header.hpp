/*
	#### OOP Project - Raster image processing ####
			FMI OOP - Informatics, 2025
*/

#ifndef __BMP_HEADER_HPP_INCLUDED__
#define __BMP_HEADER_HPP_INCLUDED__

#include <cstdint>

// disables the padding so we can read the header on one go
#pragma pack(push, 1)

struct BMPHeader {

    // BMP
    uint16_t bfType = 0x4D42; // 'BM'
    uint32_t bfSize = 0;
    uint16_t bfReserved1 = 0;
    uint16_t bfReserved2 = 0;
    uint32_t bfOffBits = 54;

    // DIB
    uint32_t biSize = 40;
    int32_t biWidth = 0;
    int32_t biHeight = 0;
    uint16_t biPlanes = 1;
    uint16_t biBitCount = 24;
    uint32_t biCompression = 0;
    uint32_t biSizeImage = 0;
    int32_t biXPelsPerMeter = 0;
    int32_t biYPelsPerMeter = 0;
    uint32_t biClrUsed = 0;
    uint32_t biClrImportant = 0;
};

#pragma pack(pop)
#endif // !__BMP_HEADER_HPP_INCLUDED__

