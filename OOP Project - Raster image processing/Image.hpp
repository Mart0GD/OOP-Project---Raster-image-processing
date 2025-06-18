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

/// Base class for every raster image
class Image {
public:

	/// Constructs an image with a given matrix, file and command index.
	/// 
	/// @param matrix The pixel matrix for the image.
	/// @param file The file object associated with this image's creation and saving
	/// @param commandIndex The index in the command stack when the image was loaded.
	/// @throws std::invalid_argument if the file is a null pointer
	Image(const Matrix& matrix, File* file, size_t commandIndex);
	~Image() noexcept;					 

	Image(const Image& other);			 
	Image& operator=(const Image& other);

	Image(Image&& other) noexcept; 			  
	Image& operator=(Image&& other) noexcept; 

	/// Applies grayscale transformation to the image 
	/// 
	/// Only works if the image isn't gray already
	/// uses the avearge color value technique (r + g + b) / 3
	void grayscale();

	/// Applies monochrome (black-and-white) transformation to the image 
	/// 
	/// Only works if the image isn' black and white already
	/// first calls grayscale than bases on a value decides wheater a pixel is black or white
	void monochrome();

	/// Applies negative transformation to the image.
	///
	/// flips every pixel value in the matrix
	void negative();

	/// Pastes this image onto another at the given position.
	/// 
	/// the image format is based on wider format
	/// @param other The image to paste.
	/// @param posX The x-coordinate where the image should be pasted.
	/// @param posY The y-coordinate where the image should be pasted.
	/// @returns A pointer to the new, resulting image or null pointer on fail.
	/// ### Example
	/// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ .cpp
	/// //... we have two images:
	/// // image1 --> bmp
	/// // image2 --> pgm
	/// 
	/// Image* pasted = image1.paste(image2, 0, 0); // Pasted will be a bmp
	/// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	Image* paste(const Image* other, size_t posX, size_t posY);

	/// Resets the image's manipulation context.
	void resetContext();

public:

	const File* getFile() const { return file; }		  ///< Gets the associated file object.

	Matrix& getMatrix() { return matrix; }				  ///< Gets a reference to the image matrix (modifiable).
	const Matrix& getMatrix() const { return matrix; }	  ///< Gets a const reference to the image matrix.
	
	const Context& getContext() const { return context; } ///< Gets a const reference to the image context.
	Context& getContext() { return context; }			  ///< Gets a modifiable reference to the image context.

	void setStartCommandIndex(size_t index);			  ///< Sets the index of start command

	
	size_t getStartCommandIndex() const { return startCommandIndex; } ///< Gets the index of start command
	RGB_STATE getState() const { return state; }					  ///< Gets the RGB state of the image.

private:
	bool checkGrey(); ///< Checks if the image can be considered grayscale.
	bool checkMono(); ///< Checks if the image can be considered monochrome.

	/// Copies the content of another image into this one.
	///
	/// used inside the copy constructor and assignment operator
	void copy(Image& image, const Image& other); 

private:
	Matrix matrix;               ///< The pixel matrix representing the image.
	File* file;                  ///< Pointer to the file that owns this image.
	Context context;             ///< Context holding transformation data.
	size_t startCommandIndex;    ///< Index of the command when the image was loaded.
	RGB_STATE state;             ///< The color state of the image (BW, GRAY, RGB).
};


#endif // !__IMAGE_HPP_INCLUDED__

