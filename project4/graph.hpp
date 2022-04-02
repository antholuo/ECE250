template<class Type>
class graph{
private:
    struct node{
    public:
        // initialization list
        node(Type data_, vector<node*> v = {}):
        data(data_), neighbours(v), isVisited(false){}
    private:
        Type data = {};
        vector<node*> neighbours;
        bool isVisited;
    }
    vector<node*> v;    // all of our vertexes
    void topologicalSortHelper(node* curr_v, stack<node*>& s);  // topological Sort Helper
public:
    int addVertex(type data_);  // adds vertex, returns int.
    void addNeighbour(int a, int b);    // adds edge between index of a and b
}