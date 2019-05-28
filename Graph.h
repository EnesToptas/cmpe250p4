#include <iostream>
#include <list>
#include <vector>
#include "MST.h"

using namespace std;


class Graph {
    class Edge
    {
    public:
        int index;
        int itself;
        int weight;
        Edge(int itselfx, int ind1, int w){
            itself = itselfx;
            index = ind1;
            weight = w;
        }
        Edge& operator = (const Edge &t){
            this->itself = t.itself;
            this->index = t.index;
            this->weight = t.weight;

            return *this;
        }
        bool operator<(const Edge& other) const{
            return !(weight<other.weight);
        }
    };
    int V;
    int height;
    vector<vector<int>> parent;
    vector<vector<int>> parentEdge;
    int *depth;
    list<Edge> *adj;
public:
    int getWeight(int src, int dst);
    void rootTree(int root) ;
    void precomputeSparseMatrix() ;
    int lca(int u, int v) ;
    int completed;
    Graph(int Ve);
    void addEdge(int ind1, int ind2, int weight);
    Graph mstbonus();
    MST mst();

    int BFS(int s, int dst) const;
};
