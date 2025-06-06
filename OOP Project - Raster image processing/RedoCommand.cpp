#include "RedoCommand.hpp"
#include "Session.hpp"

bool RedoComand::execute(Session* session, std::istream& is) {
	if (!is) return false;

	session->redoCommand();
	return true; // return true so the error messages don't overlap 
}

static RedoCommandHandler redoCmd;