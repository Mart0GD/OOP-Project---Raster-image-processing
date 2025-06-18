/*
	#### OOP Project - Raster image processing ####
			FMI OOP - Informatics, 2025
*/

#ifndef __GRAYSCALE_COMMAND_HPP_INCLUDED__
#define __GRAYSCALE_COMMAND_HPP_INCLUDED__

#include "Command.hpp"

/// Command that converts the image to grayscale.
class GrayscaleCommand : public ImageCommand {
public:
	virtual ImageCommand* clone() const override { return new GrayscaleCommand(*this); }

	/// Updates the RGB_STATE inside the context to reflect the grayscale transformation.
	/// @param context The context associated with the current image.
	virtual void loadInfo(Context& context) const override;

	/// calls the grayscale function inside the image reflecting on the context
	/// @param image Image to manipulate
	/// returns true if the operation was successful and false otherwise
	virtual bool execute(Image* image) const override;
};


class GrayscaleCommandHandler : public CommandHandler<ImageCommand> {
public:

	virtual const char* getType() const override { return "grayscale"; }
	virtual ImageCommand& getCommand() const override {
		static GrayscaleCommand gray;
		return gray;
	}
};

#endif // !__SESSION_MANAGER_HPP_INCLUDED__
