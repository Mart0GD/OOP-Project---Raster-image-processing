#include "MonochromeCommand.hpp"
#include "Image.hpp"

void MonochromeCommand::loadInfo(Context& context) const {
	if (context.state == BW) return;
	context.state = BW;
}
bool MonochromeCommand::execute(Image* image) const {
	if (image->getContext().state == BW) image->monochrome();
	return true;
}

static MonochromeCommandHandler _;