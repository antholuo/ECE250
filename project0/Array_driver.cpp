/****************************************************
 * Executable:  Array_driver
 * Author:  Douglas Wilhelm Harder
 * Copyright (c) 2014-5 by Douglas Wilhelm Harder.  All rights reserved.
 *
 * DO NOT EDIT THIS FILE
 *
 * Create an instance of
 *    Array_tester<short>
 *    Array_tester<int>
 *    Array_tester<float>
 *    Array_tester<double>
 * as requested and calls the member function run().
 *
 * The member function run() will interpret the
 * input appropriately and exit when the interpreter
 * receives either the command 'exit' or and
 * end-of-file.
 ****************************************************/

#include <iostream>
#include <cstring>
#include "Array_tester.h"

int main( int argc, char *argv[] ) {
	if ( argc > 2 ) {
		std::cerr << "Expecting at most one command-line argument" << std::endl;

		return -1;
	}

	std::cout << "Starting Test Run" << std::endl;

	if ( argc == 1 || !std::strcmp( argv[1], "int" ) ) {
		if ( argc == 1 ) {
			std::cerr << "Expecting a command-line argument of either 'short', 'int', 'float' or 'double'," << std::endl
			          << "but got none; using 'int' by default." << std::endl;
		}

		Array_tester<int> tester;
		tester.run();
	} else if ( !std::strcmp( argv[1], "short" ) ) {
		Array_tester<short> tester;
		tester.run();
	} else if ( !std::strcmp( argv[1], "double" ) ) {
		Array_tester<double> tester;
		tester.run();
	} else if ( !std::strcmp( argv[1], "float" ) ) {
		Array_tester<float> tester;
		tester.run();
	} else {
		std::cerr << "Expecting a command-line argument of either 'short', 'int', 'float' or 'double'," << std::endl
		          << "but got '" << argv[1] << "'" << std::endl;
	}

	std::cout << "Finishing Test Run" << std::endl;

	return 0;
}
