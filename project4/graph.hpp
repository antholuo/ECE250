#include <cstdlib>
#include <deque>
#include <stack>
#include <string>
#include <vector>

#define DEBUG true;

template <typename Type>
class Graph {
   private:
	class Node {
	   public:
		// initialization list constructor
		Node(Type data_, std::vector<Node*> v = {}) : data(data_), neighbours(v), isVisited(false) {}
		void addNodeNeighbour(Node* includer);
		Type getData();
		bool isVisited;
		Type data = {};
		std::vector<Node*> neighbours;
	};
	// vector initialized to be empty
	std::vector<Node*> v;                                                        // all of our vertexes
	void topologicalSortHelper(Node* curr_v, std::deque<std::string>& o_deque);  // topological Sort Helper
   public:
	~Graph();  // destructor
	void printAdjacencyList();
	int addVertex(Type data_);           // adds vertex, returns int.
	void addNeighbour(int a, int b);     // adds edge between index of a and b
	std::deque<Type> topologicalSort();  // sort this graph topologically
};

//-------------------------------------
// Node Public Functions
//-------------------------------------
/**
 * @brief Adds a Neighbour to a Node
 *  ** DEPRECATED **
 * @tparam Type
 * @param includer - Node which is to be added to the neighbour of this->neighbours[]
 */
template <typename Type>
void Graph<Type>::Node::addNodeNeighbour(Node* includer) {
	// never need to submit duplicates (by project design). Otherwise consider sets.
	neighbours.push_back(includer);
}

/**
 * @brief Gets the data of the node.
 *
 * @tparam Type
 * @return Type
 */
template <typename Type>
Type Graph<Type>::Node::getData() {
	return data;
}

//-------------------------------------
// Graph Private Functions
//-------------------------------------
/**
 * @brief Helper function (internal) topological Sort.
 *
 * Will recursively run DFS an each neighbour if they are not visited.
 * Pushes the data of each node to the front of the deque when done running DFS on all possibilites.
 *
 * @tparam Type
 * @param curr_v - current (start) node for DFS to begin on
 * @param o_deque - deque of strings for our output
 */
template <typename Type>
void Graph<Type>::topologicalSortHelper(Node* curr_v, std::deque<std::string>& o_deque) {
	curr_v->isVisited = true;
	for (auto i : curr_v->neighbours) {
		// run DFS on neighbours (it'll go all the way down one way first before coming up).
		if (!i->isVisited) {
			topologicalSortHelper(i, o_deque);
		}
	}
	// add node to stack AFTER DFS on all neighbours
	// note: pushing to front of deque is the SAME as a stack (O(1))!
	o_deque.push_front(curr_v->data);
	return;
}

//-------------------------------------
// Graph Public Functions
//-------------------------------------
/**
 * @brief Destroy the Graph< Type>:: Graph object **UNUSED**
 *
 * @tparam Type
 */
template <typename Type>
Graph<Type>::~Graph() {
	v.clear();
}

/**
 * @brief Prints the Adjacency List for our graph.
 *
 * Used only for testing.
 *
 * @tparam Type
 */
template <typename Type>
void Graph<Type>::printAdjacencyList() {
	for (Node* i : v) {
		std::cout << "File: " << i->data << " \t-Included By-> ";
		for (Node* j : i->neighbours) {
			std::cout << j->data << " ";
		}
		std::cout << std::endl;
	}
}

/**
 * @brief Adds a neighbour between two nodes.
 *
 * Looks up the index inside our vector of Nodes.
 *
 * @tparam Type
 * @param int a - includee index
 * @param int b - includer index
 */
template <typename Type>
void Graph<Type>::addNeighbour(int a, int b) {
	// recall a->b, which means that a is included by b.
	// this means b needs to be in the neighbours list of a.
	v[a]->neighbours.push_back(v[b]);
	return;
}

/**
 * @brief Adds a vertex (node) to our graph
 *
 * @tparam Type
 * @param std::string data_ - Data that we want the node/vertex to have
 * @return int - Index of this node.
 */
template <typename Type>
int Graph<Type>::addVertex(Type data_) {
	// create a node, and then push to back, and return index.
	Node* new_node = new Node(data_);  // should make empty node.

	// push vertex to the back
	v.push_back(new_node);
	return v.size() - 1;
}

/**
 * @brief Runs DFS on our graph and returns a deque of sorted data
 *
 * @tparam Type
 * @return std::deque<Type> - Deque in stack-fashion of data of nodes in order.
 */
template <typename Type>
std::deque<Type> Graph<Type>::topologicalSort() {
	// Deque of outputs (deque just makes iterating through easier later). Functionally equivalent to a stack
	std::deque<std::string> o_deque;
	for (auto i : v) {
        // Note: not strictly necessary (makes our runtime O(2n))
		i->isVisited = false;
	} 
	for (Node* i : v) {
		// Note: this should be O(n) (only go through every v once).
		// std::cout << "topological sort, on file: " << i->data <<std::endl;
		if (!i->isVisited) {
			topologicalSortHelper(i, o_deque);
		}
	}
	// no need to do anything else since the deque is the file list
	return o_deque;
}