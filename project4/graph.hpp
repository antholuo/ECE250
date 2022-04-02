#include <cstdlib>
#include <vector>
#include <stack>

template <typename Type>
class Graph{
private:
    struct Node{
    public:
        // initialization list
        Node(Type data_, std::vector<Node*> v = {}):
        data(data_), neighbours(v), isVisited(false){}
        void addNodeNeighbour(Node* includer);
    private:
        Type data = {};
        std::vector<Node*> neighbours;
        bool isVisited;
    };
    // vector initialized to be empty
    std::vector<Node*> v;    // all of our vertexes
    void topologicalSortHelper(Node* curr_v, std::stack<Node*>& s);  // topological Sort Helper
public:
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
        // add node to stack AFTER DFS
        s.push(curr_v);
    }
    return;
}

//-------------------------------------
// Graph Public Functions
//-------------------------------------
template <typename Type>
void Graph<Type>::addNeighbour(int a, int b) {
    // recall a->b, which means that a is included by b.
    // this means b needs to be in the neighbours list of a.
    v[a]->addNodeNeighbour(v[b]);
    return;
}

template <typename Type>
int Graph<Type>::addVertex(Type data_) {
    // create a node, and then push to back, and return index.
    struct Node new_node = {data_}; // should make empty node.
    // push vertex to the back (makes finding index easier).
    v.push_back(&new_node);
    // return the index of vertex
    return v.size() - 1;
}

template <typename Type>
std::vector<Type> Graph<Type>::topologicalSort() {
    std::stack<Node*> s; // create stack of visited
    for(auto i:v) { i->isVisited = false}; // not strictly necessary
    for(auto i:v) {
        if(!i->isVisited) {
            topologicalSortHelper(i, s);
        }
    }
    std::vector<type>result;
	while(!s.empty()) {
		result.push_back(s.top()->data); s.pop(); // replace this with a sest or something because otherwise this is n^2
	}
	return result;

}