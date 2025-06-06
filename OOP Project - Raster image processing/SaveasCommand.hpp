/*
	#### OOP Project - Raster image processing ####
			FMI OOP - Informatics, 2025
*/

#ifndef __SAVEAS_HPP_INCLUDED__
#define __SAVEAS_HPP_INCLUDED__

#include "Command.hpp"

#include <string>
#include <vector>

class SessionManager;

class SaveasCommand : public SessionCommand {
public:
	virtual SessionCommand* clone() const override { return new SaveasCommand(*this); }

	virtual bool execute(Session* session, std::istream& is) override;
};

class SaveasCommandHandler : public CommandHandler<SessionCommand> {
public:

	virtual const char* getType() const { return "saveas"; }
	virtual SessionCommand& getCommand() const {
		static SaveasCommand saveas;
		return saveas;
	}
};

#endif // !__SAVEAS_HPP_INCLUDED__
