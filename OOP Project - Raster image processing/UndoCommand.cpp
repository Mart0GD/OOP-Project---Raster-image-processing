#include "UndoCommand.hpp"
#include "Session.hpp"

bool UndoCommand::execute(Session* session, std::istream& is) {

	session->undoCommand();
	return true; // return true so the error messages don't overlap 
}

static UndoCommandHandler undoCmd;
