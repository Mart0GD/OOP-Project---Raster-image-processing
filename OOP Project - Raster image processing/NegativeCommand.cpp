#include "NegativeCommand.hpp"
#include "Image.hpp"

void NegativeCommand::loadInfo(Context& context) const { context.negative = !context.negative; }
bool NegativeCommand::execute(Image* image) const {
	if (image->getContext().negative) image->negative();
	return true;
}

static NegativeCommandHandler negHandler;