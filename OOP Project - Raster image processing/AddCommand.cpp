#include "AddCommand.hpp"
#include "FileFactory.hpp"

bool AddCommand::execute(Session* session, std::istream& is) {
	if (!is) return false;

	std::string filename;
	is >> filename;
	if (!is) return false;

	File* file = FileFactory::getInstance().getFile(filename);
	if (!file) {
		std::cout << "invalid filename!\n";
		return false;
	}

	Image* image = nullptr;

	// Image constructor can fail --> we only delete the file
	try { image = file->createImage(); }
	catch (const std::exception& e) {
		std::cout << e.what();
		delete file;
		return false;
	}

	// push_back fails --> no memory or the copy constructor fails
	try { session->addImage(image); }
	catch (const std::exception& e) {
		std::cout << e.what();
		delete image; // image has the file delete logic in the destructor
		return false;
	}

	return true;
}

static AddCommandHandler addCmd;