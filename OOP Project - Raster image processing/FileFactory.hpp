/*
	#### OOP Project - Raster image processing ####
			FMI OOP - Informatics, 2025
*/

#ifndef __IMAGE_FACTORY_HPP_INCLUDED__
#define __IMAGE_FACTORY_HPP_INCLUDED__

#include <string>
#include <vector>
#include "File.hpp"

class FileFactory {
public:

	static FileFactory& getInstance();

	void registerFileManager(FileManager* manager);
	File* getFile(const std::string& filename);

private:
	FileManager* getCreator(std::istream& is);

private:
	FileFactory() = default;
	~FileFactory() = default;
	FileFactory(const FileFactory&) = delete;
	FileFactory& operator=(const FileFactory&) = delete;

	// yet again no copying allowed for the singleton object. 

private:
	std::vector<FileManager*> managers;
};

#endif // !__IMAGE_FACTORY_HPP_INCLUDED__