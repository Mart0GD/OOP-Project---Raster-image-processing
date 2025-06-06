/*
	#### OOP Project - Raster image processing ####
			FMI OOP - Informatics, 2025
*/

#ifndef __MONOCHROME_HPP_INCLUDED__
#define __MONOCHROME_HPP_INCLUDED__

#include "Command.hpp"

class MonochromeCommand : public ImageCommand {
public:
	virtual ImageCommand* clone() const override { return new MonochromeCommand(*this); }

	virtual void loadInfo(Context& context) const override;
	virtual bool execute(Image* image) const override;
};


class MonochromeCommandHandler : public CommandHandler<ImageCommand> {
public:
	virtual const char* getType() const override { return "monochrome"; }
	virtual ImageCommand& getCommand() const override {
		static MonochromeCommand mono;
		return mono;
	}
};

#endif
