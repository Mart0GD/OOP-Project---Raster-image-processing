/*
	#### OOP Project - Raster image processing ####
			FMI OOP - Informatics, 2025
*/

#ifndef __IMAGE_FACTORY_HPP_INCLUDED__
#define __IMAGE_FACTORY_HPP_INCLUDED__

#include <string>
#include <vector>
#include "File.hpp"

/// A singleton factory for managing different file format handlers (FileManagers
/// @note The code for the Command factory is based on the lectue examples provided for the IS major.
/// @note The idea and execution are implementation specific.
/// @attention No copying allowed
/// ### Example
/// ~~~~~~~~~~~~~~~~~~~ .cpp
/// 
/// FileFactory& instance = FileFactory::getInstance();
/// 
/// ~~~~~~~~~~~~~~~~~~~
class FileFactory {
public:

	/// Returns the singleton instance of the FileFactory.
	static FileFactory& getInstance();

	/// Registers a new FileManager capable of handling specific file types.
	/// @throws std::bad_alloc
	void registerFileManager(FileManager* manager);

	/// Returns a new File object created by an appropriate FileManager for the given filename.
	File* getFile(const std::string& filename);

private:

	/// Finds the appropriate FileManager based on the input file stream.
	/// 
	/// Iterates over all file managers and calls their canHandle() methods
	FileManager* getCreator(std::istream& is);

private:
	FileFactory() = default;
	~FileFactory() = default;
	FileFactory(const FileFactory&) = delete;
	FileFactory& operator=(const FileFactory&) = delete;

private:

	/// Collection of registered FileManager objects.
	std::vector<FileManager*> managers;
};

#endif // !__IMAGE_FACTORY_HPP_INCLUDED__