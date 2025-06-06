#include "FileFactory.hpp"
#include "Helpers.hpp"
#include <fstream>
#include <iostream>

// returns the static instane of our file factory
FileFactory& FileFactory::getInstance() {
	static FileFactory instance;
	return instance;
}

// register a file creator in the creators
void FileFactory::registerFileManager(FileManager* manager) { managers.push_back(manager); }

// **********************
// 1. open a file from the wanted directory ( specified in the static field inside the factory)
// 2. try all the the file creators we know --> if some can handle it we get it else return nullptr
// 3. create the file from the file creator for the wanted format
// **********************
File* FileFactory::getFile(const std::string & filename) {
	std::ifstream is(INPUT_DIRECTORY_PATH + filename, std::ios::binary);
	if (!is.is_open()) return nullptr;

	FileManager* creator = getCreator(is);
	if (creator) {
		return creator->create(is, filename);;
	}
	else {
		std::cout << "\n----------- invalid format! -----------\n";
		return nullptr;
	}
}

// try all the creators we know
FileManager* FileFactory::getCreator(std::istream& is) {

	for (FileManager* manager : managers)
		if (manager->canHandle(is)) return manager;

	return nullptr;
}


// the input files directory
// the program will kinda not work without them