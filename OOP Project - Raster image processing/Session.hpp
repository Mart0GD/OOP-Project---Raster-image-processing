/*
	#### OOP Project - Raster image processing ####
			FMI OOP - Informatics, 2025
*/

#ifndef __SESSION_HPP_INCLUDED__
#define __SESSION_HPP_INCLUDED__

#include <vector>
#include <string>

class Image;
class ImageCommand;

class Session {

	friend class Snapshot;

public:
	Session();
	~Session(); // dynamic image allocation we need a dtor

	// we should not be able to copy a session
	Session(const Session& other) = delete;
	Session& operator=(const Session& other) = delete;


	bool addImage(Image* file);
	bool addCommand(ImageCommand* command);
	std::vector<Image*> executeCommands();
	bool undoCommand();
	bool redoCommand();

	std::vector<Image*> getImages() { return images; }
	Image* const getImage(std::string filename) const;
	size_t getCurrentCommandIndex() const { return undoStack.size(); }

	bool hasUnsavedWork() const { return saved; }

	void start();
	void run();
	void exit() { exitFlag = true; }

private:
	void clearData();
	bool manipulate(std::vector<Image*>& copy);

private:
	std::vector<Image*> images;

	std::vector<ImageCommand*> undoStack;
	std::vector<ImageCommand*> redoStack;

	bool exitFlag;
	bool saved;
};

#endif // !__SESSION_HPP_INCLUDED__
