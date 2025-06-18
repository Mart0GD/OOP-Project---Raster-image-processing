/*
	#### OOP Project - Raster image processing ####
			FMI OOP - Informatics, 2025
*/

#ifndef __BMP_HEADER_HPP_INCLUDED__
#define __BMP_HEADER_HPP_INCLUDED__

#include <cstdint>

// disables the padding so we can read the header on one go
#pragma pack(push, 1)

/// Struct representing a BMP file header using the BITMAPINFOHEADER format (54 bytes) 
struct BMPHeader {

    /// BMP file header
    uint16_t bfType = 0x4D42;       ///< The header field used to identify the format
    uint32_t bfSize = 0;            ///< The size of the BMP file in bytes
    uint16_t bfReserved1 = 0;       ///< Reserved.
    uint16_t bfReserved2 = 0;       ///< Reserved. 
    uint32_t bfOffBits = 54;        ///< starting address of the pixel array.

    // DIB
    uint32_t biSize = 40;           ///< the size of this header, in bytes (40)
    int32_t biWidth = 0;            ///< the bitmap width in pixels (signed integer)
    int32_t biHeight = 0;           ///< the bitmap height in pixels (signed integer)
    uint16_t biPlanes = 1;          ///< the number of color planes (must be 1)
    uint16_t biBitCount = 24;       ///< the number of bits per pixel, which is the color depth of the image.
    uint32_t biCompression = 0;     ///< the compression method being used.
    uint32_t biSizeImage = 0;       ///< the image size. This is the size of the raw bitmap data.
    int32_t biXPelsPerMeter = 0;    ///< the horizontal resolution of the image.
    int32_t biYPelsPerMeter = 0;    ///< the vertical resolution of the image
    uint32_t biClrUsed = 0;         ///< the number of colors in the color palette, or 0 to default to 2^n
    uint32_t biClrImportant = 0;    ///< the number of important colors used, generally ignored
};

#pragma pack(pop)
#endif // !__BMP_HEADER_HPP_INCLUDED__

