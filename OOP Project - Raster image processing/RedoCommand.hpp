/*
	#### OOP Project - Raster image processing ####
			FMI OOP - Informatics, 2025
*/

#ifndef __REDO_COMMAND_HPP_INCLUDED__
#define __REDO_COMMAND_HPP_INCLUDED__

#include "Command.hpp"

/// Command that redoes the last undone action inside the editing session
class RedoComand : public SessionCommand{
public:
	virtual SessionCommand* clone() const override { return new RedoComand(*this); }

	/// Pops the last command off the redo stack inside the session and puts it back inside the main stack
	/// 
	/// @param session Pointer to the current session.
	/// @param is Not used (included for interface compliance).
	/// @returns true is the command is successfully redone
	virtual bool execute(Session* session, std::istream& is) override;
};

class RedoCommandHandler : public CommandHandler<SessionCommand> {
public:

	virtual const char* getType() const override { return "redo"; }
	virtual SessionCommand& getCommand() const override {
		static RedoComand redo;
		return redo;
	}
};


#endif // !__REDO_COMMAND_HPP_INCLUDED__
