/*
	#### OOP Project - Raster image processing ####
			FMI OOP - Informatics, 2025
*/

#ifndef __SAVEAS_HPP_INCLUDED__
#define __SAVEAS_HPP_INCLUDED__

#include "Command.hpp"

#include <string>
#include <vector>

/// Command that saves all session images to their original filenames.
///
/// This command:
/// - Creates deep copies of all images
/// - Applies all pending transformations
/// - Saves them using user provided names
///
/// If a filename is not provided for a given image, a timestamped default name is used.
/// 
/// @note If two images share the same filename, 
/// the command delays subsequent saves to prevent overwriting conflicts.
class SaveasCommand : public SessionCommand {
public:
	virtual SessionCommand* clone() const override { return new SaveasCommand(*this); }

	/// Executes the saveas operation on the session's image list.
	///
	/// - Accepts a space-separated list of output filenames from the input stream 
	///   which should be less than the images inside the session.
	/// 
	/// - Makes a copy of all the images, resets thir contexts, re-applies all commands based on the contexts
	///   and saves the modified copies.
	/// 
	/// - Calls each image's file save method.
	///
	/// @param session Pointer to the current session.
	/// @param is Input stream containing optional output filenames.
	/// @returns true if all steps completed (some images may still fail to save).
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
