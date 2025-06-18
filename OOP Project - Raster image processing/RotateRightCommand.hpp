/*
	#### OOP Project - Raster image processing ####
			FMI OOP - Informatics, 2025
*/

#ifndef __ROTATE_RIGHT_COMMAND_HPP_INCLUDED__
#define __ROTATE_RIGHT_COMMAND_HPP_INCLUDED__

#include "Command.hpp"

/// Command that rotates the image to the right (90 degrees clockwise).
///
/// Similar to RotateLeftCommand, this uses context state to determine how to transform the image matrix.
class RotateRightCommand : public ImageCommand {
public:
	virtual ImageCommand* clone() const override { return new RotateRightCommand(*this); }

	/// Updates the context to reflect a right rotation request.
    /// @param context The image transformation context.
	virtual void loadInfo(Context& context) const override;

	/// Executes the actual image rotation based on the current context.
	/// 
	/// @param image The image to rotate.
	/// @returns true if successful.
	/// @note the maximum amount of rotations that can be done are 2 due to identities
	/// either one to the right or 180, otherwise it is one left rotation or a 180 flip
	virtual bool execute(Image* image) const override;
};


class RotateRightCommandHandler : public CommandHandler<ImageCommand> {
public:

	virtual const char* getType() const override { return "rotate right"; }
	virtual ImageCommand& getCommand() const override {
		static RotateRightCommand rotate_r;
		return rotate_r;
	}

	virtual bool canHandle(std::istream& is) const override;
};


#endif