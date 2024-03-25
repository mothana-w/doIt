#include "includes.h"
#include "taskList.h"
#include "process.h"


int main(int argc,char* argv[]) {


	if (argc == 1)
		display::offerHelp();
	else {
		process::processArgs(argc, argv);
	}

	return 0;
}