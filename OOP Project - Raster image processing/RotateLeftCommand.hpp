/*
	#### OOP Project - Raster image processing ####
			FMI OOP - Informatics, 2025
*/

#ifndef __ROTATE_LEFT_COMMAND_HPP_INCLUDED__
#define __ROTATE_LEFT_COMMAND_HPP_INCLUDED__

#include "Command.hpp"

class RotateLeftCommand : public ImageCommand {
public:
	virtual ImageCommand* clone() const override { return new RotateLeftCommand(*this); }

	virtual void loadInfo(Context& context) const override;
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