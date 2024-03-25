#include "display.h"

void display::invalidDirPath(std::string dirPath)
{
	std::cout << '\"' + dirPath + "\" invalid path\n";
}
void display::invalidFilePath(std::string fullPath)
{
	std::cout << '\"' + fullPath + "\" not found.\n";
}
void display::emptyList()
{
	std::cout << "List is empty\n";
}
void display::fileCreatedSuccessfully(std::string fileName)
{
	std::cout << '\"' << fileName << "\" created successfully\n";
}

void display::fileDeletionFaild(std::string fileName)
{
	std::cout << '\"' + fileName + "\" deletion faild\n";
}
void display::fileDeletionSucceeded(std::string fileName)
{
	std::cout << '\"' + fileName + "\" deleted successfully\n";
}

void display::connotOpenFile(std::string fileName)
{
	std::cout << '\"' + fileName + "\" connot open file\n";
}
void display::invalidFileName(std::string fileName)
{
	std::cout << '\"' + fileName + "\" invalid file name\n";
}
void display::fileAlreadyExists(std::string fileName){

	std::cout << '\"' << fileName << "\" already exists\n";
}
void display::fileRenamedSuccessfully(std::string oldFileName, std::string newFileName)
{
	std::cout << '\"' << oldFileName << "\" renamed successfully to \"" << newFileName << "\"\n";
}
void display::faildToRenameFile(std::string oldFileName, std::string newFileName)
{
	std::cout << "Falid to rename \"" << oldFileName << "\" to \"" << newFileName << "\"\n";
}
void display::numShouldBePositive(unsigned num)
{
	std::cout << '\"' << std::to_string(num) << "\" invalid number, number must be positive\n"; 
}
void display::invalidOption(std::string option)
{
	std::cout << '\"' + option + "\" invalid option\n";
}
void display::offerHelp()
{
	std::cout << "Use " << process::generateOption("h") << " option to get help.";
}
void display::offerHelp(std::string command)
{
	std::cout << '\"' << command << "\" invalid command\nUse " << process::generateOption("h")
		<< " option to get help.";
}
void display::help()
{
	std::cout << "Syntax: doit.exe [ / (for Windows) | - (for Linux)] option <listName>\n\n"

		<< "Description: This is a simple command-line todo list application. It facilitates\n"
		<< "creating, deleting, and renaming lists,as well as managing tasks within these lists,\n"
		<< "including, creating, inserting, deleting, checking, unchecking, and listing tasks.\n\n"

		<< "A list name is necessary for this tool to function, unless using the help command\n"
		<< "or listing existing lists.\n\n"

		<< "There are two types of options: list options, which pertain to the lists themselves,\n"
		<< "and task options, which concern tasks within the lists. These two types cannot be\n"
		<< "combined in a single command. Furthermore, options of the list type cannot be combined,\n"
		<< "but task options can be.\n\n"

		<< "Lists are stored as text files in [$HOME/Documents|%USERPROFILE\\Documents].\n\n"

		<< "Options:\n"
		<< "List options:\n"
		<< "cl : Create list. File extensions are automatically generated if not provided,\n"
		<< "     This option does not take arguments; the list name specified at the end of\n"
		<< "     the command serves as the argument.\n"
		<< "dl : Delete list. File extensions are automatically generated if not provided.\n"
		<< "     This option does not take arguments; the list name specified at the end of\n"
		<< "     the command serves as the argument.\n"
		<< "rl : Rename list. File extensions are automatically generated if not provided.\n"
		<< "     This option takes the new list name as an argument, with the old name\n"
		<< "     specified at the end of the command.\n\n"

		<< "Task options:\n"
		<< "a : Append task to the list. Task text should be enclosed in quotes.\n"
		<< "i : Insert task at a specific position. Requires two arguments: position and\n"
		<< "    \"task text\".\n"
		<< "d : Delete task. Requires the task position as an argument.\n"
		<< "c : Check task. Requires the task position as an argument.\n"
		<< "u : Uncheck a task. Requires the task position as an argument.\n"
		<< "l : List all tasks in a list. The file name serves as the argument. If no file\n"
		<< "    name is provided, it lists all available lists.\n\n"

		<< "h : Display this help message.\n";
}

// Exceptions
void display::exInvalidArg(std::string arg)
{
	std::cerr << '\"' + arg + "\" invalid argument.\n";
}
void display::exOutOfRange(std::string num) {
	
	std::cerr << '\"' + num + "\" is either too big or too small.";
}
