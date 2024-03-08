#include "includes.h"

int main() {

	task task1("this is my first task");
	task task2("this is my second task");
	task task3("this is my third task");
	task task4("this is my forth task");
	
	std::cout << task1.getTask() << std::endl;
	std::cout << task2.getTask() << std::endl;
	std::cout << task3.getTask() << std::endl;
	std::cout << task4.getTask() << std::endl;

	std::cout << task1.getTaskCounter() << std::endl;
	return 0;
}