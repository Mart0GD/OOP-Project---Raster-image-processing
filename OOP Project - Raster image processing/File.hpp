/*
	#### OOP Project - Raster image processing ####
			FMI OOP - Informatics, 2025
*/

#ifndef __FILE_HPP_INCLUDED__
#define __FILE_HPP_INCLUDED__

#include <string>
#include <vector>

#include "Enums.hpp"
#include "Image.hpp"
#include "Matrix.hpp"
#include "Helpers.hpp"

/// Abstract base class representing a raster image file.
///
/// Holds the functionallity to save, create and display the info for a bmp raster image
class File {
public:

	/// Constructs a file with a given filename and matrix data.
	///
	/// @param filename string value representing the filename 
	/// @param matrix pixel data for image creation
	/// @throws std::invalid_argument when an empty name is passed
	File(const std::string& filename, const Matrix& matrix);
	virtual File* clone() const = 0; ///< Creates a deep copy of the file. @throws std::bad_alloc()

	/// Creates an image object linked to this file.
	/// @param commandIndex The index of the command history where the image begins.
	/// @throws std::bad_alloc()
	virtual Image* createImage(size_t commandIndex = 0) = 0;

	/// Saves the provided image to a file.
	/// 
	/// The user can provide a name for the saved file 
	/// otherwise a default value representing the current save time will be applied
	/// @param image The image to save.
	/// @param filename The output file name (optional).
	virtual bool saveImage(const Image& image, const std::string& filename = NO_SAVE_NAME) const = 0;

	/// Prints file-specific information on the console.
	/// 
	/// ### Example
	/// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	/// Files in session:
	/// image1 - portable pixmap format
	///	image3 - 32bit Bitmap
	/// (...)
	/// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	virtual void printInfo() const = 0;

	std::string getFilename() const { return filename; } ///< Returns the file's name.
	void setFilename(const std::string& name) { filename = name; } ///< Sets the file's name.

protected:
	std::string filename; ///< The name of the file.
	Matrix matrix;        ///< The image matrix data associated with the file.
};


/// Interface for managing file creation and format identification.
class FileManager {
public:
	FileManager();
	virtual ~FileManager() = default;

	/// Checks if the manager can handle the provided input in the file stream.
	/// @param is Input stream to check.
	virtual bool canHandle(std::istream& is) const = 0;

	/// Creates a file from the input stream and given filename.
	/// @param is The input stream.
	/// @param filename The name of the file to create.
	virtual File* create(std::istream& is, const std::string& filename) const = 0;
};

#endif // !__FILE_HPP_INCLUDED__