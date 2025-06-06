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

template <typename T1, typename T2>
class CommandFactory {
public:
	
	// returning a reference to the static instance
	static CommandFactory& getInstance();

	void registerHandler(T2* handler);
	bool registerCommands();

	T1* getCommand(std::istream& is);
	T1* getCommand(const std::string& keyword);
	const std::vector<T1*>& getCommands() const { return commands; }

private:

	// searching for a creator in our collection
	T2* getHandler(std::istream& is);

private:
	CommandFactory() = default;
	~CommandFactory() = default;
	CommandFactory(const CommandFactory&) = delete;
	CommandFactory& operator=(const CommandFactory&) = delete;

	/*
		No copying, nor constructing outside of this class
		We are implementing the singleton and Factory design patterns for this class
	*/

private:
	std::vector<T2*> handlers;
	std::vector<T1*> commands;
};


template<typename T1, typename T2>
T1* CommandFactory<T1,T2>::getCommand(const std::string& keyword) {

	for (T2* handler : handlers)
		if (handler->getType() == keyword) return &handler->getCommand();

	return nullptr;
}

#include "CommandFactory.imp"
#endif // !COMMAND_MANAGER_HPP

// ***********************************************************************
//	The code for the Command factory is based on the lectue examples provided for the IS major.
//	The idea and execution are implementation specific.
// ***********************************************************************
