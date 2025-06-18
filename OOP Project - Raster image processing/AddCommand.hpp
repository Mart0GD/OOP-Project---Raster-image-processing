/*
	#### OOP Project - Raster image processing ####
			FMI OOP - Informatics, 2025
*/

#ifndef __ADD_COMMAND_HPP_INCLUDED__
#define __ADD_COMMAND_HPP_INCLUDED__

#include "Command.hpp"

/// Command that adds a new image to the current editing seassion
class AddCommand : public SessionCommand {
public:
	virtual SessionCommand* clone() const override { return new AddCommand(*this); }

	/// Executes the command by loading and adding an image to the session.
	/// 
	/// Reads the filename from the input stream, loads the corresponding image file using the
	/// FileFactory, creates an Image, and adds it to the session.
	/// Handles and reports all potential failures during this process.
	///
	/// @param session Pointer to the current session.
	/// @param is Input stream containing the filename.
	/// @returns true if the image was successfully loaded and added.
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
