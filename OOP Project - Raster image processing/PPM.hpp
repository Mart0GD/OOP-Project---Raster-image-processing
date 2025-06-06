/*
	#### OOP Project - Raster image processing ####
			FMI OOP - Informatics, 2025
*/

#ifndef __PPM_HPP_INCLUDED__
#define __PPM_HPP_INCLUDED__

#include <vector>
#include <string>

#include "File.hpp"
#include "Enums.hpp"
#include "PNM_Header.hpp"

class Session;

class PPM : public File {
public:
	PPM(const PNM_Header& header, 
		const std::string& filename,
		const Matrix& matrix);
	virtual File* clone() const override { return new PPM(*this); }

	virtual Image* createImage(size_t index = 0) override;
	virtual bool saveImage(const Image& image, const std::string& filename = NO_SAVE_NAME) const override;
	virtual void printInfo() const override;

private:
	bool saveToBinary(std::ostream& os, const Image& image) const;
	bool saveToASCII(std::ostream& os, const Image& image) const;
	PNM_Header header;
};

class PPMFileManagerASCII : public FileManager {
public:

	virtual File* create(std::istream& is, const std::string& filename) const override;
	virtual bool canHandle(std::istream& is) const override;
};

class PPMFileManagerBinary : public FileManager {
public:

	virtual File* create(std::istream& is, const std::string& filename) const override;
	virtual bool canHandle(std::istream& is) const override;
};

#endif // !__PPM_HPP_INCLUDED__
