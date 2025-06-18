/*
	#### OOP Project - Raster image processing ####
			FMI OOP - Informatics, 2025
*/

#include <fstream>
#include <iostream>

#include "BMP.hpp"
#include "File.hpp"
#include "Session.hpp"

BMP::BMP(const BMPHeader& bmp_header,
		 const std::string& filename, Matrix& matrix)
	: File(filename, matrix), bmp_header(bmp_header){ }


Image* BMP::createImage(size_t index) {
	return new Image(matrix, this, index); 
}
bool BMP::saveImage(const Image& image, const std::string& filename) const {
	std::string name = filename;
	createFilenameWithTimestamp(name, this->filename);

	std::ofstream os(OUTPUT_DIRECTORY_PATH + name, std::ios::binary);
	if (!os.is_open()) return false;

	// crate new headers
	BMPHeader header = this->bmp_header;

	const int32_t bmp_header_size_bytes = 54;

	const Matrix& matrix = image.getMatrix();
	int32_t width = (int32_t)image.getMatrix().getWidth();
	int32_t height = (int32_t)image.getMatrix().getHeight();

	header.biWidth = width;
	header.biHeight = height;
	int rowSize = (3 * width + 3) & ~3;
	header.biSizeImage = rowSize * height;
	header.bfSize = bmp_header_size_bytes + header.biSizeImage;

	os.write(reinterpret_cast<const char*>(&header), sizeof(header));
	if (!os) return false;

	std::vector<uint8_t> row(rowSize, 0);

	for (int y = height - 1; y >= 0; --y) {
		for (int x = 0; x < width; ++x) {
			row[x * 3 + 0] = matrix(y, x).b;
			row[x * 3 + 1] = matrix(y, x).g;
			row[x * 3 + 2] = matrix(y, x).r;
		}
		os.write(reinterpret_cast<const char*>(row.data()), rowSize);
		if(!os) return false;
	}

	return true;
}
void BMP::printInfo() const {
	File::printInfo();
	std::cout << "32bit Bitmap\n";
}

File* BMPFileManager::create(std::istream& is, const std::string& filename) const {
	if (!is) return nullptr;
	const size_t MAX_PIXEL_VALUE = 255;

	BMPHeader header;

	is.read(reinterpret_cast<char*>(&header), sizeof(header));
	if (!is) {
		std::cout << "bad header\n";
		return nullptr;
	}

	int32_t height = header.biHeight;
	int32_t width = header.biWidth;

	int rowSize = (3 * width + 3) & ~3; // 4-byte aligned
	std::vector<uint8_t> row(rowSize);

	is.seekg(header.bfOffBits, std::ios::beg);
	Matrix matrix(height, width);

	for (int y = height - 1; y >= 0; --y) {
		is.read(reinterpret_cast<char*>(row.data()), rowSize);
		if (!is) {
			std::cout << "Invalid matrix data!\n";
			return nullptr;
		}

		for (int x = 0; x < width; ++x) {

			Pixel pixel = { row[x * 3 + 2] , row[x * 3 + 1] , row[x * 3 + 0] };
			if (pixel.r > MAX_PIXEL_VALUE || pixel.g > MAX_PIXEL_VALUE || pixel.b > MAX_PIXEL_VALUE) {
				std::cout << "Max value supported is 255!\n";
				return nullptr;
			}

			matrix(y, x) = pixel;
		}
	}

	return new BMP(header, filename, matrix);
}
bool BMPFileManager::canHandle(std::istream& is) const {
	if (!is) return false;

	std::string magicNumber;
	try { 
		magicNumber += is.get();
		if (!is) { is.clear(); is.seekg(std::ios::beg, 0); return false; }
	}
	catch (...) { return false; }

	try { 
		magicNumber += is.get();
		if (!is) { is.clear(); is.seekg(std::ios::beg, 0); return false; }
	}
	catch (...) { return false; }

	is.seekg(0, std::ios::beg);
	if (magicNumber == fileTypes[FileType::BM]) return true;

	return false;
}

static BMPFileManager __;