#include "PSP.h"
#include "Tests.h"
#include <cstdlib>
#include <cstring>
#include <iostream>

/* If the only parameter is --test run the tests
 * else continue with normal operation, creating a psp "device" and running it.
 */
int main(int argc , char* argv[]){
	const char tstr[] = "--test";
	if(argc == 2 && !strncmp(argv[1], tstr, strlen(tstr))){
		//run the tests
		bool success = runTests();
		if(success){
			std::cout << "Tests succeded" << std::endl;
			return EXIT_SUCCESS;
		}
		else{
			std::cout << "Tests failed" << std::endl;
			return EXIT_FAILURE;
		}
	}

	// normal operation
	std::cout << "Starting psp" << std::endl;
	PSP psp;
	psp.run();

	return EXIT_SUCCESS;
}

