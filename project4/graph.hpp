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
};

template <typename Type>
void Graph<Type>::addNeighbour(int a, int b) {
    return;
}

template <typename Type>
int Graph<Type>::addVertex(Type data_) {
    // push vertex to the back (makes finding index easier).
    v.push_back(data_);
    // return the index of vertex
    return v.size() - 1;
}