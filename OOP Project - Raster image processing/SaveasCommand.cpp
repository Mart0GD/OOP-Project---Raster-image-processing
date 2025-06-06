#include "SaveasCommand.hpp"
#include "Image.hpp"
#include "File.hpp"
#include "Helpers.hpp"

#include <sstream>

bool SaveasCommand::execute(Session* session, std::istream& is) {
	if (!is) return false;

	std::vector<Image*> images = session->executeCommands();

	std::vector<std::string> names;
	if(!getFilenames(is, names)) return false;

	size_t imgCnt = images.size();
	size_t namesCnt = names.size();

	for(int i = 0; i < imgCnt; ++i)
	{
		Image* image = images[i];
		bool success = false;

		if (i < namesCnt) success = image->getFile()->saveImage(*image, names[i]);
		else success = image->getFile()->saveImage(*image);

		if (!success) {
			std::cout << "------ Save for " << image->getFile()->getFilename() << " failed!------\n";
		}
	}

	clear(images);
	std::cout << "------ Images saved! ------\n";
	return true;
}


static SaveasCommandHandler SaveasCmd;