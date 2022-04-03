#include <cstdlib>
#include <vector>
#include <stack>

#define DEBUG true;

template <typename Type>
class Graph{
private:
    class Node{
        public:
        // initialization list
        Node(Type data_, std::vector<Node*> v = {}):
        data(data_), neighbours(v), isVisited(false){}
        void addNodeNeighbour(Node* includer);
        Type getData();
        bool isVisited; // needs to be accessed by the graph
        Type data = {};
        std::vector<Node*> neighbours;
    };
    // vector initialized to be empty
    std::vector<Node*> v;    // all of our vertexes
    void topologicalSortHelper(Node* curr_v, std::stack<Node*>& s);  // topological Sort Helper
public:
    ~Graph(); // destructor
    void printAdjacencyList();
    int addVertex(Type data_);  // adds vertex, returns int.
    void addNeighbour(int a, int b);    // adds edge between index of a and b
    std::vector<Type> topologicalSort();     // sort this graph topologically
};

//-------------------------------------
// Node Public Functions
//-------------------------------------
template <typename Type>
void Graph<Type>::Node::addNodeNeighbour(Node* includer) {
    // never need to submit duplicates (by project design). Otherwise consider sets.
    neighbours.push_back(includer);
}

template <typename Type>
Type Graph<Type>::Node::getData() {
    return data;
}

//-------------------------------------
// Graph Private Functions
//-------------------------------------
template <typename Type>
void Graph<Type>::topologicalSortHelper(Node* curr_v, std::stack<Node*>& s) {
    curr_v->isVisited = true;
    for(auto i:curr_v->neighbours) {
        // run DFS on neighbours (it'll go all the way down one way first before coming up).
        if(!i->isVisited) {
            topologicalSortHelper(i, s);
        }
    }
    // add node to stack AFTER DFS on all neighbours
    s.push(curr_v);
    return;
}

//-------------------------------------
// Graph Public Functions
//-------------------------------------

template <typename Type>
Graph<Type>::~Graph() {
    for (Node* i:v) {
        // ? do something? -> i don't think this is necesasry
    }
}

template <typename Type>
void Graph<Type>::printAdjacencyList() {
    for (Node* i:v) {
        std::cout << "File: " <<i->data<< " \t-Included By-> ";
        for (Node* j:i->neighbours) {
            std::cout << j->data << " ";
        }
        std::cout << std::endl;
    }
}

template <typename Type>
void Graph<Type>::addNeighbour(int a, int b) {
    // recall a->b, which means that a is included by b.
    // this means b needs to be in the neighbours list of a.
    v[a]->neighbours.push_back(v[b]);
    return;
}

template <typename Type>
int Graph<Type>::addVertex(Type data_) {
    // create a node, and then push to back, and return index.
    Node * new_node = new Node(data_); // should make empty node.
    // push vertex to the back
    v.push_back(new_node);
    return v.size() - 1;
}

template <typename Type>
std::vector<Type> Graph<Type>::topologicalSort() {
    std::stack<Node*> s; // create stack of visited
    for(auto i:v) { i->isVisited = false;} // not strictly necessary
    for(Node* i:v) {
        std::cout << "topological sort, on file: " << i->data <<std::endl;
        if(!i->isVisited) {
            topologicalSortHelper(i, s);
        }
    }
    // todo, make this not O(N^2)
    std::vector<Type> result;
	while(!s.empty()) {
        // ? what does this do
		result.push_back(s.top()->getData()); s.pop(); // replace this with a sest or something because otherwise this is n^2
	}
	return result;

}