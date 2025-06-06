/*
	#### OOP Project - Raster image processing ####
			FMI OOP - Informatics, 2025
*/

#ifndef __ImageCommand_HPP_INCLUDED__
#define __ImageCommand_HPP_INCLUDED__

#include "Context.hpp"
#include "CommandFactory.hpp"
#include <iostream>

class Session;
class Image;

// Abstarct class representing an image command 
class ImageCommand {
public:
	ImageCommand() = default;
	virtual ~ImageCommand() noexcept = default;
	virtual ImageCommand* clone() const = 0;

	virtual void loadInfo(Context& context) const = 0;
	virtual bool execute(Image* image) const = 0;
};


//  Abstract class representing a session command
//  Seprating the logic between console input and business logic
class SessionCommand {
public:
	SessionCommand() = default;
	virtual ~SessionCommand() noexcept = default;
	virtual SessionCommand* clone() const = 0;

	virtual bool execute(Session* session, std::istream& is) = 0;
};


// Abstract class for giving us access to a command
// Holds the logic for extracting the data for our command classes
template <typename CommandType>
class CommandHandler {
public:
	CommandHandler();
	virtual ~CommandHandler() noexcept = default;

	virtual const char* getType() const = 0;
	virtual CommandType& getCommand() const = 0;

	virtual bool canHandle(std::istream& is) const;
};

template <typename CommandType>
CommandHandler<CommandType>::CommandHandler() {
	CommandFactory<CommandType, CommandHandler<CommandType>>::getInstance().registerHandler(this);
}

template <typename CommandType>
bool CommandHandler<CommandType>::canHandle(std::istream& is) const {
	try
	{
		std::string text;

		is >> text;
		if (!is || text != getType()) return false;
		return true;
	}
	catch (const std::exception& e)
	{
		std::cout << e.what();
		return false;
	}
	
}


#endif // !__GRAYSCALE_SESSION_COMMAND_HPP_INCLUDED__

