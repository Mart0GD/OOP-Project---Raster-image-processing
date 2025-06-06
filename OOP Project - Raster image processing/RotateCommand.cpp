#include "RotateLeftCommand.hpp"
#include "RotateRightCommand.hpp"
#include "Image.hpp"

void rotate(Context& context, int32_t degrees);

void RotateLeftCommand::loadInfo(Context& context) const { rotate(context, -1); }
void RotateRightCommand::loadInfo(Context& context) const { rotate(context, 1); }

bool RotateLeftCommand::execute(Image* image) const {
	Context& ctx = image->getContext();
	int rot = ctx.rotations;

	switch (rot) {
	case 3: image->getMatrix().rotateLeft(); break;
	case 2: image->getMatrix().rotate180(); break;
	default: return true; // no rotation
	}

	// rotations MUST COME first
	image->getContext().rotations = 0;
	if (image->getContext().hFlipped) image->getMatrix().hFlip();
	if (image->getContext().vFlipped) image->getMatrix().vFlip();

	return true;
}
bool RotateRightCommand::execute(Image* image) const {
	Context& ctx = image->getContext();
	int rot = ctx.rotations;

	switch (rot) {
	case 1: image->getMatrix().rotateRight(); break;
	case 2: image->getMatrix().rotate180(); break;
	default: return true; // no rotation
	}

	// rotations MUST COME first
	image->getContext().rotations = 0;
	if (image->getContext().hFlipped) image->getMatrix().hFlip();
	if (image->getContext().vFlipped) image->getMatrix().vFlip();

	return true;
}

bool RotateLeftCommandHandler::canHandle(std::istream& is) const {
	
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
bool RotateRightCommandHandler::canHandle(std::istream& is) const {

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

void rotate(Context& context, int32_t steps) {
	const int32_t fullRotation = 4;

	int32_t direction = (context.hFlipped != context.vFlipped) ? -1 : 1;

	context.rotations = (context.rotations + (direction * steps)) % fullRotation;
	if (context.rotations < 0) context.rotations += fullRotation;
}

static RotateLeftCommandHandler _;
static RotateRightCommandHandler __;