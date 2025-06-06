/*
	#### OOP Project - Raster image processing ####
			FMI OOP - Informatics, 2025
*/

#ifndef __SAVE_COMMAND_HPP_INCLUDED__
#define __SAVE_COMMAND_HPP_INCLUDED__

#include "Command.hpp"

class SessionManager;

class SaveCommand : public SessionCommand {
public:
	virtual SessionCommand* clone() const override { return new SaveCommand(*this); }

	virtual bool execute(Session* session, std::istream& is) override;
};


class SaveCommandHandler : public CommandHandler<SessionCommand> {
public:
	virtual const char* getType() const override { return "save"; }
	virtual SessionCommand& getCommand() const override {
		static SaveCommand save;
		return save;
	}
};

#endif // !__SAVE_COMMAND_HPP_INCLUDED__



