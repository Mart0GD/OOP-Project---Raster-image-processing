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

/// Represents a single editing session containing images and applied commands.
class Session {
public:

	/// Constructs a new session.
	///
	/// Calls start()
	Session();

	/// Destructor that frees all dynamically allocated images.
	~Session();

	/// Sessions are not copyable.
	Session(const Session& other) = delete;
	Session& operator=(const Session& other) = delete;

	/// Adds an image to the session
	/// 
	/// Also sets the passed image startCommandIndex to the last command Index in the undo stack
    /// @param file Pointer to the image to add.
    /// @returns true if the image was added successfully.
	bool addImage(Image* file);

	/// Adds a command to the session's undo stack.
    /// @param command Pointer to the image command to add.
    /// @returns true if the command was added.
	bool addCommand(ImageCommand* command);

	/// Executes all stored commands on the images.
	/// 
	/// If the undo or redo stacks are not empty we call the manipulate method (separating the logic)
	/// @param images A vector of copied image pointers for manipulation
	/// @returns true if execution succeeded.
	bool executeCommands(std::vector<Image*>& images);

	/// Undoes the last executed command.
	/// @returns true if a command was undone.
	bool undoCommand();

	/// Redoes the last undone command.
    /// @returns true if a command was redone.
	bool redoCommand();

	/// Getter for all images in the session.
	std::vector<Image*> getImages() { return images; }

	/// Getter for the current command index in the undo stack.
	size_t getCurrentCommandIndex() const { return undoStack.size(); }

	/// Retrieves a specific image by filename.
	/// @param filename The filename of the image to retrieve.
	/// @returns Pointer to the image if found, otherwise nullptr.
	Image* const getImage(std::string filename) const;

	/// Checks if there is unsaved work in the session.
	/// @returns true if unsaved changes exist.
	bool hasUnsavedWork() const { return saved; }

	/// Starts a new session.
	/// 
	/// Waits for a load command to be passed from the console.
	/// Helps the user with messages on error 
	void start();

	/// Runs the main session loop waiting for the exit command.
	void run();

	/// Flags the session to exit.
	void exit() { exitFlag = true; }

private:
	/// Clears all the stored images inside the session.
	void clearData();

	/// Two stage image manipulation.
	/// 
	/// First stage -> load images context's
	/// Second stage -> execute commands corresponding to the images context's
	/// @param copy A vector of image copies to manipulate.
	/// @returns true if manipulation succeeded.
	bool manipulate(std::vector<Image*>& copy);

private:
	std::vector<Image*> images;               ///< Stored images in the session.
	std::vector<ImageCommand*> undoStack;     ///< Stack of executed commands.
	std::vector<ImageCommand*> redoStack;     ///< Stack of undone commands.

	bool exitFlag;							  ///< Indicates whether the session should exit.
	bool saved;								  ///< Indicates whether the current state is saved.
};

#endif // !__SESSION_HPP_INCLUDED__
