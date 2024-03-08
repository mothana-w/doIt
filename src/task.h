#pragma once
#include "includes.h"

class task
{
private:
	static unsigned taskCounter;
	unsigned taskNo;

	bool isChecked;
	std::string checkBox;

	std::string taskTxt;
	task* nextTask;

public:
	task();
	task(std::string _taskTxt);
	task(std::string _taskTxt, task* _nextTask);

	void setTaskNo(unsigned _taskNo);
	void setCheckBox();
	void setTaskTxt(std::string _taskTxt);

	void check();
	void uncheck();

	unsigned getTaskCounter();
	unsigned getTaskNo();
	bool getIsCheck();
	std::string getCheckBox();
	std::string getTaskTxt();

	std::string getTask();
};

