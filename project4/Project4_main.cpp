/*****************************************
 * ECE 250 Project 4
 * Project4_main.cpp
 *****************************************
 * UW User ID:  a26luo
 * Submitted for ECE 250
 * Semester of Submission:  Winter 2022
 *
 * By  submitting this file, I affirm that
 * I am the author of all modifications to
 * the provided code.
 *****************************************/

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include "graph.hpp"

int main(int argc, char** argv)
{
	//first input argument is always the program name...
	char* fileName = argv[1];

	//open the file
	std::ifstream fin(fileName);
	
	if(!fin)
	{
		std::cout<< "File not found" << std::endl;
		return EXIT_FAILURE;
	}
	Graph<std::string> myGraph;
	
	std::string line;
	while(std::getline(fin,line))
	{
		int output = myGraph.addVertex( line );
		//this is just to get you going.  You'll need to do much more here...
		std::cout << output << " " <<line;
		if (line[0] == '#') {
			// start of the line will be an include statement, so we need to find
			std::string word = "";
			bool begin{false};
			for( auto x:line ) {
				if (begin == true) {
					if (x == '>') {
						begin = false;
					} else {
						word += x;
					}
					
				}
				if (x == '<') {
					begin = true;
				}
			}
			std::cout << " |" << word << "| ";
			std::cout << "!!!!" << std::endl;
		} else {
			std::string word = "";
			bool begin{false};
			for( auto x:line ) {
				if (begin == true) {
					if (x == '>') {
						begin = false;
					} else {
						word += x;
					}
					
				}
				if (x == '<') {
					begin = true;
				}
			}
			std::cout << " |" << word << "| ";
			std::cout << "-----" << std::endl;
		}
	}
	
	return EXIT_SUCCESS;
}
