/*
	#### OOP Project - Raster image processing ####
			FMI OOP - Informatics, 2025
*/

#ifndef __PASTE_COMMAND_HPP_INCLUDED__
#define __PASTE_COMMAND_HPP_INCLUDED__

#include "Command.hpp"


class PasteCommand : public SessionCommand {
public:
	virtual SessionCommand* clone() const { return new PasteCommand(*this); }

	virtual bool execute(Session* session, std::istream& is) override;
};

class PasteCommandHandler : public CommandHandler<SessionCommand> {
public:
	virtual const char* getType() const override { return "paste"; }
	virtual SessionCommand& getCommand() const override {
		static PasteCommand paste;
		return paste;
	}
};

#endif // !__PASTE_COMMAND_HPP_INCLUDED__
