#include "Matrix.hpp"
#include "Image.hpp"
#include "File.hpp"
#include <iostream>

Matrix::Matrix(size_t height, size_t width, const Pixel& baseValue)
	: width(width), height(height)
{
	this->data = std::vector<std::vector<Pixel>>(height, std::vector<Pixel>(width, baseValue)); // can throw
}
 
void Matrix::hFlip() {

	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width / 2; x++)
			std::swap(data[y][x], data[y][width - x - 1]);
	}
}
void Matrix::vFlip() {
	for (int y = 0; y < height / 2; y++)
		std::swap(data[y], data[height - y - 1]);
}

void Matrix::rotateLeft() {
	Matrix rotated(width, height);

	for (size_t y = 0; y < height; ++y) {
		for (size_t x = 0; x < width; ++x) {
			rotated(x, height - 1 - y) = data[y][x];
		}
	}

	std::swap(width, height);
	std::swap(*this, rotated);
}
void Matrix::rotateRight() {
	Matrix rotated(width, height);

	for (size_t y = 0; y < height; ++y) {
		for (size_t x = 0; x < width; ++x) {
			rotated(width - 1 - x, y) = data[y][x];
		}
	}

	std::swap(width, height);
	std::swap(*this, rotated);
}
void Matrix::rotate180() {
	rotateRight();
	rotateRight();
}

Matrix Matrix::pasteMatrix(const Matrix& dest, size_t x, size_t y) const {
	const int32_t white = 255;

	Matrix srcMatrix(*this);

	// get the biggest dimensions
	size_t maxWidth = std::max(dest.getWidth(), width + x);
	size_t maxHeight = std::max(dest.getHeight(), height + y);

	// create the matrix --> filled with white
	Matrix resized(maxHeight, maxWidth);

	// paste the old one
	for (size_t i = 0; i < dest.getHeight(); ++i) {
		for (size_t ii = 0; ii < dest.getWidth(); ++ii) {
			resized(i, ii) = dest(i, ii);
		}
	}

	// paste the new one
	for (size_t i = 0; i < height; ++i) {
		for (size_t j = 0; j < width; ++j) {
			resized(y + i, x + j) = srcMatrix(i, j);
		}
	}

	return resized;
}

Pixel Matrix::operator () (size_t i1, size_t i2) const {
	if (i1 >= height || i2 >= width)
		throw std::out_of_range("invalid index!\n");

	return data[i1][i2];
}
Pixel& Matrix::operator () (size_t i1, size_t i2) {
	if (i1 >= height || i2 >= width)
		throw std::out_of_range("invalid index!\n");

	return data[i1][i2];
}

Matrix& Matrix::operator +=(const std::vector<Pixel>& row) { data.push_back(row); return *this; }
Matrix operator + (const Matrix& matrix, const std::vector<Pixel>& row) {
	Matrix copy(matrix);

	copy += row;
	return copy;
}