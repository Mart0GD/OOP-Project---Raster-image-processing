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


/// Abstract class representing an image command.
///
/// Defines the interface for commands that operate on individual images.
class ImageCommand {
public:
	ImageCommand() = default;
	virtual ~ImageCommand() noexcept = default;

	/// Creates a polymorphic copy of the command.
	/// 
	/// @return Pointer to the cloned ImageCommand.
	/// @throws on unsuccessful clone
	virtual ImageCommand* clone() const = 0;

	/// Loads necessary data from the context before execution.
	/// 
	/// @param context The execution context.
	virtual void loadInfo(Context& context) const = 0;


	/// Executes the command on the provided image.
	/// 
	/// @param image Pointer to the image to operate on.
	/// @return True if the operation was successful.
	virtual bool execute(Image* image) const = 0;
};


/// Abstract class representing a session command.
///
///Separates console input handling from business logic.
class SessionCommand {
public:
	SessionCommand() = default;
	virtual ~SessionCommand() noexcept = default;

	/// Creates a polymorphic copy of the session command.
	/// 
	/// @return Pointer to the cloned SessionCommand.
	/// @throws on unsuccessful clone
	virtual SessionCommand* clone() const = 0;

	/// Executes the command on a session using input stream.
	/// 
	///@param session Pointer to the session object.
	///@param is Input stream for command parameters.
	///@return True if execution was successful.
	virtual bool execute(Session* session, std::istream& is) = 0;
};


/// Abstract class for accessing and dispatching a command.
///
/// Holds logic for recognizing and extracting the data needed to construct command objects.
/// @tparam CommandType Type of the command (e.g., ImageCommand or SessionCommand).
template <typename CommandType>
class CommandHandler {
public:
	CommandHandler();
	virtual ~CommandHandler() noexcept = default;

	/// Returns the keyword that this handler recognizes.
	/// 
	/// @return The keyword c-string.
	virtual const char* getType() const = 0;

	/// Returns a reference to a static command instance.
	/// 
	/// @return Reference to a CommandType object.
	virtual CommandType& getCommand() const = 0;

	/// Determines whether the handler can process the input.
	/// 
	/// @param is Input stream to check.
	/// @return True if the handler can process the input.
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

