#include "Session.hpp"

#include "File.hpp"
#include "Context.hpp"
#include "CommandFactory.hpp"
#include "Helpers.hpp"
#include "Command.hpp"

#include "LoadCommand.hpp"
#include "RotateLeftCommand.hpp"
#include "RotateRightCommand.hpp"

#include <sstream>

Session::Session() 
	: exitFlag(false), saved(false) { start(); }
Session::~Session() {
	clearData();
}

void Session::start() {

	bool loaded = false;

	CommandFactory<SessionCommand, CommandHandler<SessionCommand>>& scc =
		CommandFactory<SessionCommand, CommandHandler<SessionCommand>>::getInstance();

	do
	{
		try
		{
			std::string text;
			std::getline(std::cin, text);

			std::istringstream iss(text);
			if (!iss) { std::cout << "invalid input!";  continue; }

			SessionCommand* command = scc.getCommand(iss);

			LoadCommand* cast = dynamic_cast<LoadCommand*>(command);
			if (cast && cast->execute(this, iss)) break;
			else std::cout << "------ Start session first! ------\n";
		}
		catch (const std::exception& e) {
			std::cout << e.what();
		}

	} while (!loaded);

	run(); // run session
}
void Session::run() {

	CommandFactory<SessionCommand, CommandHandler<SessionCommand>>& scc =
		CommandFactory<SessionCommand, CommandHandler<SessionCommand>>::getInstance();

	CommandFactory<ImageCommand, CommandHandler<ImageCommand>>& icc =
		CommandFactory<ImageCommand, CommandHandler<ImageCommand>>::getInstance();

	do
	{
		try
		{
			std::string text;
			std::getline(std::cin, text);

			std::istringstream iss(text);
			if (!iss) { std::cout << "invalid input!";  continue; }

			SessionCommand* sc = nullptr;
			ImageCommand* ic = nullptr;

			sc = scc.getCommand(iss);
			if(!sc) ic = icc.getCommand(iss);

			if (sc) {
				if (dynamic_cast<LoadCommand*>(sc)) {
					std::cout << "------ Session already started! ------\n";
					continue;
				}

				sc->execute(this, iss);
			}
			else if (ic) addCommand(ic);
			else std::cout << "------ Invalid command! ------\n";
		}
		catch (const std::exception& e) { std::cout << e.what(); }

	} while (!exitFlag);
}

bool Session::addImage(Image* image) {
	if (!image) return false;

	try { 
		images.push_back(image);
		image->setStartCommandIndex(getCurrentCommandIndex());
	}
	catch (...) {
		std::cout << "------ Failed to add image! ------\n";
		return false;
	}

	std::cout << "------ Image " << image->getFile()->getFilename() << " added! ------\n";
	return true;
}
bool Session::addCommand(ImageCommand* command) {
	if (!command) return false;

	try { undoStack.push_back(command); }
	catch (...) { 
		std::cout << "------ Add failed! ------\n";
		return false; 
	}

	if(saved) saved = false;
	std::cout << "------ Command added! ------\n";
	return true;
}
bool Session::executeCommands(std::vector<Image*>& images) {
	if (undoStack.empty() && redoStack.empty()) return false;

	manipulate(images);

	saved = true;
	return true;
}

bool Session::undoCommand() {
	if (undoStack.empty()) {
		std::cout << "No commands to undo!\n";
		return false;
	}

	ImageCommand* topCommand = undoStack.back(); 
	undoStack.pop_back(); // won't delete the topCommand object, only the one inside

	try { redoStack.push_back(topCommand); }
	catch (...) {
		std::cout << "------ undo failed! ------\n";
		return false;
	}

	std::cout << "------ Command undone! ------\n";
	return true;
}
bool Session::redoCommand() {
	if (redoStack.empty()) {
		std::cout << "No commands to redo!\n";
		return false;
	}

	ImageCommand* command = redoStack.back();
	redoStack.pop_back();

	bool res = addCommand(command);
	return res;
}

void Session::clearData() {
	for (Image* image : images)
		delete image;
	images.clear();
}

Image* const Session::getImage(std::string filename) const {
	for (Image* image : images)
		if (filename == image->getFile()->getFilename()) return image;

	return nullptr;
}
bool Session::manipulate(std::vector<Image*>& copy)
{
	// first add command info
	for (size_t i = 0; i < undoStack.size(); i++) {
		for (Image* image : copy) {

			// image initialized before command
			if (image->getStartCommandIndex() <= i) undoStack[i]->loadInfo(image->getContext());
		}
	}

	std::vector<ImageCommand*> commands =
		CommandFactory<ImageCommand, CommandHandler<ImageCommand>>::getInstance().getCommands();

	// then execute it according to context
	for (size_t i = 0; i < commands.size(); i++) {
		for (Image* image : copy) {
			commands[i]->execute(image);
		}
	}

	redoStack.clear(); // static pointer data

	// push images back
	for (Image* image : images)
	{
		if (image->getStartCommandIndex() >= undoStack.size())
			image->setStartCommandIndex(undoStack.size()); // set at the end
	}
	return true;
}
