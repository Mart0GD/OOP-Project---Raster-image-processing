/*
	#### OOP Project - Raster image processing ####
			FMI OOP - Informatics, 2025
*/

#ifndef __ADD_COMMAND_HPP_INCLUDED__
#define __ADD_COMMAND_HPP_INCLUDED__

#include "Command.hpp"

class AddCommand : public SessionCommand {
public:
	virtual SessionCommand* clone() const override { return new AddCommand(*this); }

	virtual bool execute(Session* session, std::istream& is) override;
};

class AddCommandHandler : public CommandHandler<SessionCommand> {
public:

	virtual const char* getType() const override { return "add"; }
	virtual SessionCommand& getCommand() const override {
		static AddCommand add;
		return add;
	}
};

#endif // !__ADD_COMMAND_HPP_INCLUDED__
