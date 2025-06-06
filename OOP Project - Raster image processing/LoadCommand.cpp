#include "LoadCommand.hpp"
#include "FileFactory.hpp"
#include "Helpers.hpp"

#include <sstream>

bool LoadCommand::execute(Session* session, std::istream& is) {
	if (!is) return false;

	std::vector<std::string> filenames;
	if (!getFilenames(is, filenames)) return false;


	// first step --> create files from the filenames provided
	// they are responsible for image creation and saving

	std::vector<File*> files;
	for (const std::string& filename : filenames) {
		File* i = FileFactory::getInstance().getFile(filename);
		if (i) files.push_back(i);
		else {
			clear<File*>(files); // no dangling pointers
			return false;
		}
	}

	// second step --> create the actual images with the creation logic inside the files
	// we have separated responsibilities 

	std::vector<Image*> images;
	for (File* file : files) {

		try { Image* image = file->createImage(); images.push_back(image); }
		catch (...) {

			clear<File*>(files); // delete files --> no dangling pointers
			clear<Image*>(images); // delete images, file delete will have no effect
			return false;
		}
	}

	for (Image* image : images) 
		session->addImage(image);

	std::cout << "------ Session started! ------\n";
	return true;
}

static LoadCommandHandler loadCmd;

