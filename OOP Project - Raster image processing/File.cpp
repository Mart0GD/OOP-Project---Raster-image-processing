#include "FileFactory.hpp"
#include "Helpers.hpp"
#include <iostream>

File::File(const std::string& filename, const Matrix& matrix) 
	: filename(filename), matrix(matrix) {
	if (filename.empty()) throw std::invalid_argument("no name provided!");
}

void File::printInfo() const {

	std::string name;

	size_t dotPos = filename.rfind('.');
	if (dotPos == std::string::npos) name = filename;
	else name = filename.substr(0, dotPos);

	std::cout << name << " - ";
}

FileManager::FileManager() { FileFactory::getInstance().registerFileManager(this); }
