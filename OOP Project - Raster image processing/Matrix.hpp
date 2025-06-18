/*
	#### OOP Project - Raster image processing ####
			FMI OOP - Informatics, 2025
*/

#ifndef __MATRIX_HPP_INCLUDED__
#define __MATRIX_HPP_INCLUDED__

#include <vector>
#include "Enums.hpp"

class Image;

/// Represents a single RGB pixel using 8-bit values.
///
/// Combines all raster types:
/// | Description                          | Representation                         |
/// |--------------------------------------|----------------------------------------|
/// | Black & White                        | `r = g = b = 0` (black) or 255 (white) |
/// | Grayscale                            | `r = g = b = value`                    |
/// | Full RGB color		               | `r`, `g`, and `b` are distinct         |
struct Pixel { uint8_t r, g, b; };

/// A 2D matrix of RGB pixels representing image data.
class Matrix {
public:

	/// Default constructor initializing an empty matrix.
	Matrix() : height(0), width(0) {};

	/// Constructs a matrix of the specified dimensions with a base pixel value.
	/// @param height The height of the matrix (number of rows).
	/// @param width The width of the matrix (number of columns).
	/// @param baseValue The pixel value used to initialize the matrix.
	Matrix(size_t height, size_t width, const Pixel& baseValue = { WHITE, WHITE, WHITE } );

	void hFlip();		///< Horizontally flips the matrix.				 @throws std::bad_alloc();
	void vFlip();		///< Vertically flips the matrix.				 @throws std::bad_alloc();
	void rotateRight(); ///< Rotates the matrix 90 degrees to the right. @throws std::bad_alloc();
	void rotateLeft();  ///< Rotates the matrix 90 degrees to the left.  @throws std::bad_alloc();
	void rotate180();   ///< Rotates the matrix 180 degrees.			 @throws std::bad_alloc();

	/// Pastes another matrix onto this matrix at a specified position.
	/// 
	/// Empty space will be filled with white pixels
	/// @param other The matrix to paste.
	/// @param x The x-coordinate (column) for the paste.
	/// @param y The y-coordinate (row) for the paste.
	/// @returns A new matrix with the pasted result.
	/// @throws std::bad_alloc();
	Matrix pasteMatrix(const Matrix& other, size_t x, size_t y) const;

	size_t size() const { return data.size(); }  ///< Returns the total number of pixels in the matrix.
	size_t getWidth() const { return width; }	 ///< Returns the width of the matrix.
	size_t getHeight() const { return height; }  ///< Returns the height of the matrix.

public:
	Pixel operator () (size_t i1, size_t i2) const;  ///< Returns a copy of the pixel at the position.
	Pixel& operator () (size_t i1, size_t i2);		 ///< Returns a reference to the pixel at the position.

	/// Appends a new row of pixels to the matrix.
    /// @param row The row of pixels to append.
    /// @returns Reference to the modified matrix.
	/// @throws std::bad_alloc();
	Matrix& operator += (const std::vector<Pixel>& row);

private:
	static const size_t WHITE = 255; ///< Default white pixel value.

	std::vector<std::vector<Pixel>> data; ///< 2D vector of pixels.
	size_t width;                         ///< Matrix width.
	size_t height;                        ///< Matrix height.
};

/// Appends a row of pixels to a copy of the given matrix.
/// @param matrix The original matrix.
/// @param row The row of pixels to append.
/// @returns A new matrix with the row added.
/// @throws std::bad_alloc();
Matrix operator + (const Matrix& matrix, const std::vector<Pixel>& row);

#endif // !MATRIX_HPP