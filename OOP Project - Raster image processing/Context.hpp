/*
	#### OOP Project - Raster image processing ####
			FMI OOP - Informatics, 2025
*/

#ifndef __CONTEXT_HPP_INCLUDED__
#define __CONTEXT_HPP_INCLUDED__

#include "Enums.hpp"
class Matrix;

/// Context struct used to store information about image transformations and manipulation
///
/// keeps values for every characteristic that can be manipulated inside an image
struct Context {
	RGB_STATE state;
	bool vFlipped, hFlipped, negative;
	int32_t rotations , direction; 
};


#endif // !__CONTEXT_HPP_INCLUDED__
