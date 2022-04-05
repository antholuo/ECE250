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

#include <cstdlib>
#include <deque>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>

#include "graph.hpp"

/*
* Notes:
* Total runtime should be linear O(n). In fact, if we break it down, it should look like this:
* 	+ O(V+E) : parsing our inputs and adding them to our graph (must go through every single file and include of that file).
*	+ O(V+E) : DFS (must go through every vertex once, and explore every possible edge).
*	+ O(V)   : OUTPUT (must print every file present in order, each file = a vertex, so goes through every vertex).
*	In total, this is still O(3V+E), which is linear (take out constants, addition of V and E still linear)
*/

// Declarations
std::string getWord(std::string line);

// {{{ main }}}
/**
 * @brief Main entry point for ECE 250 Project 4
 * 
 * @details description main function has 4 main steps:
 * 	1 - get the input file
 * 	2 - add all the files into a graph class, and link them with edges as necessary
 * 	3 - topological sort
 * 	4 - print to terminal the sorted result
 * 
 * @param argc 
 * @param argv 
 * @return int 
 */
int main(int argc, char** argv) {
	// first input argument is always the program name...
	
	// ! step 1: get the file
	// get filename from cli input
	char* fileName = argv[1];

	// open the file
	std::ifstream fin(fileName);

	if (!fin) {
		std::cout << "File not found" << std::endl;
		return EXIT_FAILURE;
	}

	// variables here

	// create adjacency graph/list
	Graph<std::string> adj_graph;

	// our hashmap to check for duplication of files
	std::unordered_map<std::string, int> verif_map;

	// two integers for keeping track of our vertices.
	// a->b means a included by b (so a compiled before b)
	int a;
	int b;

	// line and word strings to be used when getting input
	std::string line;
	std::string word;

	// ! step 2: add filenames to our graph && link them as necessary
	while (std::getline(fin, line)) {
		// this is just to get you going.  You'll need to do much more here...
		//  std::cout <<line <<std::endl;
		if (line[0] == '#') {
			// start of the line will be an include statement
			word = getWord(line);
			if (verif_map.count(word) > 0) {
				// it is in the map
				a = verif_map[word];
			} else {
				// not in the map, and thus not in our vector.
				a = adj_graph.addVertex(word);
				verif_map[word] = a;
			}
			// add this to our graph
			// ? why are you segfaulting
			adj_graph.addNeighbour(a, b);
		} else {
			word = line;
			if (verif_map.count(word) > 0) {
				// it is in the map
				b = verif_map[word];
			} else {
				// not in the map, and thus not in our vector.
				b = adj_graph.addVertex(word);
				verif_map[word] = b;
			}
		}
	}  // end while. ALl nodes have now been added. Begin DFS.

	// prints our adjacency list (for debugging purposes only)
	// adj_graph.printAdjacencyList();

	// ! step 3: get our sorted result in a deque.
	std::deque<std::string> result = adj_graph.topologicalSort();

	// ! step 4: print results out
	// ( there are two ways to print -> not sure which one is more 'correct' )
	for (std::string fl : result) { std::cout << fl << std::endl; }
	// for (auto it = result.begin(); it != result.end(); ++it){std::cout << *it << std::endl;}

	return EXIT_SUCCESS;
}

/**
 * @brief Get the 'word' or file we want from the text line.
 *
 * @details description the left and right '<>' and adds remaining characters to word before returning that word.
 * 
 * @param line
 * @return std::string
 */
std::string getWord(std::string line) {
	std::string word = "";
	bool begin{false};
	for (auto x : line) {
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
	return word;
}
