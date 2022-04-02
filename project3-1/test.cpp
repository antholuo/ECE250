#include <iostream>
#include "Search_tree.h"


int main() {
	Search_tree<int> tree;
	tree.insert(4);
	tree.insert(3);
	tree.insert(2);
	tree.insert(1);
	std::cout << tree;
	tree.erase(2);
	std::cout << tree;
		for ( Search_tree<int>::Iterator itr = tree.begin(); itr != tree.end(); ++itr ) {
		std::cout << *itr << " ";
	}
	for ( int i = 1; i <= 60; ++i ) {
		int j = (83*i) % 30;
		// std::cout << i << "\t" << j << std"::endl;
		std::cout << j<< "-" <<tree.insert( j ) << " | ";
	}


	for ( int i = 1; i <= 30; ++i ) {
		int j = (97*i);
		std::cout << j<< "-" <<tree.insert( j ) << " | ";
	}
	std::cout << tree;
	std::cout << std::endl;

	std::cout << "Front:   " << tree.front()   << std::endl;
	std::cout << "Back:    " << tree.back()    << std::endl;
	std::cout << "Height:  " << tree.height()  << " <- this will change for an AVL tree" << std::endl;

	std::cout << "--> ";

	for ( Search_tree<int>::Iterator itr = tree.begin(); itr != tree.end(); ++itr ) {
		std::cout << *itr << " ";
	}

	std::cout << std::endl;

	std::cout << "--> ";

	for ( Search_tree<int>::Iterator itr = tree.rbegin(); itr != tree.rend(); --itr ) {
		std::cout << *itr << " ";
	}

	std::cout << std::endl;
		std::cout << "ERASING " << std::endl;

	for (int i = 0; i<1000; i++) {
		std::cout << i << " " << tree.erase(i) << " | ";
	}
	std::cout << tree;
	std::cout << "penguni done" << std::endl;

	tree.clear();

	std::cout << "--> ";
	

	for ( Search_tree<int>::Iterator itr = tree.begin(); itr != tree.end(); ++itr ) {
		std::cout << *itr << " ";
	}
	std::cout << std::endl;
	return 0;
}
