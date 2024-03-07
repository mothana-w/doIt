#include "fileManager.h"


std::string fileManager::concatenatePath(std::string part1Path, std::string part2Path)
{
	char slash = '/';
#ifdef _WIN32
	slash = '\\';
#endif

	if (part1Path[part1Path.length() - 1] != slash && part2Path[0] != slash)
		return part1Path + slash + part2Path;
	else
		return part1Path + part2Path;
}
std::string fileManager::getUserPath()
{
	char* userPath = getenv("HOME");

#ifdef _WIN32
	userPath = getenv("USERPROFILE");
#endif
	
	return userPath;
}
std::string fileManager::getDefPath()
{
	std::string userPath = getUserPath();
	std::string restOfPath = "Documents/doit/";

#ifdef _WIN32
	restOfPath = "Documents\\doit\\";
#endif

	std::string fullDefPath = concatenatePath(userPath, restOfPath);
	return fullDefPath;
}

bool fileManager::isValidDirPath(std::string path)
{
	struct stat stMetadata;
	return (stat(path.c_str(), &stMetadata) == 0);
}
bool fileManager::isValidFilePath(std::string path)
{
	struct stat stMetadata;
	return stat(path.c_str(), &stMetadata) == 0 && !(stMetadata.st_mode & S_IFDIR);
}

void fileManager::validateFileExtension(std::string& fileName)
{
	std::string extension = "";
	short lastDotIndx = -1;

	for (short indx = 0; indx < fileName.length(); ++indx) {
		if (fileName[indx] == '.')
			lastDotIndx = indx;
	}

	if (lastDotIndx == -1)
		fileName = fileName + ".txt";
	else {
		for (lastDotIndx; lastDotIndx < fileName.length(); ++lastDotIndx)
			extension += fileName[lastDotIndx];

		if (extension != ".txt")
			fileName = fileName + ".txt";
	}
}
fileManager::enPathState fileManager::validateFileName(std::string& fileName)
{
	validateFileExtension(fileName);

	for (unsigned short indx = 0; indx < fileName.length(); ++indx) {
		if (!isalnum(fileName[indx]) && fileName[indx] != '-' && fileName[indx] != '_')
			return enPathState::invalidFileName;
	}
	return enPathState::noProblems;
}

fileManager::enPathState fileManager::createFile(std::string& fileName)
{
	validateFileName(fileName);
	std::string defPath = getDefPath();
	std::string fullPath = concatenatePath(defPath, fileName);
	if (isValidDirPath(defPath)) {
		if (!isValidFilePath(fullPath)) {
			std::fstream file(fullPath, std::ios::out);
			if (file.is_open()) {
				file.close();
				return enPathState::noProblems;
			}
			else { return enPathState::cantOpenFile; }
		}
		else{return enPathState::fileAlreadyExists;}
	}
	else { return enPathState::dirNotFound; }
		
}
fileManager::enPathState fileManager::deleteFile(std::string& fileName)
{
	validateFileExtension(fileName);
	std::string defPath = getDefPath();
	std::string fullPath = concatenatePath(defPath, fileName);
	if (isValidDirPath(defPath)) {
		if (isValidFilePath(fullPath)) {
			if (remove(fullPath.c_str()) == 0)
				return enPathState::noProblems;
			else
				return enPathState::deleteFileFaild;
		}
		else { return enPathState::fileNotFound; }
	}
	else { return enPathState::dirNotFound; }
}
fileManager::enPathState fileManager::renameFile(std::string& fileName, std::string& newName) 
{ 
	validateFileExtension(fileName);
	validateFileExtension(newName);
	std::string defPath = getDefPath();
	std::string fullOldFilePath = concatenatePath(defPath, fileName);
	std::string fullNewFilePath = concatenatePath(defPath, newName);
	
	if (isValidDirPath(defPath)) {
		if (isValidFilePath(fullOldFilePath)) {
			if (!isValidFilePath(fullNewFilePath)) {
				if (rename(fullOldFilePath.c_str(), fullNewFilePath.c_str()) == 0)
					return enPathState::noProblems;
				else
					return enPathState::renameFileFaild;
			}
			else { return enPathState::fileAlreadyExists; }
		}
		else { return enPathState::fileNotFound; }
	}
	else { return enPathState::dirNotFound; }
} 