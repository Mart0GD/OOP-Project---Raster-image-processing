/*
	#### OOP Project - Raster image processing ####
			FMI OOP - Informatics, 2025
*/

#include "Session.hpp"
#include "CommandFactory.hpp"
#include "Command.hpp"

int main() {

	// register the commands safely
	if (!CommandFactory<ImageCommand, CommandHandler<ImageCommand>>::getInstance().registerCommands())
		return -1;

	Session session; // auto start
	return 0;
}

