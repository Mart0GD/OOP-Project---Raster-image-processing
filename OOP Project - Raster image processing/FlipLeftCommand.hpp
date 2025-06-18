/*
	#### OOP Project - Raster image processing ####
			FMI OOP - Informatics, 2025
*/

#ifndef __FLIP_LEFT_COMMAND_HPP_INCLUDED__
#define __FLIP_LEFT_COMMAND_HPP_INCLUDED__

#include "Command.hpp"

/// Command representing a horizonal image flip
class FlipLeftCommand : public ImageCommand {
public:
	virtual ImageCommand* clone() const override { return new FlipLeftCommand(*this); }

	/// flips the hFlip flag inside the context
	/// @param context execution context to manipulate 
	virtual void loadInfo(Context& context) const override;

	/// Flips the image horizonatlly if the hFlip flag is on
	/// 
	/// @param image image to manipulate
	/// returns true if the operation is successful and false otherwise
	/// @note the flips are executed after rotations for correctness.
	/// If the flip command appears before all rotations are executed 
	/// it will be skipped 
	virtual bool execute(Image* image) const override;
};


class FlipLeftCommandHandler : public CommandHandler<ImageCommand> {
public:

	virtual const char* getType() const override { return "flip left"; }
	virtual ImageCommand& getCommand() const override {
		static FlipLeftCommand flip_l;
		return flip_l; 
	}

	virtual bool canHandle(std::istream& is) const override;
};

#endif // !__FLIP_LEFT_COMMAND_HPP_INCLUDED__
