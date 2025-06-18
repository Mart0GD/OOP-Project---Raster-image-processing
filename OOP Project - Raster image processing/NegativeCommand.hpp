/*
	#### OOP Project - Raster image processing ####
			FMI OOP - Informatics, 2025
*/

#ifndef __NEGATICE_COMMAND_HPP_INCLUDED__
#define __NEGATICE_COMMAND_HPP_INCLUDED__

#include "Command.hpp"

/// Command that flips all pixel values inside an image
class NegativeCommand : public ImageCommand {
public:
	virtual ImageCommand* clone() const override { return new NegativeCommand(*this); }

	/// flips the negative flag inside the context
	/// @param context The context associated with the current image.
	virtual void loadInfo(Context& context) const override;

	/// Negates the image if the negative flag is on
	/// 
	/// @param image image to manipulate
	/// returns true if the operation is successful and false otherwise
	virtual bool execute(Image* image) const override;
};

class NegativeCommandHandler : public CommandHandler<ImageCommand> {
public:

	virtual const char* getType() const override { return "negative"; }
	virtual ImageCommand& getCommand() const override {
		static NegativeCommand negative;
		return negative;
	}
};

#endif

