#include "SaveCommand.hpp"
#include "Image.hpp"
#include "File.hpp"
#include "Helpers.hpp"

#include <thread>

bool SaveCommand::execute(Session* session, std::istream& is) {

	std::vector<Image*> images = session->executeCommands();
	for (size_t i = 0; i < images.size(); ++i) {

		if (!images[i]->getFile()->saveImage(*images[i])) {
			std::cout << "------ Save for " << images[i]->getFile()->getFilename() << " failed!------\n";
			// we save what we can
		}

		// don't beat we );
		// if two file have the same name they are overwritten i just had to wait
		// https://en.cppreference.com/w/cpp/thread/sleep_for.html --> ref
		if (i + 1 < images.size() &&
			images[i]->getFile()->getFilename() == images[i + 1]->getFile()->getFilename())
		{
			std::this_thread::sleep_for(std::chrono::seconds(1));
		}
			
	}

	clear(images);
	std::cout << "------ Images saved! ------\n";
	return true;
}

static SaveCommandHandler saveCmd;
