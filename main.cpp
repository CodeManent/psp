#ifndef TEST_

#include "PSP.h"

#include <iostream>
#include <cstdlib>

int main(int /*argc*/, char* /*argv*/[]){
	std::cout << "Starting psp" << std::endl;

	PSP testPSP;

	testPSP.run();

	return EXIT_SUCCESS;
}

#else

#include "Tests.h"
#include <cstdlib>
#include <iostream>

int main(int , char* []){
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


#endif
