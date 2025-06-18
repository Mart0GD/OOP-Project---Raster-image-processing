/*
	#### OOP Project - Raster image processing ####
			FMI OOP - Informatics, 2025
*/

#ifndef __LOAD_COMMAND_HPP_INCLUDED__
#define __LOAD_COMMAND_HPP_INCLUDED__

#include "Command.hpp"
#include <vector>
#include <string>

/// Command responsible for loading images on session startup
///
/// @note a session can be started without any images, they can be added later on with AddCommand
class LoadCommand : public SessionCommand {
public:
	virtual SessionCommand* clone() const override { return new LoadCommand(*this); }

	/// Executes the command by loading and adding images to the session.
	/// 
	/// Reads the filenames from the input stream, loads the corresponding image files using the
	/// FileFactory, creates the Images, and adds them to the session one by one.
	/// Handles and reports all potential failures during this process.
	/// Clears all dynamically allocated memory on failure
	/// 
	/// @param session Pointer to the current session.
	/// @param is used to read the filenames for image generation
	/// @returns true if all images were successfully created and added to the editing session
	virtual bool execute(Session* session, std::istream& is) override;
};

static LoadCommand load;

// Load command creator --> reads the filenames and passes them to the ctor
class LoadCommandHandler : public CommandHandler<SessionCommand> {
public:

	virtual const char* getType() const override { return "load"; }
	virtual SessionCommand& getCommand() const override {
		static LoadCommand load;
		return load;
	}
};

#endif // !__LOAD_COMMAND_HPP_INCLUDED__
