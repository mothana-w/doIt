#pragma once
#include "task.h"
#include "fileManager.h"
#include "display.h"

#define RESET_COLOR "\033[0m"
#define GREEN_TEXT "\033[32m"

class taskList
{
private:
	task* head;
	std::string listName;

	void handleTaskLine(std::string line);
	void loadList(std::string fullPath);
	// return nullptr if task node not found.
	task* getTask(int _taskNo);
	void decreaseTaskNumbers(task* postDeletedTask);
	void increaseTaskNumbers(task* insertedTask);
	void appendTask(std::string taskLine, bool isChecked);
	void insertTaskFirst(std::string taskLine, bool isChecked);

public:
	taskList(std::string _listName);

	static void createTaskList(std::string listName);
	static void deleteTaskList(std::string listName);
	static void renameTaskList(std::string oldListName, std::string newListName);

	void displayTasks();
	void insertTaskFirst(std::string taskLine);
	// if taskpos 0 or 1 insert first, if greater than counter append.
	void insertTask(std::string taskLine, int taskPos);
	void appendTask(std::string taskLine);

	bool deleteFirstTask();
	bool deleteTask(int taskNo);

	//return 1 on success and 0 on failure.
	bool checkTask(int taskNo);
	bool uncheckTask(int taskNo);

	~taskList();
};

