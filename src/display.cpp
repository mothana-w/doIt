#include "display.h"

void display::invalidDirPath(std::string dirPath)
{
	std::cout << '\"' + dirPath + "\" invalid path\n";
}
void display::invalidFilePath(std::string fullPath)
{
	std::cout << '\"' + fullPath + "\" invalid file\n";
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
