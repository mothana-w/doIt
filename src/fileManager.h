#pragma once
#include "includes.h"
#pragma warning (disable: 4996)

class fileManager
{
public:
	enum enPathState { noProblems, fileAlreadyExists, fileNotFound , dirNotFound, cantOpenFile, invalidFileName, deleteFileFaild, renameFileFaild};

public:
	static std::string concatenatePath(std::string part1Path, std::string part2Path);
	static std::string getUserPath();
	static std::string getDefPath();

	static bool isValidDirPath(std::string path);
	static bool isValidFilePath(std::string path);
	static void validateFileExtension(std::string& fileName);
	static enPathState validateFileName(std::string& fileName);

	static enPathState createFile(std::string& fileName);
	static enPathState deleteFile(std::string& fileName);
	static enPathState renameFile(std::string& fileName, std::string& newName);
};

