#include <fstream>
#include <iostream>
#include <assert.h>

#include "Image.hpp"
#include "File.hpp"
#include "Session.hpp"
#include "Helpers.hpp"

Image::Image(const Matrix& matrix, File* file, size_t commandIndex)
	: matrix(matrix), file(file), startCommandIndex(commandIndex)
{
	if (!file) throw std::invalid_argument("file should not be null pointer!");

	// strongest criteria check first
	if (checkMono()) state = BW; 
	else if (checkGrey()) state = GRAY; 
	else state = RGB;

	resetContext();
}
Image::~Image() noexcept {
	delete (File*)file;
}

Image::Image(const Image& other) 
{
	copy(*this, other);
	file = other.file->clone();
}
Image& Image::operator=(const Image& other) {
	if (this == &other) return *this;

	Image copy(other);
	*this = std::move(copy);

	return *this;
}

Image::Image(Image&& other) noexcept {
	copy(*this, other);
	file = other.file;
	other.file = nullptr;
}
Image& Image::operator=(Image&& other) noexcept {
	if (this == &other) return *this;

	copy(*this, other);
	std::swap(file, other.file);

	return *this;
}

void Image::grayscale() {
	if (state == BW || state == GRAY) return;

	for (int y = 0; y < matrix.getHeight(); ++y)
	{
		for (int x = 0; x < matrix.getWidth(); ++x)
		{
			Pixel& pixel = matrix(y, x);
			uint8_t newValue = (pixel.r + pixel.g + pixel.b) / 3;

			pixel = { newValue, newValue, newValue };
		}
	}

	state = GRAY;
}
void Image::monochrome() {
	if (state == BW) return;
	const int32_t treshold = 128;

	grayscale();
	for (int y = 0; y < matrix.getHeight(); ++y)
	{
		for (int x = 0; x < matrix.getWidth(); ++x)
		{
			Pixel& pixel = matrix(y, x);
			uint8_t newValue = pixel.r >= treshold ? 255 : 0;

			pixel = { newValue, newValue, newValue };
		}
	}

	state = BW;
}
void Image::negative() {

	const uint8_t negatingValue = 255;

	for (int y = 0; y < matrix.getHeight(); y++)
	{
		for (int x = 0; x < matrix.getWidth(); x++)
		{
			Pixel& pixel = matrix(y, x);

			pixel.r = negatingValue - pixel.r;
			pixel.g = negatingValue - pixel.g;
			pixel.b = negatingValue - pixel.b;
		}
	}
}

Image* Image::paste(const Image* other, size_t posX, size_t posY) {

	try
	{
		Matrix matrix = this->matrix.pasteMatrix(other->getMatrix(), posX, posY);

		// we use the wider format
		File* file = state >= other->state
					 ? this->file->clone()
					 : other->file->clone();

		std::string name = "pasted";
		createFilename(file->getFilename(), name);
		file->setFilename(name);

		Image* image = file->createImage();
		std::swap(image->getMatrix(), matrix);
		return image;
	}
	catch (const std::exception& e)
	{
		std::cout << e.what();
		return nullptr;
	}
}

bool Image::checkGrey() {
	for (int y = 0; y < matrix.getHeight(); y++)
	{
		for (int x = 0; x < matrix.getWidth(); x++)
		{
			const Pixel& pixel = matrix(y, x);
			if (pixel.r != pixel.g || pixel.r != pixel.b) return false;
		}
	}

	return true;
}
bool Image::checkMono() {
	const int32_t white = 255;
	const int32_t black = 0;

	for (int y = 0; y < matrix.getHeight(); y++)
	{
		for (int x = 0; x < matrix.getWidth(); x++)
		{
			const Pixel& pixel = matrix(y, x);
			if ((pixel.r == white && pixel.g == white && pixel.b == white) ||
				(pixel.r == black && pixel.g == black && pixel.b == black)) continue;

			return false;
		}
	}

	return true;
}

void Image::resetContext() {
	context.state = state;
	context.hFlipped = context.vFlipped = context.negative = false;
	context.rotations = 0;
	context.direction = 1;
}
void Image::setStartCommandIndex(size_t index) {
	startCommandIndex = index;
}

void Image::copy(Image& image, const Image& other) 
{
	image.startCommandIndex = other.startCommandIndex;
	image.context = other.context;
	image.matrix = other.matrix;
	image.state = other.state;

}