/*
	#### OOP Project - Raster image processing ####
			FMI OOP - Informatics, 2025
*/

#ifndef __EXIT_COMMAND_HPP_INCLUDED__
#define __EXIT_COMMAND_HPP_INCLUDED__

#include "Command.hpp"

/// Command that closes the editing session
class ExitCommand : public SessionCommand {
public:
	virtual SessionCommand* clone() const override { return new ExitCommand(*this); }

	/// Flips the exit flag inside the editing session
	/// 
	/// is unsaved work is present the user is prompted to save or delete it
	/// @param session Pointer to the current session.
	/// @param is Input stream for user input.
	/// @returns true if the program is successfully saved and closed
	virtual bool execute(Session* session, std::istream& is) override;
};

class ExitCommandHandler : public CommandHandler<SessionCommand> {
public:
	virtual const char* getType() const override { return "exit"; }
	virtual SessionCommand& getCommand() const override {
		static ExitCommand exit_c;
		return exit_c;
	}
};

#endif // !__EXIT_COMMAND_HPP_INCLUDED__
