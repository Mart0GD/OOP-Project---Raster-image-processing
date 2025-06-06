/*
	#### OOP Project - Raster image processing ####
			FMI OOP - Informatics, 2025
*/

#ifndef __BMP_HPP_INCLUDED__
#define __BMP_HPP_INCLUDED__

#include "File.hpp"
#include "BMP_Header.hpp"

class Session;

class BMP : public File {
public:
	BMP(const BMPHeader& bmp_header,
		const std::string& filename, Matrix& matrix);
	virtual File* clone() const override { return new BMP(*this); }

	virtual Image* createImage(size_t index = 0) override;
	virtual bool saveImage(const Image& image, const std::string& filename = NO_SAVE_NAME) const override;
	virtual void printInfo() const override;

private:
	BMPHeader bmp_header;
};

class BMPFileManager : public FileManager {
public:

	virtual File* create(std::istream& is, const std::string& filename) const override;
	virtual bool canHandle(std::istream& is) const override;
};

#endif // !__IMAGE_HPP_INCLUDED__

