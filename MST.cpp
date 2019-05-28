#include "MST.h"
#include <queue>
#include <stack>
#include <map>

MST::MST(int Ve) {
	V = Ve;
	adj = new list<Edge>[V];
	completed = 0;
}

void MST::addEdge(int ind1, int ind2, int weight) {
	adj[ind1].push_back(*new Edge(ind1,ind2,weight));
	adj[ind2].push_back(*new Edge(ind2,ind1,weight));
}

int MST::BFS(int s, int dst) const
{
	bool *visited = new bool[V];
	for(int i = 0; i < V; i++)
		visited[i] = false;

	list<int> queue;

	visited[s] = true;
	queue.push_back(s);
	int index = s;
	map<int, int> paths;
	paths.insert(std::make_pair<int&, int>(index,0));
	
	list<Edge>::iterator i;
	

	while(!queue.empty())
	{

		index = queue.front();
		if(index==dst){
			return paths.find(index)->second;;
		}
		queue.pop_front();

		for (i = adj[index].begin(); i != adj[index].end(); ++i)
		{
			if (!visited[(*i).index])
			{   
				visited[(*i).index] = true;
				int key = (*i).index;
				int weight = paths.find((*i).itself)->second;
				paths.insert(std::make_pair<int&, const int&>(key,max((*i).weight,weight)));
				queue.push_back((*i).index);
			}
		}
	}
}
