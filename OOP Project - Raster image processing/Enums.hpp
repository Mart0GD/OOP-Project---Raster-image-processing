#ifndef __ENUMS_HPP_INCLUDED__
#define __ENUMS_HPP_INCLUDED__

#include <string>

enum RGB_STATE {
	BW,
	GRAY,
	RGB
};

enum FileType {
	P1,
	P2,
	P3,
	P4,
	P5,
	P6,
	BM, // only binary
	FCOUNT
};

const std::string fileTypes[FCOUNT] =
{ "P1", "P2", "P3", "P4", "P5", "P6", "BM"};

#endif // !__ENUMS_HPP_INCLUDED__