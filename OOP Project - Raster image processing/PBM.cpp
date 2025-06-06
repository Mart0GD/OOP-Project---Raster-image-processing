#include "PBM.hpp"
#include "Helpers.hpp"
#include "Session.hpp"

#include <fstream>
#include <iostream>
#include <string>
#define BITS_PER_PIXEL 8

PBM::PBM(const PNM_Header& header,
	const std::string& filename,
	const Matrix& matrix)
	: File(filename, matrix), header(header) { }

Image* PBM::createImage(size_t index) {
	return new Image(matrix, this, index);
}
bool PBM::saveImage(const Image& image, const std::string& filename) const {
	std::string name = filename;
	createFilenameWithTimestamp(name, this->filename);

	std::string fullPath = OUTPUT_DIRECTORY_PATH + name;
	std::ofstream os(fullPath, std::ios::binary);
	if (!os.is_open()) return false;

	os << header.format << '\n'
		<< image.getMatrix().getWidth() << ' ' << image.getMatrix().getHeight() << '\n';
	if (!os) {
		std::remove(fullPath.c_str());
		return false;
	}

	if (header.format == fileTypes[FileType::P1]) {
		return saveToASCII(os, image); 
	}
	if (header.format == fileTypes[FileType::P4]) {
		return saveToBinary(os, image);
	}

	return false;
}
void PBM::printInfo() const {
	File::printInfo();
	std::cout << "Portable bitmap file\n";
}

bool PBM::saveToBinary(std::ostream& os, const Image& image) const {
	const Matrix& matrix = image.getMatrix();

	size_t rowSize = ((BITS_PER_PIXEL - 1) + matrix.getWidth()) / BITS_PER_PIXEL;
	std::vector<uint8_t> row(rowSize);

	
	for (int y = 0; y < matrix.getHeight(); y++)
	{
		std::fill(row.begin(), row.end(), 0);

		for (int x = 0; x < matrix.getWidth(); x++)
		{
			// white
			if (matrix(y, x).r == 0) continue;
			
			row[x / BITS_PER_PIXEL] |= (1 << (7 - (x % BITS_PER_PIXEL))); // black
		}

		os.write(reinterpret_cast<const char*>(row.data()), rowSize);
		if (!os) { std::remove(filename.c_str()); return false; }
	}

	return true;
}
bool PBM::saveToASCII(std::ostream& os, const Image& image) const {
	const int32_t max_value = 255;

	const Matrix& matrix = image.getMatrix();
	for (int y = 0; y < matrix.getHeight(); y++)
	{
		for (int x = 0; x < matrix.getWidth(); x++)
		{
			const Pixel& pixel = matrix(y, x);
			os << (pixel.r == max_value ? 0 : 1) << ' ';
		}
		if (y + 1 < matrix.size()) std::cout << '\n';
	}

	return os.good();
}

// file creation logic
File* PBMFileManagerASCII::create(std::istream& is, const std::string& filename) const {
	if (!is) return nullptr;

	try
	{
		PNM_Header header;
		if(!readHeader(is, header)) return nullptr;

		Matrix matrix(header.height, header.width);
		for (int y = 0; y < header.height && is; y++)
		{
			for (int x = 0; x < header.width && is; x++)
			{
				bool pixel;
				is >> pixel;
				if (!is) { std::cout << "Bad read!\n"; return nullptr; }
				if (pixel != 0 && pixel != 1) { std::cout << "invalid matrix values!\n"; return nullptr; }

				uint8_t value = pixel ? 255 : 0;

				matrix(y, x) = { value, value, value };
			}
		}
		
		return new PBM(header,filename, matrix); // throws
	}
	catch (const std::exception& e)
	{
		std::cout << e.what();
		return nullptr;
	}
}
bool PBMFileManagerASCII::canHandle(std::istream& is) const {
	if (!is) return false;

	std::string magicNumber;

	try { magicNumber += readToken(is); }
	catch(...) { is.clear(); is.seekg(0, std::ios::beg); return false; }

	is.seekg(0, std::ios::beg);
	if (magicNumber == fileTypes[FileType::P1]) return true;

	return false;
}

File* PBMFileManagerBinary::create(std::istream& is, const std::string& filename) const {
	if (!is) return nullptr;

	try
	{
		PNM_Header header;
		if(!readHeader(is, header)) return nullptr;
		if (!skipWhiteSpace(is)) return nullptr;

		Matrix matrix(header.height, header.width); // throws 

		// from the wikipedia page --> ceiling doesn't allow functionality for int's
		int32_t rowSize = ((BITS_PER_PIXEL - 1) + header.width) / BITS_PER_PIXEL;
		std::vector<uint8_t> row(rowSize); // bitvector to store the row and the padding --> can throw

		for (int y = 0; y < header.height; y++) {
			is.read(reinterpret_cast<char*>(row.data()), rowSize);
			if (!is) return nullptr;

			for (int x = 0; x < header.width; x++) {
				int byteIndex = x / BITS_PER_PIXEL;
				int bitIndex = 7 - (x % BITS_PER_PIXEL); // we start with the MS bit
				bool pixel = ((row[byteIndex]) >> bitIndex) & 1;

				uint8_t value = pixel ? 255 : 0;
				matrix(y, x) = { value, value, value };
			}
		}

		return new PBM(header,filename, matrix); // throws
	}
	catch (const std::exception& e)
	{
		std::cout << e.what();
		return nullptr;
	}
}
bool PBMFileManagerBinary::canHandle(std::istream& is) const {
	if (!is) return false;

	std::string magicNumber;

	try { magicNumber += readToken(is); }
	catch (...) { is.clear(); is.seekg(0, std::ios::beg); return false; }

	is.seekg(0, std::ios::beg);
	if (magicNumber == fileTypes[FileType::P4]) return true;

	return false;
}

static PBMFileManagerASCII _;
static PBMFileManagerBinary __;
