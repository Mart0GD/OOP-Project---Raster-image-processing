/*
	#### OOP Project - Raster image processing ####
			FMI OOP - Informatics, 2025
*/

#ifndef __UNDO_COMMAND_HPP_INCLUDED__
#define __UNDO_COMMAND_HPP_INCLUDED__

#include "Command.hpp"

/// Command that undoes the last action inside the editing session
class UndoCommand : public SessionCommand {
public:
	virtual SessionCommand* clone() const override { return new UndoCommand(*this); }

	/// Pops the last command off the main stack inside the session and puts on the redo stack
	/// 
	/// @param session Pointer to the current session.
	/// @param is Not used (included for interface compliance).
	/// @returns true is the command is successfully undone
	virtual bool execute(Session* session, std::istream& is) override;
};

class UndoCommandHandler : public CommandHandler<SessionCommand> {
public:
	virtual const char* getType() const override { return "undo"; }
	virtual SessionCommand& getCommand() const override {
		static UndoCommand undo;
		return undo;
	}
};


#endif // !__UNDO_COMMAND_HPP_INCLUDED__
