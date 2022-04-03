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
#include <unordered_map>
#include <deque>

#include "graph.hpp"

/*
* How do we do this?
* Have a bunch of included by relationships. I.E. A->B means that we compile A before B
* Then, when we do topological sort (with DFS), after we visit a node we put it onto the stack.
* This means that the furthest in nodes will always be put to stack before the shallowest nodes.
? somehow need the stack to know if the node is in there or not?
*/
// ! create map to keep track of what is in our adjacency list? (so we don't insert twice)...
// - This map will then be used to keep track of whether or not something has already been popped


// Declarations
std::string getWord(std::string line);

int main(int argc, char** argv)
{
	//first input argument is always the program name...

	// TODO: UNCOMMENT THIS
	char* fileName = argv[1];

	// ! COMMENT THIS OUT WHEN SUBMITTING
	// char* fileName = "inputTest.txt";
	//open the file
	std::ifstream fin(fileName);
	
	if(!fin)
	{
		std::cout<< "File not found" << std::endl;
		return EXIT_FAILURE;
	}

	// variables here
	
	// our adjacency graph
	Graph<std::string> adj_graph;
	
	// our hashmap
	std::unordered_map<std::string, int> verif_map;

	// two integers for keeping track of our vertices.
	// a->b means a included by b (so a compiled before b)
	int a;
	int b;

	std::string line;
	std::string word;
	while(std::getline(fin,line))
	{
		//this is just to get you going.  You'll need to do much more here...
		// std::cout <<line <<std::endl;
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
	} // end while. ALl nodes have now been added. Begin DFS.

	// prints our adjacency list (for debugging purposes only)
	// adj_graph.printAdjacencyList();

	// get our result in a deque.
	std::deque<std::string> result = adj_graph.topologicalSort();

	// print those elements (two ways to print -> not sure which one is more 'correct')
	for (std::string fl:result) {std::cout << fl << std::endl;}
	// for (auto it = result.begin(); it != result.end(); ++it){std::cout << *it << std::endl;}
	
	return EXIT_SUCCESS;
}

std::string getWord(std::string line) {
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
	return word;
}
