/*
	#### OOP Project - Raster image processing ####
			FMI OOP - Informatics, 2025
*/

#ifndef __PBM_HPP_INCLUDED__
#define __PBM_HPP_INCLUDED__

#include <string>
#include <vector>

#include "File.hpp"
#include "PNM_Header.hpp"

class Session;

/// Represent a Portable bitmap file
///
/// Supports only black and white images
///	- 0 is black
///	- 1 is white
class PBM : public File{
public:
	PBM(const PNM_Header& header, 
		const std::string& filename, const Matrix& matrix);

	virtual File* clone() const override { return new PBM(*this); }
	virtual Image* createImage(size_t index = 0) override;

	/// Checks the identifier and saves the file in either binary or ASCII format
	/// @param image The image to save.
	/// @param filename The output filename. If not provided, uses a default.
	virtual bool saveImage(const Image& image, const std::string& filename = NO_SAVE_NAME) const override;
	virtual void printInfo() const override;

private:

	/// Saves the image's pixel data in compressed binary format.
	///
	/// Uses the **P4 binary format** where each pixel is represented by a single bit.
	/// - Each row is packed into bytes (8 pixels per byte).
	/// - The **most significant bit** in each byte represents the **first pixel** in the row.
	/// - If the image width isn't divisible by 8, extra bits are padded and ignored.
	/// - To calculate the total number of bytes: **⌈width / 8⌉ × height**.
	///
	/// @param os The output stream to which the file will be written.
	/// @param image Reference to the image to be saved.
	/// @returns `true` if the operation is successful, `false` otherwise.
	bool saveToBinary(std::ostream& os, const Image& image) const;

	/// Saves the image's pixel data in ASCII format.
	///
	/// Uses the **P1 format**, where:
	/// - Each pixel is represented by a single digit: **0 for black**, **1 for white**.
	/// - Whitespace and line breaks between pixel values are ignored.
	/// - Rows and columns do not need to be aligned.
	///
	/// @param os The output stream to which the file will be written.
	/// @param image Reference to the image to be saved.
	/// @returns `true` if the operation is successful, `false` otherwise.
	bool saveToASCII(std::ostream& os, const Image& image) const;

	PNM_Header header;
};

class PBMFileManagerASCII : public FileManager {
public:

	virtual bool canHandle(std::istream& is) const override;
	virtual File* create(std::istream& is, const std::string& filename) const override;
};

class PBMFileManagerBinary : public FileManager {
public:

	virtual bool canHandle(std::istream& is) const override;
	virtual File* create(std::istream& is, const std::string& filename) const override;
};

#endif // !__IMAGE_HPP_INCLUDED__

