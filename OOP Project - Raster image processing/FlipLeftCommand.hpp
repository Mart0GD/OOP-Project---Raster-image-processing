/*
	#### OOP Project - Raster image processing ####
			FMI OOP - Informatics, 2025
*/

#ifndef __FLIP_LEFT_COMMAND_HPP_INCLUDED__
#define __FLIP_LEFT_COMMAND_HPP_INCLUDED__

#include "Command.hpp"

class FlipLeftCommand : public ImageCommand {
public:
	virtual ImageCommand* clone() const override { return new FlipLeftCommand(*this); }

	virtual void loadInfo(Context& context) const override;
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
