/*
	#### OOP Project - Raster image processing ####
			FMI OOP - Informatics, 2025
*/

#ifndef __SAVE_COMMAND_HPP_INCLUDED__
#define __SAVE_COMMAND_HPP_INCLUDED__

#include "Command.hpp"

/// Command that saves all session images to their original filenames.
///
/// This command:
/// - Creates deep copies of all images
/// - Applies all pending transformations
/// - Saves them using timestamped default names.
///
/// @note If two images share the same filename, 
/// the command delays subsequent saves to prevent overwriting conflicts.
class SaveCommand : public SessionCommand {
public:
	virtual SessionCommand* clone() const override { return new SaveCommand(*this); }

	/// Executes the save operation using the original filenames of the images.
	///
	/// - Makes a copy of all the images, resets thir contexts, re-applies all commands based on the contexts
	///   and saves the modified copies.
	/// 
	/// - Calls each image's file save method.
	///
	/// @param session Pointer to the active session.
	/// @param is Not used (included for interface compliance).
	/// @returns true if execution completes (some saves may still fail).
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



