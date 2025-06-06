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
#include "File.hpp"

// global consts
static const char NO_SAVE_NAME[] = "N/a";
static const char OUTPUT_DIRECTORY_PATH[] = "manipulated/";
static const char INPUT_DIRECTORY_PATH[] = "examples/";
static const char COMMENT_SYMBOL = '#';

// method for reading a valid token from PNM type files
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

//the need for this method arised when my binary reader read a leftover / r in a newline
static bool skipWhiteSpace(std::istream& is) {
	char c;
	while (is.get(c) && std::isspace(static_cast<unsigned char>(c)) && is);
	if (!is) return false;

	is.unget();
	return is.good();
}

// method I found on github --> https://shorturl.at/1OpcF
static std::string getCurrentTime() {
	time_t now = std::time(0);
	struct tm tmStruct;
	char buffer[80];

	tmStruct = *localtime(&now);
	strftime(buffer, sizeof(buffer), "(%H-%M-%S)", &tmStruct);
	return buffer;
}

// template method responsible for deleteing raw allocated data in a std::vector conatiner
template<typename T>
static void clear(std::vector<T>& vector) {
	for (T& element : vector) {
		delete element; element = nullptr;
	}
	vector.clear();
}

// helper function for reading a PNM file header
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

//  helper function for reading filenames form a stream
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

static void createFilename(const std::string& original, std::string& newName) {
	std::size_t dotPos = original.rfind('.'); // doesn't throw
	if (dotPos == std::string::npos) return;

	newName += original.substr(dotPos);
}

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
