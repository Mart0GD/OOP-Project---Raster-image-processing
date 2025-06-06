#include <fstream>
#include <iostream>
#include "PPM.hpp"
#include "Helpers.hpp"

PPM::PPM(const PNM_Header& header,
		 const std::string& filename,
		 const Matrix& matrix) 
	: File(filename, matrix), header(header) { }

Image* PPM::createImage(size_t index) {
	return new Image(matrix, this, index);
}
bool PPM::saveImage(const Image& image, const std::string& filename) const {
	std::string name = filename;
	createFilenameWithTimestamp(name, this->filename);

	std::ofstream os(OUTPUT_DIRECTORY_PATH + name, std::ios::binary);
	if (!os.is_open()) return false;

	os  << header.format << '\n'
		<< image.getMatrix().getWidth() << ' ' << image.getMatrix().getHeight() << '\n'
		<< header.maxValue << '\n';
	if (!os) { std::remove(name.data()); return false; }

	if (header.format == fileTypes[FileType::P3] && saveToASCII(os, image)) return true;
	if (header.format == fileTypes[FileType::P6] && saveToBinary(os, image)) return true;

	return false;
}
void PPM::printInfo() const {
	File::printInfo();
	std::cout << "Portable pixmap file\n";
}

bool PPM::saveToBinary(std::ostream & os, const Image& image) const {
	if (!os) return false;

	const Matrix& matrix = image.getMatrix();
	for (int y = 0; y < matrix.getHeight(); y++)
	{
		for (int x = 0; x < matrix.getWidth(); x++)
		{
			const Pixel& pixel = matrix(y, x);

			os.write(reinterpret_cast<const char*>(&pixel.r), sizeof(pixel.r));
			os.write(reinterpret_cast<const char*>(&pixel.g), sizeof(pixel.g));
			os.write(reinterpret_cast<const char*>(&pixel.b), sizeof(pixel.b));
			if (!os) return false;
		}
	}

	return os.good();
}
bool PPM::saveToASCII(std::ostream& os, const Image& image) const {
	if (!os) return false;

	const Matrix& matrix = image.getMatrix();
	for (int y = 0; y < matrix.getHeight(); ++y) {

		for (int x = 0; x < matrix.getWidth(); x++)
		{
			const Pixel& pixel = matrix(y, x);
			os << pixel.r << ' ' << pixel.g << ' ' << pixel.b << ' ';
		}
		if (y + 1 < matrix.size()) std::cout << '\n';
	}

	return os.good();
}

File* PPMFileManagerASCII::create(std::istream& is, const std::string& filename) const {
	if (!is) return nullptr;

	try
	{
		PNM_Header header;
		if (readHeader(is, header, true)) return nullptr;
		Matrix matrix(header.height, header.width);

		for (int y = 0; y < header.height; y++)
		{
			for (int x = 0; x < header.width; x++)
			{
				// unsigned for reading purposes 
				unsigned r, g, b;

				is >> r >> g >> b;
				if (!is || r > header.maxValue || g > header.maxValue || b > header.maxValue) return nullptr;

				matrix(y, x) = { (uint8_t)r, (uint8_t)g, (uint8_t)b };
			}
		}

		return new PPM(header, filename, matrix); // throws
	}
	catch (const std::exception& e)
	{
		std::cout << e.what();
		return nullptr;
	}
}
bool  PPMFileManagerASCII::canHandle(std::istream& is) const {
	if (!is) return false;

	std::string magicNumber;

	try { magicNumber += readToken(is); }
	catch (...) { is.clear(); is.seekg(0, std::ios::beg); return false; }

	is.seekg(0, std::ios::beg);
	if (magicNumber == fileTypes[FileType::P3]) return true;

	return false;
}

File* PPMFileManagerBinary::create(std::istream& is, const std::string& filename) const {
	if (!is) return nullptr;

	try
	{
		PNM_Header header;
		if (!readHeader(is, header, true)) return nullptr;
		if(!skipWhiteSpace(is)) return nullptr;

		Matrix matrix(header.height, header.width);

		for (int y = 0; y < header.height; y++)
		{
			for (int x = 0; x < header.width; x++)
			{
				uint8_t r, g, b;

				is.read(reinterpret_cast<char*>(&r), sizeof(r));
				is.read(reinterpret_cast<char*>(&g), sizeof(g));
				is.read(reinterpret_cast<char*>(&b), sizeof(b));

				if (!is || r > header.maxValue || g > header.maxValue || b > header.maxValue) return nullptr;

				matrix(y, x) = {r, g, b};
			}
		}

		return new PPM(header, filename, matrix); // throws
	}
	catch (const std::exception& e)
	{
		std::cout << e.what();
		return nullptr;
	}
}
bool PPMFileManagerBinary::canHandle(std::istream& is) const {
	if (!is) return false;

	std::string magicNumber;

	try { magicNumber += readToken(is); }
	catch (...) { is.clear(); is.seekg(0, std::ios::beg); return false; }

	is.seekg(0, std::ios::beg);
	if (magicNumber == fileTypes[FileType::P6]) return true;

	return false;
}

static PPMFileManagerASCII ppm_a;
static PPMFileManagerBinary ppm_b;