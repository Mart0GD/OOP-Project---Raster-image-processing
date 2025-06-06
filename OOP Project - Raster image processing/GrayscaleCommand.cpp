#include "GrayscaleCommand.hpp"
#include "Image.hpp"

void GrayscaleCommand::loadInfo(Context& context) const {
	if (context.state <= GRAY) return;
	context.state = GRAY;
}
bool GrayscaleCommand::execute(Image* image) const {
	if (image->getContext().state == GRAY) image->grayscale();
	return true;
}

static GrayscaleCommandHandler _;