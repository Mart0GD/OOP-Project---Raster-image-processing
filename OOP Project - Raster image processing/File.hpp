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

class File {
public:
	File(const std::string& filename, const Matrix& matrix);
	virtual File* clone() const = 0;

	virtual Image* createImage(size_t commandIndex = 0) = 0;

	virtual bool saveImage(const Image& image, const std::string& filename = NO_SAVE_NAME) const = 0;
	virtual void printInfo() const = 0;

	std::string getFilename() const { return filename; }
	void setFilename(const std::string& name) { filename = name; }

protected:
	std::string filename;
	Matrix matrix;
};


// interface like class responsible for file creation
class FileManager {
public:
	FileManager();
	virtual ~FileManager() = default;

	virtual bool canHandle(std::istream& is) const = 0;
	virtual File* create(std::istream& is, const std::string& filename) const = 0;

};

#endif // !__FILE_HPP_INCLUDED__