#include <iostream>
#include <list>
#include <vector>

using namespace std;


class MST {
public:
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
    list<Edge> *adj;
	int completed;
    MST(int Ve);
    void addEdge(int ind1, int ind2, int weight);
    int BFS(int s, int dst) const;
};

