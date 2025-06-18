/*
	#### OOP Project - Raster image processing ####
			FMI OOP - Informatics, 2025
*/

#ifndef __PGM_HPP_INCLUDED__
#define __PGM_HPP_INCLUDED__

#include <vector>
#include <string>

#include "File.hpp"
#include "PNM_Header.hpp"

class Session;

/// Represent a Portable bitmap file
///
/// only allows gray values 0 is black and the maxValue is white,
/// everything in between is a shade of grey
class PGM : public File{
public:
	PGM(const PNM_Header& header, 
		const std::string& filename,
		const Matrix& matrix);
	virtual File* clone() const override { return new PGM(*this); }

	/// Checks the identifier and saves the file in either binary (P5) or ASCII format (P2)
	/// @param image The image to save.
	/// @param filename The output filename. If not provided, uses a default.
	virtual Image* createImage(size_t index = 0) override;
	virtual bool saveImage(const Image& image, const std::string& filename = NO_SAVE_NAME) const override;
	virtual void printInfo() const override;

private:

	/// Saves the image's pixel data in binary format.
	/// 
	/// @param os The output stream to which the file will be written.
	/// @param image Reference to the image to be saved.
	/// @returns `true` if the operation is successful, `false` otherwise.
	bool saveToBinary(std::ostream& os, const Image& image) const;

	/// Saves the image's pixel data in ASCII format.
	///
	/// Uses the **P2 format**, where:
	/// - Each pixel is represented by a single digit: from **0 for black**, **maxValue for white**.
	/// - Whitespace and line breaks between pixel values are ignored.
	/// - Rows and columns do not need to be aligned.
	///
	/// @param os The output stream to which the file will be written.
	/// @param image Reference to the image to be saved.
	/// @returns `true` if the operation is successful, `false` otherwise.
	bool saveToASCII(std::ostream& os, const Image& image) const;

	PNM_Header header;
};

class PGMFileManagerASCII : public FileManager {
public:

	virtual bool canHandle(std::istream& is) const override;
	virtual File* create(std::istream& is, const std::string& filename) const override;
};

class PGMFileManagerBinary : public FileManager {
public:

	virtual bool canHandle(std::istream& is) const override;
	virtual File* create(std::istream& is, const std::string& filename) const override;
};

#endif // !__IMAGE_HPP_INCLUDED__

