/*
	#### OOP Project - Raster image processing ####
			FMI OOP - Informatics, 2025
*/

#ifndef __FLIP_TOP_COMMAND_HPP_INCLUDED__
#define __FLIP_TOP_COMMAND_HPP_INCLUDED__

#include "Command.hpp"

class FlipTopCommand : public ImageCommand {
public:
	virtual ImageCommand* clone() const override { return new FlipTopCommand(*this); }

	virtual void loadInfo(Context& context) const override;
	virtual bool execute(Image* image) const override;
};

class FlipTopCommandHandler : public CommandHandler<ImageCommand> {
public:
	virtual const char* getType() const override { return "flip top"; }
	virtual ImageCommand& getCommand() const override {
		static FlipTopCommand flip_t;
		return flip_t;
	}

	virtual bool canHandle(std::istream& is) const override;
};

#endif // !__FLIP_TOP_COMMAND_HPP_INCLUDED__
