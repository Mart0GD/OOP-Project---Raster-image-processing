/*
	#### OOP Project - Raster image processing ####
			FMI OOP - Informatics, 2025
*/

#ifndef __MATRIX_HPP_INCLUDED__
#define __MATRIX_HPP_INCLUDED__

#include <vector>
#include "Enums.hpp"

class Image;

struct Pixel { uint8_t r, g, b; };

class Matrix {
public:
	Matrix() : height(0), width(0) {};
	Matrix(size_t height, size_t width, const Pixel& baseValue = { WHITE, WHITE, WHITE } );

	void hFlip();
	void vFlip();
	void rotateRight();
	void rotate180();
	void rotateLeft();
	Matrix pasteMatrix(const Matrix& other, size_t x, size_t y) const;

	size_t size() const { return data.size(); }
	size_t getWidth() const { return width; }
	size_t getHeight() const { return height; }

public:
	Pixel operator () (size_t i1, size_t i2) const;
	Pixel& operator () (size_t i1, size_t i2);

	Matrix& operator += (const std::vector<Pixel>& row);

private:
	static const size_t WHITE = 255;

	std::vector<std::vector<Pixel>> data;
	size_t width, height;
};

Matrix operator + (const Matrix& matrix, const std::vector<Pixel>& row);

#endif // !MATRIX_HPP