#include "process.h"

std::vector<std::string> process::listFileOptions = { "cl", "dl", "rl" };
std::vector<std::string> process::otherOptions = { "a", "i", "d", "c", "u", "l", "h"};

std::string process::generateOption(std::string option)
{
	std::string fullOption = '-' + option;

#ifdef _WIN32
	fullOption = '/' + option;
#endif
	return fullOption;
}
bool process::isValidOption(std::string option)
{
	for (int indx = 0; indx < listFileOptions.size(); ++indx)
		if (option == listFileOptions.at(indx))
			return true;
	for (int indx = 0; indx < otherOptions.size(); ++indx)
		if (option == otherOptions.at(indx))
			return true;

	return false;
}
int process::convertToNum(std::string num)
{
	int number = 0;
	try {
		number = stoi(num);
	}
	catch (std::invalid_argument){
		display::exInvalidArg(num);
		exit(EXIT_SUCCESS);
	}
	catch (std::out_of_range) {
		display::exOutOfRange(num);
		exit(EXIT_SUCCESS);
	}
	return number;
}
std::string process::getCommand(int argc, char* argv[])
{
	std::string command = "";
	for (int indx = 0; indx < argc; ++indx) 
		command += std::string(argv[indx]) + ' ';

	return command;
}
void process::validateCommand(int argc, char* argv[])
{
	handleSingleOptCommands(argc, argv);
	bool lstFileOptn = false;
	bool otherOptn = false;

	for (int indx = 1; indx < argc; ++indx) {
		bool lstFileOpt = false;
		bool otherOpt = false;

		char slash = '-';
#ifdef _WIN32
		slash = '/';
#endif

		if (argv[indx][0] == slash) {
			for (int i = 0; i < listFileOptions.size(); ++i) {
				if (std::string(argv[indx]) == generateOption(listFileOptions.at(i))) {
					if (lstFileOptn) // checkes if this kind of options were repeated
					{
						display::offerHelp(getCommand(argc, argv));
						exit(EXIT_SUCCESS);
					}
					lstFileOpt = true;
					lstFileOptn = true;
					break;
				}
			}
			for (int i = 0; i < otherOptions.size(); ++i) {
				if (std::string(argv[indx]) == generateOption(otherOptions.at(i))) {
					otherOpt = true;
					otherOptn = true;
					break;
				}
			}
			if (!lstFileOpt && !otherOpt) {
				display::invalidOption(std::string(argv[indx]));
				exit(EXIT_SUCCESS);
			}
		}
	}

	if (lstFileOptn && otherOptn) {
		display::offerHelp(getCommand(argc, argv));
		exit(EXIT_SUCCESS);
	}
}

bool process::processListFileArgs(int argc, char* argv[])
{
	for (int indx = 1; indx < argc - 1; ++indx) {
		if (std::string(argv[indx]) == generateOption("cl") && argc == 3) {
			taskList::createTaskList(std::string(argv[indx + 1]));
			++indx;
		}
		else if (std::string(argv[indx]) == generateOption("dl") && argc == 3) {
			taskList::deleteTaskList(std::string(argv[indx + 1]));
			++indx;
		}
		else if (std::string(argv[indx]) == generateOption("rl") && argc == 4) {
			taskList::renameTaskList(std::string(argv[indx + 2]), argv[indx + 1]);
			indx += 2;
		}
		else { return false; }
	}
	return true;
}
bool process::processOtherArgs(int argc, char* argv[])
{
	std::string listName = std::string(argv[argc - 1]);
	if (fileManager::validateFileName(listName) == fileManager::invalidFileName) {
		display::invalidFilePath(listName);
		exit(EXIT_SUCCESS);
	}

	taskList list(listName);
	for (int indx = 1; indx < argc - 1; ++indx) {
		if (std::string(argv[indx]) == generateOption("a")) {
			++indx;
			list.appendTask(argv[indx]);
		}
		else if (std::string(argv[indx]) == generateOption("i")) {

			int pos = convertToNum(argv[indx + 1]);
			indx += 2;
			list.insertTask(argv[indx], pos);
		}
		else if (std::string(argv[indx]) == generateOption("d")) {

			int pos = convertToNum(argv[indx + 1]);
			++indx;
			list.deleteTask(pos);
		}
		else if (std::string(argv[indx]) == generateOption("c")) {
			int pos = convertToNum(argv[indx + 1]);
			++indx;
			list.checkTask(pos);
		}
		else if (std::string(argv[indx]) == generateOption("u")) {
			int pos = convertToNum(argv[indx + 1]);
			++indx;
			list.uncheckTask(pos);
		}
		else if (std::string(argv[indx]) == generateOption("l")) {
			list.displayTasks();
		}
		else { return false; }
	}
	return true;
}

void process::handleSingleOptCommands(int argc, char* argv[])
{
	if (argc == 2 && argv[1] == generateOption("h")) {
		display::help();
		exit(EXIT_SUCCESS);
	}
	else if (argc == 2 && argv[1] == generateOption("l")) {
		std::string command = "dir " + fileManager::getDefPath();
		system(command.c_str());
		exit(EXIT_SUCCESS);
	}
	else if (argc == 2){
		display::offerHelp(getCommand(argc, argv));
		exit(EXIT_SUCCESS);
	}
}

void process::processArgs(int argc, char* argv[])
{
	handleSingleOptCommands(argc, argv);
	validateCommand(argc, argv);

	if (processListFileArgs(argc, argv)) {
		exit(EXIT_SUCCESS);
	}
	if (processOtherArgs(argc, argv)) {
		exit(EXIT_SUCCESS);
	}
	else{
		display::offerHelp();
		exit(EXIT_SUCCESS);
	}
}
