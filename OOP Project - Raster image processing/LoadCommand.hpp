/*
	#### OOP Project - Raster image processing ####
			FMI OOP - Informatics, 2025
*/

#ifndef __LOAD_COMMAND_HPP_INCLUDED__
#define __LOAD_COMMAND_HPP_INCLUDED__

#include "Command.hpp"
#include <vector>
#include <string>

// Class responsible for loading images in our program workflow
class LoadCommand : public SessionCommand {
public:
	virtual SessionCommand* clone() const override { return new LoadCommand(*this); }

	// creates images using our factory for images 
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
