#include "taskList.h"


bool taskList::isChecked(std::string checkBox)
{
	for (int indx = 0; indx < checkBox.length(); ++indx) {
		if (!isalpha(checkBox[indx])) {
			if (checkBox[indx] == '[')
				if (checkBox[indx + 1] == '*')
					return true;
		}
		else
			return false;
	}
	return false;
}
void taskList::handleTaskLine(std::string line)
{
	std::string checkBox = "";
	std::string taskTxt = "";

	for (int indx = 0; indx < line.length(); ++indx) {
		if (indx < 6)
			checkBox += line[indx];
		else
			taskTxt += line[indx];
	}
	appendTask(taskTxt, isChecked(checkBox));
}
void taskList::loadList(std::string fullPath)
{
	std::fstream taskFile(fullPath, std::fstream::in);
	if (taskFile.is_open()) {
		std::string line = "";
		while (std::getline(taskFile, line)) {
			if (line.length() != 0) {
				handleTaskLine(line);
			}
		}
		taskFile.close();
	}
	else { display::connotOpenFile(fullPath); }
}
task* taskList::getTask(unsigned _taskNo)
{
	if (head == nullptr)
		return nullptr;
	else {
		task* temp = head;
		unsigned counter = 1;
		
		while (temp != nullptr) {
			if (counter == _taskNo)
				return temp;

			++counter;
			temp = temp->getNextTask();
		}
		return nullptr;
	}
}
void taskList::decreaseTaskNumbers(task* postDeletedTask)
{
	if (postDeletedTask != nullptr) {
		task::decreaseTaskCounter();

		while (postDeletedTask != nullptr) {
			postDeletedTask->setTaskNo(postDeletedTask->getTaskNo() - 1);
			postDeletedTask = postDeletedTask->getNextTask();
		}
	}
	else
		task::decreaseTaskCounter();
}
void taskList::increaseTaskNumbers(task* insertedTask)
{
	while (insertedTask->getNextTask() != nullptr) {

		insertedTask->setTaskNo(insertedTask->getNextTask()->getTaskNo());
		insertedTask = insertedTask->getNextTask();
	}
	insertedTask->setTaskNo(insertedTask->getTaskNo() + 1);

}

taskList::taskList(std::string _listName) : head(nullptr), listName(_listName)
{
	std::string defPath = fileManager::getDefPath();
	std::string fullPath = fileManager::concatenatePath(defPath, listName);
	if (fileManager::isValidDirPath(defPath)) {
		if (fileManager::isValidFilePath(fullPath)) {
			loadList(fullPath);
		}
		else {
			display::invalidFilePath(fullPath);
			exit(EXIT_SUCCESS);
		}
	}
	else {
		display::invalidDirPath(defPath);
		exit(EXIT_SUCCESS);
	}
}

void taskList::createTaskList(std::string listName)
{
	std::string defPath = fileManager::getDefPath();

	switch (fileManager::createFile(listName)) {
	case fileManager::enPathState::invalidFileName:
		display::invalidFileName(listName);
		break;
	case fileManager::enPathState::dirNotFound:
		display::invalidDirPath(defPath);
		break;
	case fileManager::enPathState::fileAlreadyExists:
		display::fileAlreadyExists(listName);
		break;
	case fileManager::enPathState::cantOpenFile:
		display::connotOpenFile(listName);
		break;
	case fileManager::enPathState::noProblems:
		display::fileCreatedSuccessfully(listName);
		break;
	default:
		break;
	}
}
void taskList::deleteTaskList(std::string listName)
{
	std::string defPath = fileManager::getDefPath();
	std::string fullPath = fileManager::concatenatePath(defPath, listName);

	switch (fileManager::deleteFile(listName)) {
	case fileManager::enPathState::dirNotFound:
		display::invalidDirPath(defPath);
		break;
	case fileManager::enPathState::fileNotFound:
		display::invalidFilePath(fullPath);
		break;
	case fileManager::enPathState::deleteFileFaild:
		display::fileDeletionFaild(listName);
		break;
	case fileManager::enPathState::noProblems:
		display::fileDeletionSucceeded(listName);
		break;
	default:
		break;
	}
}
void taskList::renameTaskList(std::string oldListName, std::string newListName)
{
	std::string defPath = fileManager::getDefPath();
	std::string oldFullPath = fileManager::concatenatePath(defPath, oldListName);

	switch (fileManager::renameFile(oldListName, newListName)) {
	case fileManager::enPathState::dirNotFound:
		display::invalidDirPath(defPath);
		break;
	case fileManager::enPathState::fileNotFound:
		display::invalidFilePath(oldFullPath);
		break;
	case fileManager::enPathState::fileAlreadyExists:
		display::fileAlreadyExists(newListName);
		break;
	case fileManager::enPathState::renameFileFaild:
		display::faildToRenameFile(oldListName, newListName);
		break;
	case fileManager::enPathState::noProblems:
		display::fileRenamedSuccessfully(oldListName, newListName);
		break;
	default:
		break;
	}

}

