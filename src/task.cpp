#include "task.h"

unsigned task::taskCounter = 0;

task::task() : isChecked(false), checkBox("[ ]"), taskTxt(""), nextTask(nullptr)
{
	++taskCounter;
	taskNo = taskCounter;
}
task::task(std::string _taskTxt) : isChecked(false), checkBox("[ ]"), taskTxt(_taskTxt), nextTask(nullptr)
{
	++taskCounter;
	taskNo = taskCounter;
}
task::task(std::string _taskTxt, bool _isChecked) : isChecked(_isChecked), taskTxt(_taskTxt), nextTask(nullptr)
{
	++taskCounter;
	taskNo = taskCounter;
	setCheckBox();
}
task::task(std::string _taskTxt, task* _nextTask) : isChecked(false), checkBox("[ ]"), taskTxt(_taskTxt), nextTask(_nextTask)
{
	++taskCounter;
	taskNo = taskCounter;
}

void task::setTaskNo(unsigned _taskNo)
{
	if (_taskNo <= 0)
		taskNo = 0;
	else
		taskNo = _taskNo;
}
void task::setCheckBox()
{
	if (isChecked)
		checkBox = "[*]";
	else
		checkBox = "[ ]";
}
void task::setTaskTxt(std::string _taskTxt)
{
	taskTxt = _taskTxt;
}
void task::setNextTask(task* _nextTask)
{
	nextTask = _nextTask;
}

void task::decreaseTaskCounter()
{
	--taskCounter;
}

void task::check()
{
	isChecked = true;
	setCheckBox();
}
void task::uncheck()
{
	isChecked = false;
	setCheckBox();
}

unsigned task::getTaskCounter()
{
	return taskCounter;
}
unsigned task::getTaskNo()
{
	return taskNo;
}
bool task::getIsCheck()
{
	return isChecked;
}
std::string task::getCheckBox()
{
	return checkBox;
}
std::string task::getTaskTxt()
{
	return taskTxt;
}
task* task::getNextTask()
{
	return nextTask;
}

std::string task::getTask()
{
	return std::to_string(getTaskNo()) + '.' + getCheckBox() + ' ' + getTaskTxt();
}
