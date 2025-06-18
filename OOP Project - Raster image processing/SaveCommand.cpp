#include "SaveCommand.hpp"
#include "Image.hpp"
#include "File.hpp"
#include "Helpers.hpp"

#include <thread>

bool SaveCommand::execute(Session* session, std::istream& is) {
	
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
	for (size_t i = 0; i < copy.size(); ++i) {

		if (!copy[i]->getFile()->saveImage(*copy[i])) {
			std::cout << "------ Save for " << copy[i]->getFile()->getFilename() << " failed!------\n";
			// we save what we can
		}

		// don't beat me );
		// if two file have the same name they are overwritten i just had to wait
		// https://en.cppreference.com/w/cpp/thread/sleep_for.html --> ref
		if (i + 1 < copy.size() &&
			copy[i]->getFile()->getFilename() == copy[i + 1]->getFile()->getFilename())
		{
			std::this_thread::sleep_for(std::chrono::seconds(1));
		}
			
	}

	// clear the images
	clear(copy);
	std::cout << "------ Images saved! ------\n";
	return true;
}

static SaveCommandHandler saveCmd;
