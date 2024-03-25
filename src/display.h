#pragma once
#include "includes.h"
#include "process.h"

class display
{
public:
	static void invalidDirPath(std::string dirPath);
	static void invalidFilePath(std::string fullPath);
	static void connotOpenFile(std::string fullPath);
	static void emptyList();
	static void invalidFileName(std::string fileName);
	static void fileAlreadyExists(std::string fullPath);
	static void fileCreatedSuccessfully(std::string fileName);
	static void fileDeletionFaild(std::string fileName);
	static void fileDeletionSucceeded(std::string fileName);
	static void fileRenamedSuccessfully(std::string oldFileName, std::string newFileName);
	static void faildToRenameFile(std::string oldFileName, std::string newFileName);
	static void numShouldBePositive(unsigned num);
	static void invalidOption(std::string option);
	static void offerHelp();
	static void offerHelp(std::string command);
	static void help();

	// Exceptions
	static void exInvalidArg(std::string arg);
	static void exOutOfRange(std::string num);
};

