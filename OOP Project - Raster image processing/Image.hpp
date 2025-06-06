/*
	#### OOP Project - Raster image processing ####
			FMI OOP - Informatics, 2025
*/

#ifndef __IMAGE_HPP_INCLUDED__
#define __IMAGE_HPP_INCLUDED__

#include "Matrix.hpp"
#include "Context.hpp"
#include "Session.hpp"

class File;

//Base class for every raster image
class Image {
public:

	// we pass the matrix by ref in order to synch it with the file
	Image(const Matrix& matrix, File* file, size_t commandIndex);
	~Image() noexcept;

	Image(const Image& other);
	Image& operator=(const Image& other);

	Image(Image&& other) noexcept;
	Image& operator=(Image&& other) noexcept;

	void grayscale();
	void monochrome();
	void negative();

	Image* paste(const Image* other, size_t posX, size_t posY);

	void resetContext();

public:

	const File* getFile() const { return file; }

	Matrix& getMatrix() { return matrix; } // we will be changing it
	const Matrix& getMatrix() const { return matrix; } // overload for saving 

	const Context& getContext() const { return context; }
	Context& getContext() { return context; }

	void setStartCommandIndex(size_t index);
	size_t getStartCommandIndex() const { return startCommandIndex; }

	RGB_STATE getState() const { return state; }

private:
	bool checkGrey();
	bool checkMono();

	void copy(Image& image, const Image& other);

private:
	Matrix matrix;

	File* file;

	Context context;
	size_t startCommandIndex;
	RGB_STATE state;
};


#endif // !__IMAGE_HPP_INCLUDED__

