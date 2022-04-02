#ifndef ARRAY_TESTER_H
#define ARRAY_TESTER_H

#ifndef nullptr
#define nullptr 0
#endif

#include "Tester.h"
#include "Array.h"
#include "ece250.h"

#include <iostream>
#include <cmath>

template <typename Type>
class Array_tester:public Tester< Array<Type> > {
	using Tester< Array<Type> >::object;
	using Tester< Array<Type> >::command;

	public:
		Array_tester( Array<Type> *obj = 0 ):Tester< Array<Type> >( obj ) {

			// empty
		}

		void process();
};

/****************************************************
 * void process()
 *
 * Process the current command.  For Array, these include:
 *
 *   new             new Array()     create a new array with default capacity
 *   new: n          new Array( n )  create a new array with capacity n
 *   size n          size            the size equals n
 *   capacity n      capacity        the capacity equals n
 *   empty b         empty           empty() returns the Boolean value b
 *   full b          full            full() returns the Boolean value b
 *
 *   at i m          operator[]      object[i] returns m
 *   at! i           operator[]      object[i] throws an out_of_range
 *
 *   append n b      append          attempting to append n returns the Boolean value b
 *   clear           clear           empties the array--always succeeds as a test
 *
 *  Others
 *   summary                         prints the amount of memory allocated
 *                                   minus the memory deallocated
 *   details                         prints a detailed description of which
 *                                   memory was allocated with details
 *   !!                              use the previous command, e.g.  5 append 3
 *                                                                   6 !! 7         // same as append 7
 *   !n                              use the command used in line n  7 append 7
 *                                                                   8 !7 9         // same as append 9
 *
 ****************************************************/

template <typename Type>
void Array_tester<Type>::process() {
	if ( command == "new" ) {
		object = new Array<Type>();
		std::cout << "object = new Array<Type>();  // ";
		std::cout << "Okay" << std::endl;
	} else if ( command == "new:" ) {
		int n;
		std::cin >> n;
		std::cout << "object = new Array<Type>( " << n << " );  // ";
		object = new Array<Type>( n );
		std::cout << "Okay" << std::endl;
	} else if ( command == "size" ) {
		int expected_size;
		std::cin >> expected_size;

		std::cout << "object->size() == " << expected_size << ";  // ";

		int actual_size = object->size() ;

		if ( actual_size == expected_size ) {
			std::cout << "Okay" << std::endl;
		} else {
			std::cout << "Failure in size(): expecting the value '" << expected_size
			          << "' but got '" << actual_size << "'" << std::endl;
		}
	} else if ( command == "capacity" ) {
		int expected_capacity;
		std::cin >> expected_capacity;

		std::cout << "object->capacity() == " << expected_capacity << ";  // ";

		int actual_capacity = object->capacity() ;

		if ( actual_capacity == expected_capacity ) {
			std::cout << "Okay" << std::endl;
		} else {
			std::cout << "Failure in capacity(): expecting the value '" << expected_capacity
			          << "' but got '" << actual_capacity << "'" << std::endl;
		}
	} else if ( command == "empty" ) {
		bool expected_empty;
		std::cin >> expected_empty;

		if ( expected_empty ) {
			std::cout << "object->empty() == true;  // ";
		} else {
			std::cout << "object->empty() == false;  // ";
		}

		bool actual_empty = object->empty() ;

		if ( actual_empty == expected_empty ) {
			std::cout << "Okay" << std::endl;
		} else {
			std::cout << "Failure in empty(): expecting the value '" << expected_empty
			          << "' but got '" << actual_empty << "'" << std::endl;
		}
	} else if ( command == "full" ) {
		bool expected_full;
		std::cin >> expected_full;

		if ( expected_full ) {
			std::cout << "object->full() == true;  // ";
		} else {
			std::cout << "object->full() == false;  // ";
		}

		bool actual_full = object->full() ;

		if ( actual_full == expected_full ) {
			std::cout << "Okay" << std::endl;
		} else {
			std::cout << "Failure in full(): expecting the value '" << expected_full
			          << "' but got '" << actual_full << "'" << std::endl;
		}
	} else if ( command == "at" ) {
		int index;
		std::cin >> index;

		Type expected_value;
		std::cin >> expected_value;

		std::cout << "(*object)[" << index << "] == " << expected_value << ";  // ";

		Type actual_value = object->operator[]( index ) ;

		if ( actual_value == expected_value ) {
			std::cout << "Okay" << std::endl;
		} else {
			std::cout << "Failure in instance[" << index << "]: expecting the value '" << expected_value
			          << "' but got '" << actual_value << "'" << std::endl;
		}
	} else if ( command == "at!" ) {
		int index;
		std::cin >> index;

		std::cout << "try {" << std::endl
		          << "    (*object)[" << index << "];" << std::endl
		          << "} catch ( out_of_range ) {" << std::endl
		          << "    // expecting this error" << std::endl
		          << "} // ";


		try {
			object->operator[]( index );
			std::cout << "Failure in instance[" << index << "]: expecting to catch an exception but nothing was raised."
			          << std::endl;
		} catch( out_of_range ) {
			std::cout << "Okay" << std::endl;
		} catch (...) {
			std::cout << "Failure in instance[" << index << "]: expecting an out_of_range exception but caught a different exception" << std::endl;
		}
	} else if ( command == "append" ) {
		Type n;
		bool expected_append;

		std::cin >> n;
		std::cin >> expected_append;

		if ( expected_append ) {
			std::cout << "object->append( " << n << " ) == true;  // ";
		} else {
			std::cout << "object->append( " << n << " ) == false;  // ";
		}

		bool actual_append = object->append( n );

		if ( actual_append == expected_append ) {
			std::cout << "Okay" << std::endl;
		} else {
			std::cout << "Failure in append(" << n << "): expecting the value '" << expected_append
			          << "' but got '" << actual_append << "'" << std::endl;
		}
	} else if ( command == "clear" ) {
		std::cout << "object->clear();  // ";
		object->clear();

		std::cout << "Okay" << std::endl;
	}  else {
		std::cout << command << ": Command not found." << std::endl;
	}
}

#endif
