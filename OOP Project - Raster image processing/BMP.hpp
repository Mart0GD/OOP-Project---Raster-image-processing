/*
	#### OOP Project - Raster image processing ####
			FMI OOP - Informatics, 2025
*/

#ifndef __BMP_HPP_INCLUDED__
#define __BMP_HPP_INCLUDED__

#include "File.hpp"
#include "BMP_Header.hpp"

class Session;

/// Represents a BMP file.
/// 
/// supports full 24 bits per pixel RGB images.
class BMP : public File {
public:
	BMP(const BMPHeader& bmp_header,
		const std::string& filename, Matrix& matrix);

	virtual File* clone() const override { return new BMP(*this); }
	virtual Image* createImage(size_t index = 0) override;

	/// Saves the image to a BMP file in binary format.
	///
	/// The BMP format is **padded** so that each row's size in bytes is a multiple of 4.
	/// A new **BMPHeader** is constructed during the save operation based on the image's properties.
	///
	/// @param image The image to be saved.
	/// @param filename The output filename. If not specified, a default name is used.
	/// @returns `true` if the image is successfully saved; `false` otherwise.
	virtual bool saveImage(const Image& image, const std::string& filename = NO_SAVE_NAME) const override;
	virtual void printInfo() const override;

private:
	BMPHeader bmp_header; ///< Header containing BMP-specific metadata.
};


class BMPFileManager : public FileManager {
public:

	virtual bool canHandle(std::istream& is) const override;
	virtual File* create(std::istream& is, const std::string& filename) const override;
};

#endif // !__IMAGE_HPP_INCLUDED__

