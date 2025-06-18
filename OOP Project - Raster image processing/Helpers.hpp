/*
	#### OOP Project - Raster image processing ####
			FMI OOP - Informatics, 2025
*/

#ifndef __HELPERS_HPP_INCLUDED__
#define __HELPERS_HPP_INCLUDED__
#pragma warning(disable : 4996)

#include <string>
#include <vector>
#include <iostream>
#include <ctime>
#include <sstream>
#include "PNM_Header.hpp"

/// Represents a placeholder name used when no filename is assigned.
static const char NO_SAVE_NAME[] = "N/a";

/// The directory where manipulated files are saved.
static const char OUTPUT_DIRECTORY_PATH[] = "manipulated/";

/// The directory from which example images are read.
static const char INPUT_DIRECTORY_PATH[] = "examples/";

/// The symbol used to indicate comments in PNM files.
static const char COMMENT_SYMBOL = '#';

/// Reads the next valid token from a PNM file input stream.
/// 
/// Skips comment lines starting with `#`.
/// @throws std::invalid_argument If the stream contains no valid token.
static std::string readToken(std::istream& is) {
	std::string token;
	while (is >> token && is) {
		if (token[0] == COMMENT_SYMBOL) {
			char buffer[1024];
			is.getline(buffer, sizeof(buffer));
			continue;
		}

		return token;
	}

	throw std::invalid_argument("\n----------- invalid format! -----------\n");
}

/// Skips whitespace characters in the stream and positions the stream at the next non-whitespace character
/// 
/// @returns true if successful, false if the stream becomes invalid.
static bool skipWhiteSpace(std::istream& is) {
	char c;
	while (is.get(c) && std::isspace(static_cast<unsigned char>(c)) && is);
	if (!is) return false;

	is.unget();
	return is.good();
}

/// Returns the current time formatted as "(HH-MM-SS)".
/// 
/// @returns A string representing the current time.
/// @note found on github --> https://shorturl.at/1OpcF
static std::string getCurrentTime() {
	time_t now = std::time(0);
	struct tm tmStruct;
	char buffer[80];

	tmStruct = *localtime(&now);
	strftime(buffer, sizeof(buffer), "(%H-%M-%S)", &tmStruct);
	return buffer;
}

/// Deletes raw pointers inside a vector and clears it.
/// 
/// @tparam T The pointer type.
/// @param vector The vector of pointers to delete.
template<typename T>
static void clear(std::vector<T>& vector) {
	for (T& element : vector) {
		delete element; element = nullptr;
	}
	vector.clear();
}

/// Reads the header of a PNM file from an input stream.
/// 
/// @param is The input stream.
/// @param header The header object to fill.
/// @param hasMax Whether the file format expects a max pixel value field.
/// @returns true if the header was read successfully, false otherwise.
static bool readHeader(std::istream& is, PNM_Header& header, bool hasMax = false) {
	const int32_t MAX_PIXEL_VALUE = 255;

	try
	{
		std::string format = readToken(is); // throws
		int32_t width = std::stoi(readToken(is)); // throws
		int32_t height = std::stoi(readToken(is)); // throws

		uint32_t maxValue;
		if (hasMax) maxValue = std::stoi(readToken(is)); // throws
		if (hasMax && maxValue > MAX_PIXEL_VALUE) return false;

		header = { format, width, height, hasMax ? maxValue : 1 };
	}
	catch (const std::exception&) { return false; }

	return true;
}

/// Extracts filenames from a stream line and populates a vector with them.
/// 
/// @param is The input stream containing space-separated filenames.
/// @param filenames The output vector to fill.
/// @returns true on success, false on failure.
static bool getFilenames(std::istream& is, std::vector<std::string>& filenames)
{
	try
	{
		std::string text;
		std::getline(is, text);

		std::istringstream iss(text);
		if (!iss)return false;

		do
		{
			std::string name;

			iss >> name;
			if (!iss) break;

			filenames.push_back(name);
		} while (is);
	}
	catch (const std::exception& e)
	{
		std::cout << e.what();
		return false;
	}

	return true;
}

/// Appends the file extension from the original filename to the new name.
/// @param original The original filename with extension.
/// @param newName The destination string to append the extension to.
static void createFilename(const std::string& original, std::string& newName) {
	std::size_t dotPos = original.rfind('.'); // doesn't throw
	if (dotPos == std::string::npos) return;

	newName += original.substr(dotPos);
}

/// Creates a filename by appending a timestamp to the base name if the current name is NO_SAVE_NAME.
/// @param name The name to modify (passed by reference).
/// @param filename The original filename to base the new name on.
static void createFilenameWithTimestamp(std::string& name, const std::string filename) {

	if (name == NO_SAVE_NAME) {
		name = filename;
		std::string time = getCurrentTime();

		// find dot index
		std::size_t dotPos = name.rfind('.'); // doesn't throw
		if (dotPos == std::string::npos) {
			name = name + "_" + time; // no dot
		}

		// we have a valid dot position
		name = name.substr(0, dotPos) + "_" + time + name.substr(dotPos);
	}
}

#endif // ! __HELPERS_HPP_INCLUDED__
