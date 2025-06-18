/*
	#### OOP Project - Raster image processing ####
			FMI OOP - Informatics, 2025
*/

#ifndef __PASTE_COMMAND_HPP_INCLUDED__
#define __PASTE_COMMAND_HPP_INCLUDED__

#include "Command.hpp"

/// Command that creates a new image by placing two existing images one over the other
class PasteCommand : public SessionCommand {
public:
	virtual SessionCommand* clone() const { return new PasteCommand(*this); }

	/// Places the first image onto the other at a specified position
	/// 
	/// Reads two filenames and two integer coordinate values from the input stream
	/// Searches for the images inside the editing session. 
	/// If the names are valid, pastes the first image onto the other
	/// 
	/// @param session Pointer to the current session.
	/// @param is used to read the filenames for the two images
	/// @returns true if the images are valid and pasting occurs without any errors
	/// @note the file format of the newly created image is the higher one of the two
	/// @see Image::paste();
	virtual bool execute(Session* session, std::istream& is) override;
};


class PasteCommandHandler : public CommandHandler<SessionCommand> {
public:
	virtual const char* getType() const override { return "paste"; }
	virtual SessionCommand& getCommand() const override {
		static PasteCommand paste;
		return paste;
	}
};

#endif // !__PASTE_COMMAND_HPP_INCLUDED__
