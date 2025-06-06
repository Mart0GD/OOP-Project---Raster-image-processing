/*
	#### OOP Project - Raster image processing ####
			FMI OOP - Informatics, 2025
*/

#ifndef __NEGATICE_COMMAND_HPP_INCLUDED__
#define __NEGATICE_COMMAND_HPP_INCLUDED__

#include "Command.hpp"

class NegativeCommand : public ImageCommand {
public:
	virtual ImageCommand* clone() const override { return new NegativeCommand(*this); }

	virtual void loadInfo(Context& context) const override;
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

