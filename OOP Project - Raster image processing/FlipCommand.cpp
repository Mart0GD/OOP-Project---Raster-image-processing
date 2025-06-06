#include "FlipLeftCommand.hpp"
#include "FlipTopCommand.hpp"
#include "Image.hpp"

void FlipLeftCommand::loadInfo(Context& context) const { context.hFlipped = !context.hFlipped; }
void FlipTopCommand::loadInfo(Context& context) const { context.vFlipped = !context.vFlipped; }

bool FlipLeftCommand::execute(Image* image) const {
	if (image->getContext().hFlipped && image->getContext().rotations == 0) { image->getMatrix().hFlip(); }
	return true;
}
bool FlipTopCommand::execute(Image* image) const {
	if (image->getContext().vFlipped && image->getContext().rotations == 0) { image->getMatrix().vFlip(); }
	return true;
}

bool FlipLeftCommandHandler::canHandle(std::istream& is) const {

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
		// potential string fail
		std::cout << e.what();
		return false;
	}

}
bool FlipTopCommandHandler::canHandle(std::istream& is) const {

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
		// potential string fail
		std::cout << e.what();
		return false;
	}

}

static FlipLeftCommandHandler _;
static FlipTopCommandHandler __;