void taskList::displayTasks()
{
	if (head == nullptr)
		display::emptyList();
	else {
		task* temp = head;

		while (temp != nullptr) {
			if (temp->getIsCheck()) {
				std::cout << GREEN_TEXT << temp->getTask() << RESET_COLOR << '\n';
			}
			else
				std::cout << temp->getTask() << '\n';
			temp = temp->getNextTask();
		}
	}
}
void taskList::insertTaskFirst(std::string taskLine, bool isChecked)
{
	task* newTask = new task(taskLine, isChecked);
	newTask->setNextTask(head);
	head = newTask;
	if (head->getNextTask() != nullptr)
		increaseTaskNumbers(head);

}
void taskList::insertTaskFirst(std::string taskLine) {

	insertTaskFirst(taskLine, false);
}
void taskList::insertTask(std::string taskLine, unsigned taskPos) {

	if (head == nullptr || taskPos <= 1)
		insertTaskFirst(taskLine);
	else if (taskPos > task::getTaskCounter())
		appendTask(taskLine);
	else {
		task* temp = head;
		unsigned counter = 1;
		
		while (counter + 1 != taskPos) {
			++counter;
			temp = temp->getNextTask();
		}
		task* newTask = new task(taskLine);
		newTask->setNextTask(temp->getNextTask());
		temp->setNextTask(newTask);
		increaseTaskNumbers(newTask);
	}
}
void taskList::appendTask(std::string taskLine, bool isChecked)
{
	if (head == nullptr) {
		insertTaskFirst(taskLine, isChecked);
	}
	else {
		task* temp = head;
		while (temp->getNextTask() != nullptr)
			temp = temp->getNextTask();

		task* newTask = new task(taskLine, isChecked);
		temp->setNextTask(newTask);
	}
}
void taskList::appendTask(std::string taskLine)
{
	appendTask(taskLine, false);
}

bool taskList::deleteFirstTask()
{
	if (head != nullptr) 
		head = head->getNextTask();
	decreaseTaskNumbers(head);
	return true;
}
bool taskList::deleteTask(unsigned taskNo) {

	if (head == nullptr || head->getNextTask() == nullptr || taskNo == 1)
		return deleteFirstTask();
	else {
		task* temp = head;
		unsigned counter = 1;

		if (taskNo <= task::getTaskCounter() && taskNo > 1) {
			while (counter + 1 != taskNo) {

				++counter;
				temp = temp->getNextTask();
			}

			temp->setNextTask(temp->getNextTask()->getNextTask());
			decreaseTaskNumbers(temp->getNextTask());
			return true;
		}
		else { 
			return false; 
		}
	}
}

bool taskList::checkTask(unsigned taskNo)
{
	if (taskNo <= task::getTaskCounter()) {

		task* goalTask = getTask(taskNo);
		if (goalTask != nullptr) {
			goalTask->check();
			return true;
		}
	}
	 return false;

}
bool taskList::uncheckTask(unsigned taskNo)
{
	if (taskNo <= task::getTaskCounter()) {

		task* goalTask = getTask(taskNo);
		if (goalTask != nullptr) {
			goalTask->uncheck();
			return true;
		}
	}
	return false;
}

taskList::~taskList()
{
	std::string fullPath = fileManager::concatenatePath(fileManager::getDefPath(), listName);
	std::fstream taskFile(fullPath, std::fstream::out | std::fstream::trunc);
	if (taskFile.is_open()) {
		task* temp = head;

		while (temp != nullptr) {
			taskFile << temp->getTask() << '\n';
			temp = temp->getNextTask();
		}
		taskFile.close();
	}
	else { display::connotOpenFile(listName);}
}

