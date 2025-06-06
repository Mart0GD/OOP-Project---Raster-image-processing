#include <fstream>
#include <iostream>

#include "PGM.hpp"
#include "Helpers.hpp"
#include "Session.hpp"

PGM::PGM(const PNM_Header& header,
		 const std::string& filename,
		 const Matrix& matrix)
	: File(filename, matrix), header(header) { }

Image* PGM::createImage(size_t index)  {
	return new Image(matrix, this, index);
}
bool PGM::saveImage(const Image& image, const std::string& filename) const {
	std::string name = filename;
	createFilenameWithTimestamp(name, this->filename);

	std::ofstream os(OUTPUT_DIRECTORY_PATH + name, std::ios::binary);
	if (!os.is_open()) return false;

	os  << header.format << '\n' 
		<< image.getMatrix().getWidth() << ' ' << image.getMatrix().getHeight() << '\n'
		<< header.maxValue << '\n';
	if (!os) { std::remove(name.data()); return false; }

	if (header.format == fileTypes[FileType::P2] && saveToASCII(os, image)) return true;
	if (header.format == fileTypes[FileType::P5] && saveToBinary(os, image)) return true;

	return false;
}
void PGM::printInfo() const {
	File::printInfo();
	std::cout << "Portable graymap file\n";
}

bool PGM::saveToBinary(std::ostream& os, const Image& image) const {
	if (!os) return false;

	const Matrix& matrix = image.getMatrix();
	for (int y = 0; y < matrix.getHeight(); y++)
	{
		for (int x = 0; x < matrix.getWidth(); x++)
		{
			const Pixel& pixel = matrix(y, x);

			uint8_t value = pixel.r;
			os.write(reinterpret_cast<const char*>(&value), sizeof(value));
			if (!os) return false;
		}
	}

	return os.good();
}
bool PGM::saveToASCII(std::ostream& os, const Image& image) const {
	if (!os) return false;

	const Matrix& matrix = image.getMatrix();
	for (int y = 0; y < matrix.getHeight(); ++y) {

		for (int x = 0; x < matrix.getWidth(); x++)
		{
			const Pixel& pixel = matrix(y, x);
			os << pixel.r << ' ';
		}
		if (y + 1 < matrix.size()) std::cout << '\n';
	}

	return os.good();
}

File* PGMFileManagerASCII::create(std::istream& is, const std::string& filename) const {
	if (!is) return nullptr;

	try
	{
		PNM_Header header;
		if (!readHeader(is, header, true)) return nullptr;
		if (!skipWhiteSpace(is)) return nullptr;

		Matrix matrix(header.height, header.width);
		for (int y = 0; y < header.height; y++)
		{
			for (int x = 0; x < header.width; x++)
			{
				unsigned pixel;

				is >> pixel;
				if (!is || pixel > header.maxValue) return nullptr;

				matrix(y, x) = { (uint8_t)pixel, (uint8_t)pixel, (uint8_t)pixel };
			}
		}

		return new PGM(header,filename, matrix); // throws
	}
	catch (const std::exception& e)
	{
		std::cout << e.what();
		return nullptr;
	}
}
bool PGMFileManagerASCII::canHandle(std::istream& is) const {
	if (!is) return false;

	std::string magicNumber;

	try { magicNumber += readToken(is); }
	catch (...) { is.clear(); is.seekg(0, std::ios::beg); return false; }

	is.seekg(0, std::ios::beg);
	if (magicNumber == fileTypes[FileType::P2]) return true;

	return false;
}

File* PGMFileManagerBinary::create(std::istream& is, const std::string& filename) const {
	if (!is) return nullptr;

	try
	{
		PNM_Header header;
		if (!readHeader(is, header, true)) return nullptr;
		if (!skipWhiteSpace(is)) return nullptr;

		Matrix matrix(header.height, header.width);

		uint8_t byte;
		for (int y = 0; y < header.height && is; y++)
		{
			for (int x = 0; x < header.width && is; x++)
			{
				is.read(reinterpret_cast<char*>(&byte), sizeof(byte));
				if (!is || byte > header.maxValue) return nullptr;

				matrix(y, x) = { byte, byte, byte };
			}
		}

		return new PGM(header, filename, matrix); // throws
	}
	catch (const std::exception& e)
	{
		std::cout << e.what();
		return nullptr;
	}
}
bool PGMFileManagerBinary::canHandle(std::istream& is) const {
	if (!is) return false;

	std::string magicNumber;

	try { magicNumber += readToken(is); }
	catch (...) { is.clear(); is.seekg(0, std::ios::beg); return false; }

	is.seekg(0, std::ios::beg);
	if (magicNumber == fileTypes[FileType::P5]) return true;

	return false;
}

static PGMFileManagerASCII _;
static PGMFileManagerBinary __;