/*
	#### OOP Project - Raster image processing ####
			FMI OOP - Informatics, 2025
*/

#ifndef __HEADER_HPP_INCLUDED__
#define __HEADER_HPP_INCLUDED__

#include <string>

struct PNM_Header {
	std::string format{}; // P1-P6
	int32_t width{};
	int32_t height{};
	uint32_t maxValue = 1; // default for pbm
};

#endif // !__LOAD_COMMAND_HPP_INCLUDED__
