#include "ListSessionCommand.hpp"
#include "Image.hpp"
#include "File.hpp"
#include "Session.hpp"

bool ListSessionCommand::execute(Session* session, std::istream& is) {
	if (!is) return false;

	std::cout << "Files in session\n";
	for (Image* image : session->getImages()) image->getFile()->printInfo();

	return true;
}

bool ListSessionCommandHandler::canHandle(std::istream& is) const {
	
	try
	{
		std::string text;
		is >> text;
		if (!is) return false;

		std::string side;
		is >> side;
		if (!is) return false;

		return text + " " + side == getType();
	}
	catch (const std::exception& e)
	{
		std::cout << e.what();
		return false;
	}
}

static ListSessionCommandHandler listCmd;