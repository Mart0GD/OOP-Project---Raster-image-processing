#include "PasteCommand.hpp"
#include "Image.hpp"
#include "Helpers.hpp"

bool PasteCommand::execute(Session* session, std::istream& is) {
	if (!is) return false;

	try
	{
		std::string filenameOne;
		std::string filenameTwo;

		size_t posX, posY;

		is >> filenameOne;
		if (!is) return false;

		is >> filenameTwo;
		if (!is) return false;

		is >> posX >> posY;
		if (!is) return false;

		Image* image1 = session->getImage(filenameOne);
		Image* image2 = session->getImage(filenameTwo);

		if (!image1 || !image2) {
			std::cout << "------ Load images first! ------\n";
			return false;
		}

		std::vector<Image*> temp;
		temp.push_back((image1->resetContext(), new Image(*image1)));
		temp.push_back((image2->resetContext(), new Image(*image2)));
		session->executeCommands(temp);

		Image* image = image1->paste(image2, posX, posY); // won't throw
		clear(temp);
		if (!session->addImage(image)) return false; // won't throw, takes in nullptr
		return true;
	}
	catch (const std::exception& e)
	{
		std::cout << e.what();
		return false;
	}
	
}

static PasteCommandHandler pasteCmd;
