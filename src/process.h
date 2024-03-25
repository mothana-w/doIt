#pragma once
#include "includes.h"
#include "display.h"
#include "taskList.h"

class process
{
private:
	static std::vector<std::string> listFileOptions;
	static std::vector<std::string> otherOptions;
	static int convertToNum(std::string num);
	static std::string getCommand(int argc, char* argv[]);

	static bool processListFileArgs(int argc, char* argv[]);
	static bool processOtherArgs(int argc, char* argv[]);

public:
	static std::string generateOption(std::string option);
	static bool isValidOption(std::string option);
	static void handleSingleOptCommands(int argc, char* argv[]);
	static void validateCommand(int argc, char* argv[]);
	static void processArgs(int argc, char* argv[]);
};

