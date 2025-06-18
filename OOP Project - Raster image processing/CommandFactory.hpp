/*
	#### OOP Project - Raster image processing ####
			FMI OOP - Informatics, 2025
*/

#ifndef __COMMAND_MANAGER_HPP_INCLUDED__
#define __COMMAND_MANAGER_HPP_INCLUDED__

#include <string>
#include <vector>
#include <iostream>

#include "Enums.hpp"

/// A template factory and registry for commands using the singleton and Factory design patterns
/// 
/// @tparam T1 The base type of the commands (e.g., ImageCommand or SessionCommand).
/// @tparam T2 The handler type used to recognize and instantiate commands.
/// @note The code for the Command factory is based on the lectue examples provided for the IS major.
/// @note The idea and execution are implementation specific.
/// @attention No copying allowed 
/// ### Example
/// ~~~~~~~~~~~~~~~~~~~ .cpp
/// 
/// CommandFactory<ImageCommand, CommandHandler<ImageCommand>>& instance =
/// CommandFactory<ImageCommand, CommandHandler<ImageCommand>>::getInstance();
/// 
/// ~~~~~~~~~~~~~~~~~~~
template <typename T1, typename T2>
class CommandFactory {
public:
	
	/// Returns the singleton instance of the CommandFactory.
	static CommandFactory& getInstance();

	/// Registers a handler in the factory.
	///
	/// Static handler instances are registerd before the application starts 
	/// for less complexity 
	/// @throws std::bad_alloc
	void registerHandler(T2* handler);

	/// Registers all commands from the registered handlers.
	/// 
	/// Static instances of Session and Image commands are registerd 
	/// in order to be used for second stage image manipulation
	bool registerCommands();

	/// Retrieves a command by parsing input from a stream.
	///
	/// Used in the command parsing stage of the application
	T1* getCommand(std::istream& is);

	/// Gets the list of all registered commands by extracting them from the handlers
	const std::vector<T1*>& getCommands() const { return commands; }

private:

	/// Finds the handler capable of handling the command based on stream input.
	T2* getHandler(std::istream& is);

private:
	CommandFactory() = default;
	~CommandFactory() = default;
	CommandFactory(const CommandFactory&) = delete;
	CommandFactory& operator=(const CommandFactory&) = delete;

private:
	/// Collection of registered command handlers.
	std::vector<T2*> handlers;

	/// Collection of created command instances.
	std::vector<T1*> commands;
};

#include "CommandFactory.imp"
#endif // !COMMAND_MANAGER_HPP

// ***********************************************************************
//	The code for the Command factory is based on the lectue examples provided for the IS major.
//	The idea and execution are implementation specific.
// ***********************************************************************
