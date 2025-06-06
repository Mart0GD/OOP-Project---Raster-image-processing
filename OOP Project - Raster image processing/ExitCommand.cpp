#include "ExitCommand.hpp"
#include "SaveCommand.hpp"
#include "Session.hpp"

bool ExitCommand::execute(Session* session, std::istream& is) {
	if (!is) return false;

	if (session->hasUnsavedWork()) {
		std::cout << "Session contains unsaved work. Save it now (y/n)?\n";

		const char yes = 'y', no = 'n';

		char answer;
		do
		{
			answer;
			std::cin >> answer;
		} while (answer != yes && answer != no);
		

		if (answer == yes) {
			SaveCommand save;
			save.execute(session, is);
		}
	}

	session->exit();
	return true;
}

static ExitCommandHandler exitCmd;