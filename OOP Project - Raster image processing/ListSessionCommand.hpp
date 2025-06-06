/*
	#### OOP Project - Raster image processing ####
			FMI OOP - Informatics, 2025
*/

#ifndef __LIST_SESSION_COMMAND_HPP_INCLUDED__
#define __LIST_SESSION_COMMAND_HPP_INCLUDED__

#include "Command.hpp"

class ListSessionCommand : public SessionCommand {
public:
	virtual SessionCommand* clone() const override { return new ListSessionCommand(*this); }

	virtual bool execute(Session* session, std::istream& is) override;
};


class ListSessionCommandHandler: public CommandHandler<SessionCommand> {
public:
	virtual const char* getType() const override { return "list session"; }
	virtual SessionCommand& getCommand() const override {
		static ListSessionCommand list;
		return list;
	}

	virtual bool canHandle(std::istream& is) const override;
};

#endif // !__LIST_SESSION_COMMAND_HPP_INCLUDED__
