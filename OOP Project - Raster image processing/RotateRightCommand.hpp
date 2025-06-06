/*
	#### OOP Project - Raster image processing ####
			FMI OOP - Informatics, 2025
*/

#ifndef __ROTATE_RIGHT_COMMAND_HPP_INCLUDED__
#define __ROTATE_RIGHT_COMMAND_HPP_INCLUDED__

#include "Command.hpp"

class RotateRightCommand : public ImageCommand {
public:
	virtual ImageCommand* clone() const override { return new RotateRightCommand(*this); }

	virtual void loadInfo(Context& context) const override;
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