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

	bool isChecked(std::string checkBox);
	void handleTaskLine(std::string line);
	void loadList(std::string fullPath);
	// return nullptr if task node not found.
	task* getTask(unsigned _taskNo);
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
	void insertTask(std::string taskLine, unsigned taskPos);
	void appendTask(std::string taskLine);

	bool deleteFirstTask();
	bool deleteTask(unsigned taskNo);

	//return 1 on success and 0 on failure.
	bool checkTask(unsigned taskNo);
	bool uncheckTask(unsigned taskNo);

	~taskList();
};

