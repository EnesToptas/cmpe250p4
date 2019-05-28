#include "Graph.h"
#include <queue>
#include <stack>
#include <map>
#include <cmath>

Graph::Graph(int Ve) {
	V = Ve;
	height = ceil(log(V));
	adj = new list<Edge>[V];
	vector<vector<int>> a(V, vector<int>(height));
	parent = a;
	parentEdge = a;
	depth = new int[V];
	completed = 0;
}

void Graph::addEdge(int ind1, int ind2, int weight) {
	adj[ind1].push_back(*new Edge(ind1,ind2,weight));
	adj[ind2].push_back(*new Edge(ind2,ind1,weight));
}
MST Graph::mst() {
	priority_queue<Edge,vector<Edge>,less<Edge>> heaps;
	
	MST m(V);

	int isVisited[V];
	for (int i=0; i<V; i++){
		isVisited[i]=0;
	}
	isVisited[0] = 1;
	completed++;
	for(list<Edge>::iterator x = adj[0].begin(); x != adj[0].end(); x++){
		heaps.push(*x);
	}
	while (!heaps.empty()){
		Edge tmp = heaps.top();
		if(completed==V) break;
		if(isVisited[tmp.index]==1){
			heaps.pop();
		}
		else{
			heaps.pop();
			m.addEdge(tmp.itself,tmp.index,tmp.weight);
			list<Edge>::iterator x = adj[tmp.index].begin();
			for(int i = 0; i<adj[tmp.index].size(); i++){
				if(isVisited[(*x).index]!=1){
					heaps.push(*x);
				}
			x++;
			}
		isVisited[tmp.index]=1;
		completed++;
		}
	}
	return m;
	
}

Graph Graph::mstbonus() {
	priority_queue<Edge,vector<Edge>,less<Edge>> heaps;
	
	Graph g(V);

	int isVisited[V];
	for (int i=0; i<V; i++){
		isVisited[i]=0;
	}
	isVisited[0] = 1;
	completed++;
	for(list<Edge>::iterator x = adj[0].begin(); x != adj[0].end(); x++){
		heaps.push(*x);
	}
	while (!heaps.empty()){
		Edge tmp = heaps.top();
		if(completed==V) break;
		if(isVisited[tmp.index]==1){
			heaps.pop();
		}
		else{
			heaps.pop();
			g.addEdge(tmp.itself,tmp.index,tmp.weight);
			list<Edge>::iterator x = adj[tmp.index].begin();
			for(int i = 0; i<adj[tmp.index].size(); i++){
				if(isVisited[(*x).index]!=1){
					heaps.push(*x);
				}
			x++;
			}
		isVisited[tmp.index]=1;
		completed++;
		}
	}
	return g;
	
}

int Graph::BFS(int s, int dst) const
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
			return paths.find(index)->second;
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

void Graph::rootTree(int root)  {
  int N = V;
  stack<int> s;
  s.push(root);
  parent[root][0] = -1;
  parentEdge[root][0] = 0;
  depth[root] = 0;
  while (!s.empty()) {
    int currentVertex = s.top(); s.pop();
    for(list<Edge>::iterator x = adj[currentVertex].begin(); x != adj[currentVertex].end(); x++){
       if((*x).index != parent[currentVertex][0]) {
         parent[(*x).index][0] = currentVertex;
         parentEdge[(*x).index][0] = (*x).weight;
         depth[(*x).index] = depth[currentVertex] + 1;
         s.push((*x).index);
       }
     }
  }
}

void Graph::precomputeSparseMatrix()  
{	
    for (int i=1; i<height; i++)
    { 
        for (int node = 0; node < V; node++) 
        {
            if (parent[node][i-1] != -1){
                parent[node][i] = parent[parent[node][i-1]][i-1]; 
                parentEdge[node][i] = max(parentEdge[node][i-1],parentEdge[parent[node][i-1]][i-1]);
            }
        } 
    } 
}

 
int Graph::lca(int u, int v) 
{ 
    if (depth[v] < depth[u]) 
        swap(u, v); 
  	
  	int first = u;
  	int second = v;
    int diff = depth[v] - depth[u]; 
  	int maxima_first = 0;
  	int maxima_second = 0;
  	
  	if (u == v) 
        return maxima_first;

    // Step 1 of the pseudocode 
    for (int i=0; i<height; i++)
        if ((diff>>i)&1) {
        	maxima_second = max(maxima_second,parentEdge[v][i]);
        	v = parent[v][i];
             
        }
  
    // now depth[u] == depth[v] 
    if (u == v) {
        return maxima_second; 
    }
  
    // Step 2 of the pseudocode 
    for (int i=height-1; i>=0; i--) {
      if (parent[u][i] != parent[v][i]) 
        { 
        	maxima_first = max(maxima_first,parentEdge[u][i]);
        	maxima_second = max(maxima_second,parentEdge[v][i]);
            u = parent[u][i]; 
            v = parent[v][i]; 
        }
    }	
    
    maxima_first = max(maxima_first,parentEdge[u][0]);
    maxima_second = max(maxima_second,parentEdge[v][0]);

    return max(maxima_first,maxima_second);
} 

int Graph::getWeight(int src, int dst){
	for(list<Edge>::iterator x = adj[src].begin(); x != adj[src].end(); x++){
       if((*x).index==dst)
       	return (*x).weight;
    }
}
