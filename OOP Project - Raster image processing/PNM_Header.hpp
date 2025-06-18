/*
	#### OOP Project - Raster image processing ####
			FMI OOP - Informatics, 2025
*/

#ifndef __HEADER_HPP_INCLUDED__
#define __HEADER_HPP_INCLUDED__

#include <string>

/// Struct representing a PNM file header
struct PNM_Header {
	std::string format{};		///< Identifier -> P1-P6
	int32_t width{};			///< the width of the pixel matrix
	int32_t height{};			///< the height of the pixel matrix
	uint32_t maxValue = 1;		///< max pixel value (1 by default for pbm)
};

#endif // !__LOAD_COMMAND_HPP_INCLUDED__
