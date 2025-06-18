/*
	#### OOP Project - Raster image processing ####
			FMI OOP - Informatics, 2025
*/

#ifndef __ROTATE_LEFT_COMMAND_HPP_INCLUDED__
#define __ROTATE_LEFT_COMMAND_HPP_INCLUDED__

#include "Command.hpp"

/// Command that rotates the image to the left (90 degrees counter-clockwise).
///
/// The command interprets the rotation context and applies the appropriate matrix transformation.
/// It resets the rotation value in the context after execution.
class RotateLeftCommand : public ImageCommand {
public:
	virtual ImageCommand* clone() const override { return new RotateLeftCommand(*this); }

	/// Updates the context to reflect a left rotation request.
    /// @param context The image transformation context.
	virtual void loadInfo(Context& context) const override;

	/// Executes the actual image rotation based on the current context.
	/// 
	/// @param image The image to rotate.
	/// @returns true if successful.
	/// @note the maximum amount of rotations that can be done are 2 due to identities
	/// either one to the left or 180, otherwise it is one right rotation or a 180 flip
	virtual bool execute(Image* image) const override;
};


class RotateLeftCommandHandler : public CommandHandler<ImageCommand> {
public:

	virtual const char* getType() const override { return "rotate left"; }

	virtual ImageCommand& getCommand() const {
		static RotateLeftCommand rotate_l;
		return rotate_l;
	}

	virtual bool canHandle(std::istream& is) const override;
};


#endif