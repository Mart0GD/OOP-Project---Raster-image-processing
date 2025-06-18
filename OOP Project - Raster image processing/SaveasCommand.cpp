#include "SaveasCommand.hpp"
#include "Image.hpp"
#include "File.hpp"
#include "Helpers.hpp"

#include <sstream>
#include <thread>

bool SaveasCommand::execute(Session* session, std::istream& is) {
	if (!is) return false;

	std::vector<std::string> names;
	if (!getFilenames(is, names)) return false;
	if (names.size() >= session->getImages().size()) {
		std::cout << "------ Provided names are more than the images inside the session! ------\n";
		return false;
	}

	// create a copy of the images 
	std::vector<Image*> copy;
	try {
		for (Image* image : session->getImages()) {
			image->resetContext();
			copy.push_back(new Image(*image));
		}
	}
	catch (const std::exception&) {
		for (Image* image : copy) delete image;
		return false;
	}

	session->executeCommands(copy);

	size_t imgCnt = copy.size();
	size_t namesCnt = names.size();

	for(int i = 0; i < imgCnt; ++i)
	{
		Image* image = copy[i];
		bool success = false;

		if (i < namesCnt) success = image->getFile()->saveImage(*image, names[i]);
		else success = image->getFile()->saveImage(*image);

		if (!success) {
			std::cout << "------ Save for " << image->getFile()->getFilename() << " failed!------\n";
		}

		// same reason as the save command
		if (i + 1 < copy.size() &&
			copy[i]->getFile()->getFilename() == copy[i + 1]->getFile()->getFilename())
		{
			std::this_thread::sleep_for(std::chrono::seconds(1));
		}
	}

	clear(copy);
	std::cout << "------ Images saved! ------\n";
	return true;
}


static SaveasCommandHandler SaveasCmd;