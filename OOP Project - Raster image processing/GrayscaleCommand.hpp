/*
	#### OOP Project - Raster image processing ####
			FMI OOP - Informatics, 2025
*/

#ifndef __GRAYSCALE_COMMAND_HPP_INCLUDED__
#define __GRAYSCALE_COMMAND_HPP_INCLUDED__

#include "Command.hpp"

class GrayscaleCommand : public ImageCommand {
public:
	virtual ImageCommand* clone() const override { return new GrayscaleCommand(*this); }

	virtual void loadInfo(Context& context) const override;
	virtual bool execute(Image* image) const override;
};


class GrayscaleCommandHandler : public CommandHandler<ImageCommand> {
public:
	virtual const char* getType() const override { return "grayscale"; }
	virtual ImageCommand& getCommand() const override {
		static GrayscaleCommand gray;
		return gray;
	}
};

#endif // !__SESSION_MANAGER_HPP_INCLUDED__
