#ifndef __ENUMS_HPP_INCLUDED__
#define __ENUMS_HPP_INCLUDED__

#include <string>

/// Represents the color state of a raster image.
enum RGB_STATE {
    BW,   ///< Black and white
    GRAY, ///< Grayscale
    RGB   ///< Red-Green-Blue (full color)
};

/// Represents the supported file types (PBM, PGM, PPM, BMP).
enum FileType {
    P1,  ///< Portable bitmap (ASCII)
    P2,  ///< Portable graymap (ASCII)
    P3,  ///< Portable pixmap (ASCII)
    P4,  ///< Portable bitmap (binary)
    P5,  ///< Portable graymap (binary)
    P6,  ///< Portable pixmap (binary)
    BM,  ///< BMP (binary only)
    FCOUNT ///< Total count of supported file types
};

/// File type strings corresponding to the FileType enum values.
const std::string fileTypes[FCOUNT] = { "P1", "P2", "P3", "P4", "P5", "P6", "BM" };

#endif // !__ENUMS_HPP_INCLUDED__