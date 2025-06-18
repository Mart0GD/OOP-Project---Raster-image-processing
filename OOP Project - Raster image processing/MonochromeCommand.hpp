/*
	#### OOP Project - Raster image processing ####
			FMI OOP - Informatics, 2025
*/

#ifndef __MONOCHROME_HPP_INCLUDED__
#define __MONOCHROME_HPP_INCLUDED__

#include "Command.hpp"

/// Command that converts an image to a monochrome version of itself
class MonochromeCommand : public ImageCommand {
public:
	virtual ImageCommand* clone() const override { return new MonochromeCommand(*this); }

	/// Updates the RGB_STATE inside the context to reflect the monochromatic transformation.
	/// @param context The context associated with the current image.
	virtual void loadInfo(Context& context) const override;

	/// calls the grayscale function inside the image reflecting on the context
	/// @param image Image to manipulate
	/// returns true if the operation was successful and false otherwise
	virtual bool execute(Image* image) const override;
};


class MonochromeCommandHandler : public CommandHandler<ImageCommand> {
public:

	virtual const char* getType() const override { return "monochrome"; }
	virtual ImageCommand& getCommand() const override {
		static MonochromeCommand mono;
		return mono;
	}
};

#endif
